#include <iostream>
#include <assert.h>
#include "../rw_types.h"
#define RWM_IMPLEMENTATION
#include "../rw_math.h"
#include "foo.h"
#define RWMEM_IMPLEMENTATION
#include "../rw_memory.h"

using namespace std;
int main() {
  f();
  cout << "Hello world" << endl;
  Vec2 v = v2_zero();
  Vec3 v2 = v3_init(1.0, 2.0, 3.0);
  Vec3 v3 = v3_init(1.0, 2.0, 3.0);
  float c = clamp(0.0, -1.0f, 2.0);
  assert(c == 0.0);
  c = clamp(-1.0, 0.0f, 2.0);
  assert(c == 0.0);
  c = clamp(-1.0, 3.0f, 2.0);
  assert(c == 2.0);

  v2_puts(&v);
  v3_puts(&v2);
  v3_puts(&v3);
  Vec3 a = (v2 + v3)*2.0;
  v3_puts(&a);
  printf("%f\n", v3_length(a));
  a = v3_normalize(a);
  v3_printf("normalized", &a);

  Vec4 v4 = v4_init(1.0, 2.0, 3.0, 4.0);
  Vec4 v4_2 = v4_init(1.0, 2.0, 3.0, 4.0);
  v4_printf("v4", &v4);
  Vec4 result = v4 + v4_2;
  v4_printf("v4 + v4_2", &result);
  result = v4_subtract(v4, v4_2);
  v4_printf("v4 - v4_2", &result);
  result = v4_lerp(v4, 0.5, v4_2);
  v4_printf("lerp(v4, 0.5, v4_2)", &result);

  int *arr = (int *) malloc(1);
  for (int i = 0; i < 1; i++) {
    arr[i] = 1;
  }

  char *p = (char *) rw_aligned_malloc(19, 8);
  assert(IS_ALIGNED(p, 8));
  printf("%p\n", p);
  for (int i = 0; i < 19; i++) {
    p[i] = 'a';
  }
  p[18] = '\0';
  printf("%s\n", p);
  rw_free(p);
}
