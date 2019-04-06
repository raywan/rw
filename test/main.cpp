#include <stdio.h>
#include <assert.h>
#include "../rw_types.h"
#define RWM_IMPLEMENTATION
#include "../rw_math.h"

#include "v2_test.h"
#include "v3_test.h"
#include "v4_test.h"
#include "m4_test.h"
#include "tr_test.h"

#define RWMEM_IMPLEMENTATION
#include "../rw_memory.h"

using namespace std;

int main() {
  run_rwm_v2_test();
  run_rwm_v3_test();
  run_rwm_v4_test();
  run_rwm_m4_test();
  run_rwtr_test();

  char *p = (char *) rwmem_aligned_malloc(19, 8);
  assert(IS_ALIGNED(p, 8));
  printf("%p\n", p);
  for (int i = 0; i < 19; i++) {
    p[i] = 'a';
  }
  p[18] = '\0';
  printf("%s\n", p);
  rwmem_free(p);
}
