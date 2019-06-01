/*
  FILE: rw_memory.h
  VERSION: 0.2.0
  DESCRIPTION: Custom memory allocation.
  AUTHOR: Raymond Wan
  USAGE: Simply including the file will only give you declarations (see __API)
    To include the implementation,
      #define RWMEM_IMPLEMENTATION

  NOTE(ray): To quickly navigate through the file,
             sections and/or subsections are available to jump to.
  SECTIONS:
    1. __TYPES
    2. __API
    3. __MACROS
    4. __IMPLEMENTATION
      4.1. __ALIGNED
      4.2. __ARENA
*/

#ifndef __RW_MEMORY_H__
#define __RW_MEMORY_H__

#if defined(RWMEM_STATIC)
  #define RWMEM_DEF static
#elif defined(RWMEM_HEADER_ONLY)
  #define RWMEM_DEF static inline
#else
  #define RWMEM_DEF extern
#endif

///////////////////////////////////////////////////////////////////////////////
// __TYPES
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

typedef struct MA_BookkeepingNode {
  uint8_t *block_ptr;
  size_t cur_alloc_size;
  MA_BookkeepingNode *next;
} MA_BookkeepingNode;

typedef struct MemoryArena {
  size_t block_size_bytes;
  size_t cur_block_pos;
  size_t cur_alloc_size;
  uint8_t *cur_block_ptr;
  // Bookkeeping
  MA_BookkeepingNode *used_blocks_node;
  MA_BookkeepingNode *available_blocks_node;
} MemoryArena;

///////////////////////////////////////////////////////////////////////////////
// __API
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

// __ALIGNED
RWMEM_DEF void *rwmem_aligned_alloc(size_t size, size_t alignment);
RWMEM_DEF void rwmem_aligned_free(void *p);

// __ARENA
RWMEM_DEF MemoryArena rwmem_arena_create(size_t block_size_bytes);
RWMEM_DEF void *rwmem_arena_alloc(MemoryArena *arena, size_t bytes);
RWMEM_DEF void rwmem_arena_free(MemoryArena *arena);
// Reset offset and move all memory from used blocks to available blocks
RWMEM_DEF void rwmem_arena_reset(MemoryArena *arena);

#ifdef __cplusplus
}
#endif


///////////////////////////////////////////////////////////////////////////////
// __MACROS
///////////////////////////////////////////////////////////////////////////////

#define ALIGN_X(size, x) ((size + (x-1)) & ~(x-1))
#define ALIGN4(size) ALIGN_X(size, 4)
#define ALIGN8(size) ALIGN_X(size, 8)
#define ALIGN16(size) ALIGN_X(size, 16)
#define IS_ALIGNED(p, alignment) \
  ((((unsigned long) (const void *) p) % alignment) == 0)

#define DEFAULT_ARENA_BLOCK_SIZE_BYTES 262144


///////////////////////////////////////////////////////////////////////////////
// __IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////

#if defined(RWMEM_IMPLEMENTATION) || defined(RWMEM_HEADER_ONLY)

#if defined(__APPLE__) || defined(__linux__)
#include <stdlib.h>
#define RWMEM_POSIX_MEMALIGN_AVAILABLE
#elif defined(_WIN32)
#include <alloc.h>
#define RWMEM_ALIGNED_MALLOC_AVAILABLE
#else
#include <stdlib.h>
#include <malloc.h>
#endif

// Aligned memory allocation to the heap
// Alignment must be a power of 2 and multiple of sizeof(void *)
RWMEM_DEF void *rwmem_aligned_alloc(size_t size, size_t alignment) {
  void *result;
#if defined(RWMEM_POSIX_MEMALIGN_AVAILABLE)
  posix_memalign(&result, alignment, size);
#elif defined(RWMEM_ALIGNED_MALLOC_AVAILABLE)
  result = _aligned_malloc(size, alignment)
#else
  memalign(&result, alignment, size);
#endif
  return result;
}

RWMEM_DEF void rwmem_aligned_free(void *p) {
  if (!p) return;
#if defined(RWMEM_ALIGNED_MALLOC_AVAILABLE)
  _aligned_free(p);
#else
  free(p);
#endif
}

RWMEM_DEF MemoryArena rwmem_arena_create(size_t block_size_bytes) {
  MemoryArena result;
  result.block_size_bytes = block_size_bytes;
  result.cur_block_pos = 0;
  result.cur_alloc_size = 0;
  result.cur_block_ptr = NULL;
  result.used_blocks_node = NULL;
  result.available_blocks_node = NULL;
  return result;
}

RWMEM_DEF void *rwmem_arena_alloc(MemoryArena *arena, size_t bytes) {
  // NOTE(ray): Round up requested bytes to align. Safer.
  bytes = ALIGN16(bytes);

  if (arena->cur_block_pos + bytes > arena->cur_alloc_size) {
    // The number of bytes we have requested exceed the current block size.
    // So add this block to the used blocks list
    if (arena->cur_block_ptr != NULL) {
      // TODO(ray): MAKE THIS NOT USE A LINKED LIST!!!
      // Traverse to the end of the list so we can add a new node
      if (arena->used_blocks_node == NULL) {
        arena->used_blocks_node = (MA_BookkeepingNode *) rwmem_aligned_alloc(sizeof(MA_BookkeepingNode), 16);
        arena->used_blocks_node->cur_alloc_size = arena->cur_alloc_size;
        arena->used_blocks_node->block_ptr = arena->cur_block_ptr;
        arena->used_blocks_node->next = NULL;
      } else {
        MA_BookkeepingNode *cur_used_blocks_node = arena->used_blocks_node;
        while (cur_used_blocks_node->next != NULL) {
          cur_used_blocks_node = cur_used_blocks_node->next;
        }
        cur_used_blocks_node->next = (MA_BookkeepingNode *) rwmem_aligned_alloc(sizeof(MA_BookkeepingNode), 16);
        cur_used_blocks_node->next->cur_alloc_size = arena->cur_alloc_size;
        cur_used_blocks_node->next->block_ptr = arena->cur_block_ptr;
        cur_used_blocks_node->next->next = NULL;
      }
      // Set the current block pointer to NULL. Will be creating a new one below.
      arena->cur_block_ptr = NULL;
    }

    // Try to first get a block from the available blocks
    // NOTE(ray): This code path won't be taken unless the arena is reset via rwmem_arena_reset(arena)
    MA_BookkeepingNode *cur_available_blocks_node = arena->available_blocks_node;
    MA_BookkeepingNode *prev_available_blocks_node = NULL;
    while (cur_available_blocks_node != NULL) {
      // TODO(ray): MAKE THIS NOT USE A LINKED LIST!!!
      // Find the first available block that can hold requested bytes
      if (cur_available_blocks_node->cur_alloc_size >= bytes) {
        arena->cur_alloc_size = cur_available_blocks_node->cur_alloc_size;
        arena->cur_block_ptr = cur_available_blocks_node->block_ptr;
        // Remove this block from the available blocks list and free
        if (prev_available_blocks_node != NULL) { // Delete middle
          prev_available_blocks_node->next = cur_available_blocks_node->next;
        } else if (cur_available_blocks_node->next) { // Delete front
          arena->available_blocks_node = cur_available_blocks_node->next;
        } else { // Only 1 element
          arena->available_blocks_node = NULL;
        }
        rwmem_aligned_free(cur_available_blocks_node);
        break;
      }
      prev_available_blocks_node = cur_available_blocks_node;
      cur_available_blocks_node = cur_available_blocks_node->next;
    }

    if (arena->cur_block_ptr == NULL) {
      arena->cur_alloc_size = bytes > arena->block_size_bytes ? bytes : arena->block_size_bytes;
      arena->cur_block_ptr = (uint8_t *) rwmem_aligned_alloc(arena->cur_alloc_size, 16);
    }

    arena->cur_block_pos = 0;
  }

  void *result = arena->cur_block_ptr + arena->cur_block_pos;
  arena->cur_block_pos += bytes;

  return result;
}

RWMEM_DEF void rwmem_arena_free(MemoryArena *arena) {
  rwmem_aligned_free(arena->cur_block_ptr);
  MA_BookkeepingNode *cur_used_blocks_node = arena->used_blocks_node;
  while (cur_used_blocks_node) {
    MA_BookkeepingNode *next = cur_used_blocks_node->next;
    // Free the block's memory
    rwmem_aligned_free(cur_used_blocks_node->block_ptr);
    // Free bookkeeping node
    rwmem_aligned_free(cur_used_blocks_node);
    cur_used_blocks_node = next;
  }
  MA_BookkeepingNode *cur_available_blocks_node = arena->available_blocks_node;
  while (cur_available_blocks_node) {
    MA_BookkeepingNode *next = cur_available_blocks_node->next;
    // Free the block's memory
    rwmem_aligned_free(cur_available_blocks_node->block_ptr);
    // Free bookkeeping node
    rwmem_aligned_free(cur_available_blocks_node);
    cur_available_blocks_node = next;
  }
}

// Reset offset and move all memory from used blocks to available blocks
RWMEM_DEF void rwmem_arena_reset(MemoryArena *arena) {
  arena->cur_block_pos = 0;
  MA_BookkeepingNode *cur_used_blocks_node = arena->used_blocks_node;
  if (cur_used_blocks_node == NULL) {
    cur_used_blocks_node = arena->available_blocks_node;
  } else {
    // Go to the end of used_blocks_nodes and attach available_blocks_nodes
    while (cur_used_blocks_node->next != NULL) {
      cur_used_blocks_node = cur_used_blocks_node->next;
    }
    cur_used_blocks_node->next = arena->available_blocks_node;
  }
  // Set available_block_nodes pointer to be the start of used_block_nodes
  arena->available_blocks_node = arena->used_blocks_node;
  arena->used_blocks_node = NULL;
}

#endif // #if defined(RWMEM_IMPLEMENTATION) || defined(RWMEM_HEADER_ONLY)

#endif // #ifndef __RW_MEMORY_H__
