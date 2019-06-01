#include <assert.h>
#if !defined(_WIN32)
#include <pthread.h>
#endif
#include <stdio.h>
#include "../rw_th.h"

#define NUM_THREADS 5
#define EXPECTED_RESULT 500

static int64_t val = 0;

#if defined(_WIN32)
void run_rwth_test() {}
#else

void *add_func(void *t) {
  for (int i = 0; i < 100; i++) {
    rwth_atomic_add_i64(&val, 1);
  }
  pthread_exit(NULL);
}

void run_rwth_test() {
	printf("run_rwth_test");
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;
  for (int i = 0; i < NUM_THREADS; i++) {
    rc = pthread_create(&threads[i], NULL, add_func, (void *) t);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  void *status;
  for (int i = 0; i < NUM_THREADS; i++) {
    rc = pthread_join(threads[i], &status);
    if (rc) {
      printf("ERROR; return code from pthread_join() is %d\n", rc);
      exit(-1);
    }
  }
  assert(val == EXPECTED_RESULT);
	printf(" - PASSED\n");
}
#endif
