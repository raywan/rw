/*
  FILE: rw_memory.h
  VERSION: 0.1.0
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

typedef struct MemoryArena {
  size_t block_size_bytes;
  size_t cur_block_pos;
  size_t cur_alloc_size;
  uint8_t *cur_block;
  Block *used_blocks_node;
  Block *available_blocks_node;
} MemoryArena;

typedef struct Block {
  uint8_t *p;
  size_t cur_alloc_size;
  Block *next;
};

///////////////////////////////////////////////////////////////////////////////
// __API
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

RWMEM_DEF void *rwmem_aligned_alloc(size_t size, size_t alignment);
RWMEM_DEF void rwmem_free(void *p);

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


///////////////////////////////////////////////////////////////////////////////
// __IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////

#if defined(RWMEM_IMPLEMENTATION) || defined(RWMEM_HEADER_ONLY)

#if defined(__APPLE__) || defined(__linux__)
#include <stdlib.h>
#define RWMEM_POSIX_MEMALIGN_AVAILABLE
#elif defined(__MSC_VER)
#include <alloc.h>
#define RWMEM_ALIGNED_MALLOC_AVAILABLE
#else
#include <stdlib.h>
#include <malloc.h>
#endif

// Aligned memory allocation to the heap
// alignment must be a power of 2 and multiple of sizeof(void *)
RWMEM_DEF void *rwmem_aligned_alloc(size_t size, size_t alignment) {
	void *result;
#if defined(RWMEM_POSIX_MEMALIGN_AVAILABLE)
	posix_memalign(&result, alignment, size);
#elif defined(ALIGNED_MALLOC_AVAILABLE)
	result = _aligned_malloc(size, alignment)
#else
	memalign(&result, alignment, size);
#endif
	return result;
}

RWMEM_DEF void rwmem_aligned_free(void *p) {
	if (p == NULL) return;
#if defined(ALIGNED_MALLOC_AVAILABLE)
	_aligned_free(p);
#else
	free(p);
#endif
}

RWMEM_DEF MemoryArena rwmem_arena_create(size_t block_size_bytes) {
  MemoryArena result;
  result.block_size_bytes = 262144;
  result.block_size_bytes = block_size_bytes;
  result.cur_block_pos = 0;
  result.cur_alloc_size = 0;
  result.cur_block = NULL;
  return result;
}

RWMEM_DEF void *rwmem_arena_alloc(MemoryArena *arena, size_t bytes) {
  // NOTE(ray): Round up requested bytes to align. Safer.
  bytes = ALIGN16(bytes);
  if (arena->cur_block_pos + bytes > arena->cur_alloc_size) {
    if (arena->cur_block) {
      // Get the next empty node
      Block *cur_used_blocks_node = arena->used_block_node;
      while (cur_used_blocks_node) cur_used_blocks_node = cur_used_blocks_node->next;
      cur_used_blocks_node = (Block *) rwmem_aligned_alloc(sizeof(Block), 16);
      cur_used_blocks_node->cur_alloc_size = arena->cur_alloc_size;
      cur_used_blocks_node->p = arena->cur_block;
      arena->cur_block = NULL;
    }
    Block *cur_available_blocks_node = arena->used_block_node;
    while (cur_available_blocks_node) {
      if (cur_available_blocks_node->cur_alloc_size >= bytes) {
        arena->cur_alloc_size = cur_available_blocks_node->cur_alloc_size;
        arena->cur_block = cur_available_blocks_node->p;
        rwm
        break;
      }
      cur_used_blocks_node = cur_used_blocks_node->next;
    }

    if (!arena->cur_block) {
      arena->cur_alloc_size = bytes > arena->block_size_bytes ? bytes : arena->block_size_bytes;
      arena->cur_block = (uint8_t) rwmem_aligned_alloc(arena->cur_alloc_size);
    }

    arena->cur_block_pos = 0;
  }
  void *result = arena->cur_block + arena->cur_block_pos;
  arena->cur_block_pos += bytes;
  return result;
}

RWMEM_DEF void rwmem_arena_free(MemoryArena *arena) {
}

#endif // #if defined(RWMEM_IMPLEMENTATION) || defined(RWMEM_HEADER_ONLY)

#endif // #ifndef __RW_MEMORY_H__
