#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "../rw_types.h"
#define RWM_IMPLEMENTATION
#include "../rw_math.h"

#include "v2_test.cpp"
#include "v3_test.cpp"
#include "v4_test.cpp"
#include "m4_test.cpp"
#include "tr_test.cpp"

#define RWMEM_IMPLEMENTATION
#include "../rw_memory.h"

#define RWTM_IMPLEMENTATION
#include "../rw_time.h"

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

  rwtm_init();
  double now = rwtm_now();
  sleep(5);
  printf("time: %f\n", rwtm_to_sec(rwtm_since(now)));
}
