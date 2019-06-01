#define RWMEM_IMPLEMENTATION
#include "../rw_memory.h"

struct BigTest {
	float a;
	int b;
	char c;
	char big[512];
};

struct SmallTest {
	float a;
	int b;
	char c;
};

BigTest *create_big(MemoryArena *arena, float a, int b, char c) {
  BigTest *result = (BigTest *) rwmem_arena_alloc(arena, sizeof(BigTest));
  result->a = a;
  result->b = b;
  result->c = c;
  return result;
}

SmallTest *create_small(MemoryArena *arena, float a, int b, char c) {
  SmallTest *result = (SmallTest *) rwmem_arena_alloc(arena, sizeof(SmallTest));
  result->a = a;
  result->b = b;
  result->c = c;
  return result;
  printf("%f %d %c\n", result->a, result->b, result->c);
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

  BigTest *bt_ptrs[7];
  SmallTest *st_ptrs[2];
  MemoryArena arena = rwmem_arena_create(600);
  bt_ptrs[0] = create_big(&arena, 1.0, 3, 'a');
  st_ptrs[0] = create_small(&arena, 99.0, 3, 'x');
  bt_ptrs[1] = create_big(&arena, 2.0, 6, 'b');
  bt_ptrs[2] = create_big(&arena, 2.0, 6, 'b');
  st_ptrs[1] = create_small(&arena, 99.0, 3, 'x');
  for (int i = 0; i < 3; i++) {
	  printf("%f %d %c\n", bt_ptrs[i]->a, bt_ptrs[i]->b, bt_ptrs[i]->c);
  }
  for (int i = 0; i < 2; i++) {
	  printf("%f %d %c\n", st_ptrs[i]->a, st_ptrs[i]->b, st_ptrs[i]->c);
  }
  rwmem_arena_reset(&arena);
  bt_ptrs[0] = create_big(&arena, 4.4, 12, 'c');
  bt_ptrs[1] = create_big(&arena, 5.0, 13, 'd');
  bt_ptrs[2] = create_big(&arena, 6.0, 14, 'e');
  bt_ptrs[3] = create_big(&arena, 7.0, 15, 'f');
  for (int i = 0; i < 3; i++) {
	  printf("%f %d %c\n", bt_ptrs[i]->a, bt_ptrs[i]->b, bt_ptrs[i]->c);
  }
  rwmem_arena_free(&arena);
}
