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
// __API
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

RWMEM_DEF void *rwmem_aligned_malloc(size_t size, size_t alignment);
RWMEM_DEF void rwmem_afree(void *p);

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
RWMEM_DEF void *rwmem_aligned_malloc(size_t size, size_t alignment) {
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

RWMEM_DEF void rwmem_free(void *p) {
	if (p == NULL) return;
#if defined(ALIGNED_MALLOC_AVAILABLE)
	_aligned_free(p);
#else
	free(p);
#endif
}

typedef struct MemoryArena {
	size_t block_size_bytes;
	size_t cur_block_pos;
	size_t cur_alloc_size;
} MemoryArena;

#endif // #if defined(RWMEM_IMPLEMENTATION) || defined(RWMEM_HEADER_ONLY)

#endif // #ifndef __RW_MEMORY_H__
