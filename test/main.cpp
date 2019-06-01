#include <stdio.h>
#if defined(_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <assert.h>
#include "../rw_types.h"
#define RWM_IMPLEMENTATION
#include "../rw_math.h"

#include "v2_test.cpp"
#include "v3_test.cpp"
#include "v4_test.cpp"
#include "m4_test.cpp"
#include "tr_test.cpp"
#include "mem_test.cpp"

#define RWTM_IMPLEMENTATION
#include "../rw_time.h"

#define RWTH_IMPLEMENTATION
#include "../rw_th.h"
#include "th_test.cpp"

using namespace std;

int main() {
  run_rwm_v2_test();
  run_rwm_v3_test();
  run_rwm_v4_test();
  run_rwm_m4_test();
  run_rwtr_test();
  run_rwth_test();
  run_rwmem_test();

  rwtm_init();
  double now = rwtm_now();
#if defined(_WIN32)
  Sleep(1000);
#else
  sleep(1);
#endif
  printf("time: %f\n", rwtm_to_sec(rwtm_since(now)));
}
