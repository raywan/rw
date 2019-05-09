/*
  FILE: rw_th.h
  VERSION: 0.1.0
  DESCRIPTION: Multithreading related functions.
  AUTHOR: Raymond Wan
  USAGE: Simply including the file will only give you declarations (see __API)
    To include the implementation,
      #define RWTH_IMPLEMENTATION

  NOTE(ray): To quickly navigate through the file,
             sections and/or subsections are available to jump to.
  SECTIONS:
    1. __TYPES
    2. __API
    4. __IMPLEMENTATION
*/

#ifndef __RW_TH_H__
#define __RW_TH_H__

#if defined(RWTH_STATIC)
  #define RWTH_DEF static
#elif defined(RWTH_HEADER_ONLY)
  #define RWTH_DEF static inline
#else
  #define RWTH_DEF extern
#endif

#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#include <x86intrin.h>
#define NOT_MSCV
#elif defined(__MSC_VER)
#include <intrin.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// __TYPES
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// __API
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

RWTH_DEF int64_t rwth_atomic_add_i64(int64_t volatile *val, int64_t addend);
RWTH_DEF int64_t rwth_atomic_exchange_i64(int64_t volatile *val, int64_t new_val);
RWTH_DEF int64_t rwth_atomic_cas_i64(int64_t volatile *val, int64_t expected, int64_t new_val);

#ifdef __cplusplus
}
#endif


///////////////////////////////////////////////////////////////////////////////
// __IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////

#if defined(RWTH_IMPLEMENTATION) || defined(RWTH_HEADER_ONLY)

RWTH_DEF int64_t rwth_atomic_add_i64(int64_t volatile *val, int64_t addend) {
  int64_t result;
#if defined(NOT_MSCV)
  result = __sync_fetch_and_add(val, addend);
#else
  // NOTE(ray): This returns the value prior to adding
  result = _InterlockedExchangeAdd64(val, addend);
#endif
  return result;
}

RWTH_DEF int64_t rwth_atomic_exchange_i64(int64_t volatile *val, int64_t new_val) {
  int64_t result;
#if defined(NOT_MSCV)
  result = __sync_lock_test_and_set(val, new_val);
#else
  // NOTE(ray): This returns the value prior to exchange
  result = _InterlockedExchange64(val, new_val);
#endif
  return result;
}

RWTH_DEF int64_t rwth_atomic_cas_i64(int64_t volatile *val, int64_t expected, int64_t new_val) {
  int64_t result;
#if defined(NOT_MSCV)
  result = __sync_val_compare_and_swap(val, expected, new_val);
#elif
  // NOTE(ray): This returns the value prior to exchange
  result = _InterlockedCompareExchange64(val, expected, new_val);
#endif
  return result;
}

#endif // #ifdef RWTH_IMPLEMENTATION

#endif // #ifndef __RW_TH_H__
