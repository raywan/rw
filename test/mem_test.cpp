#define RWMEM_IMPLEMENTATION
#include "../rw_memory.h"

struct MemTest {
	float a;
	int b;
	char c;
};

void create_blah(MemoryArena *arena, float a, int b, char c) {
  MemTest *blah = (MemTest *) rwmem_arena_alloc(arena, sizeof(MemTest));
  blah->a = a;
  blah->b = b;
  blah->c = c;
  printf("%f %d %c\n", blah->a, blah->b, blah->c);
}

void mem_test() {
  char *p = (char *) rwmem_aligned_alloc(19, 8);
  assert(IS_ALIGNED(p, 8));
  printf("%p\n", p);
  for (int i = 0; i < 19; i++) {
    p[i] = 'a';
  }
  p[18] = '\0';
  printf("%s\n", p);
  rwmem_aligned_free(p);

  MemoryArena arena = rwmem_arena_create(0);
  create_blah(&arena, 2.0, 3, 'a');
  create_blah(&arena, 4.0, 4, 'b');
  rwmem_arena_free(&arena);
}
