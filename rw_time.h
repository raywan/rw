/*
  FILE: rw_time.h
  VERSION: 0.2.0
  DESCRIPTION: High resolution timer (nanoseconds) and related utilities
  AUTHOR: Raymond Wan
  USAGE: Simply including the file will only give you declarations (see __API)
    To include the implementation,
      #define RWTM_IMPLEMENTATION

  NOTE(ray): To quickly navigate through the file,
             sections and/or subsections are available to jump to.
  SECTIONS:
    1. __TYPES
    2. __API
    3. __MACROS
    4. __IMPLEMENTATION
      4.1. __INIT
      4.2. __CORE
      4.3. __UTILITY
      4.4. __CONVERSION
*/

#ifndef __RW_TIME_H__
#define __RW_TIME_H__

#if defined(RWTM_STATIC)
  #define RWTM_DEF static
#elif defined(RWTM_HEADER_ONLY)
  #define RWTM_DEF static inline
#else
  #define RWTM_DEF extern
#endif

///////////////////////////////////////////////////////////////////////////////
// __TYPES
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#if defined(__APPLE__) && defined(__MACH__)
  // Use the high performance timer for Apple devices (if available)
  #include <mach/mach_time.h>
#elif defined(_WIN32)
  #include <windows.h>
#else
  #include <time.h>
#endif

typedef struct rwtm_timer {
#if defined(__APPLE__) && defined(__MACH__)
  mach_timebase_info_data_t timebase;
  uint64_t start_ticks;
#elif defined(_WIN32)
  LARGE_INTEGER start_counter;
  LARGE_INTEGER freq;
#else
  uint64_t start_ns;
#endif
} rwtm_timer;

static rwtm_timer _timer;

///////////////////////////////////////////////////////////////////////////////
// __MACROS
///////////////////////////////////////////////////////////////////////////////

#define SECS_TO_MILLI(secs) ((uint64_t) secs * 1000)
#define SECS_TO_MICRO(secs) ((uint64_t) secs * 1000000)
#define SECS_TO_NANO(secs) ((uint64_t) secs * 1000000000)

///////////////////////////////////////////////////////////////////////////////
// __API
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

// __INIT

// Initialize the internal timer
RWTM_DEF void rwtm_init();

// __TIMER

// Returns the current time since intializing the timer (in nanoseconds)
RWTM_DEF uint64_t rwtm_now();

// __UTILITY
RWTM_DEF uint64_t rwtm_diff(int64_t end, int64_t start);
RWTM_DEF uint64_t rwtm_since(int64_t start);

// TODO(ray): Implement these
RWTM_DEF uint64_t rwtm_mark();
RWTM_DEF uint64_t rwtm_window_avg();

// __CONVERSION
RWTM_DEF double rwtm_to_sec(uint64_t ns);
RWTM_DEF double rwtm_to_ms(uint64_t ns);
RWTM_DEF double rwtm_to_us(uint64_t ns);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// __IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////

#if defined(RWTM_IMPLEMENTATION) || defined(RWTM_HEADER_ONLY)

///////////////////////////////////////////////////////////////////////////////
// __INIT
///////////////////////////////////////////////////////////////////////////////

RWTM_DEF void rwtm_init() {
#if defined(__APPLE__) && defined(__MACH__)
  mach_timebase_info(&_timer.timebase);
  _timer.start_ticks = mach_absolute_time();
#elif defined(_WIN32)
  // NOTE(ray): QueryPerformanceFrequency returns counts per second
  // https://msdn.microsoft.com/en-us/library/windows/desktop/ms644904(v=vs.85).aspx
  // https://msdn.microsoft.com/en-us/library/windows/desktop/ms644905(v=vs.85).aspx
  // The frequncy returned is in COUNTS PER SECOND
  QueryPerformanceFrequency(&_timer.freq);
  QueryPerformanceCounter(&_timer.start_counter);
#else
  // NOTE(ray): https://linux.die.net/man/3/clock_gettime
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  // Store the highest resolution time we can i.e nanoseconds
	_timer.start_ns = SECS_TO_NANO(tp.tv_sec) + tp.tv_nsec;
#endif
}

///////////////////////////////////////////////////////////////////////////////
// __CORE
///////////////////////////////////////////////////////////////////////////////

static int64_t rwtm__mul_div_i64(int64_t t, int64_t numer, int64_t denom) {
  // NOTE(ray): We want to perform t * (numer/denom)
  // https://en.wikipedia.org/wiki/Euclidean_division
  // Let n = numer, d = denom
  // We want to compute t * (n/d). (1)
  // Via quotient and remainder, let q = t/d and let r = t mod d. So t = q*d + r. (2)
  // Substitute (2) into (1) to get (q*d + r)(n/d)
  // Thus, the final calculation is q*n + r*(n/d)
  int64_t q = t / denom;
  int64_t r = t % denom;
  return (q * numer) + (r * numer) / denom;
}

RWTM_DEF uint64_t rwtm_now() {
  uint64_t cur_time;
#if defined(__APPLE__) && defined(__MACH__)
  // NOTE(ray): https://shiftedbits.org/2008/10/01/mach_absolute_time-on-the-iphone/
  cur_time = rwtm__mul_div_i64(mach_absolute_time() - _timer.start_ticks, _timer.timebase.numer, _timer.timebase.denom);
#elif defined(_WIN32)
  // NOTE(ray): https://docs.microsoft.com/en-us/windows/desktop/SysInfo/acquiring-high-resolution-time-stamps
  LARGE_INTEGER count;
  QueryPerformanceCounter(&count);
  cur_time = rwtm__mul_div_i64(count.QuadPart - _timer.start_counter.QuadPart, 1000000000 /* ns/sec */, _timer.freq.QuadPart);
#else
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  cur_time = (SECS_TO_NANO(tp.tv_sec) + tp.tv_nsec) - _timer.start_ns;
#endif
  return cur_time;
}

///////////////////////////////////////////////////////////////////////////////
// __UTILITY
///////////////////////////////////////////////////////////////////////////////

RWTM_DEF uint64_t rwtm_diff(int64_t end, int64_t start) {
  return end < start ? 0 : end - start;
}

RWTM_DEF uint64_t rwtm_since(int64_t start) {
  return rwtm_diff(rwtm_now(), start);
}

///////////////////////////////////////////////////////////////////////////////
// __CONVERSION
///////////////////////////////////////////////////////////////////////////////

RWTM_DEF double rwtm_to_sec(uint64_t ns) {
  return (double) ns / 1000000000.0;
}

RWTM_DEF double rwtm_to_ms(uint64_t ns) {
  return (double) ns / 1000000.0;
}

RWTM_DEF double rwtm_to_us(uint64_t ns) {
  return (double) ns / 1000.0;
}

#endif // #ifdef RWTM_IMPLEMENTATION

#endif // #ifndef __RW_TIME_H__
