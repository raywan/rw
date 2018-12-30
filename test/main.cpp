#include <stdio.h>
#include <assert.h>
#include "../rw_types.h"
#define RWM_IMPLEMENTATION
#include "../rw_math.h"

#include "foo.h"
#include "v2_test.h"
#include "v3_test.h"
#include "v4_test.h"
#include "m4_test.h"
#include "tr_test.h"

#define RWMEM_IMPLEMENTATION
#include "../rw_memory.h"

using namespace std;
int main() {
  f();
  run_v2_test();
  run_v3_test();
  run_v4_test();
  run_m4_test();
  run_tr_test();

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
