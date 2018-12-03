// This is a test file

#ifndef __RW_TEST_H__
#define __RW_TEST_H__

#ifdef RW_STATIC
#define RWDEF static
#else
#define RWDEF extern
#endif

#ifdef __cplusplus
extern "C" {
#endif
  RWDEF void rw_test();
#ifdef __cplusplus
}
#endif

#ifdef RW_IMPL
#include <stdio.h>
RWDEF void rw_test() {
  puts("test");
}

#endif

#endif
