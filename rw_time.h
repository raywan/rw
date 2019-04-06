/*
  FILE: rw_time.h
  VERSION: 0.1.0
  DESCRIPTION: High resolution timer.
  AUTHOR: Raymond Wan
  USAGE: Simply including the file will only give you declarations (see __API)
    To include the implementation,
      #define RWT_IMPLEMENTATION

  NOTE(ray): To quickly navigate through the file,
             sections and/or subsections are available to jump to.
  SECTIONS:
    1. __TYPES
    2. __API
    3. __MACROS
    4. __IMPLEMENTATION
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

#ifndef RWTM_STANDALONE
#include "rw_types.h"
#endif

#if defined(RWTM_STANDALONE) || !defined(__RW_TYPES_H__)
// TODO(ray): Paste the definitions of types here from rw_types.h
#endif // #if defined(RWTM_STANDALONE) && !defined(__RW_TYPES_H__)

///////////////////////////////////////////////////////////////////////////////
// __API
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

// FORWARD DECLARATIONS HERE

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// __IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////

#if defined(RWTM_IMPLEMENTATION) || defined(RWTM_HEADER_ONLY)


#endif // #ifdef RWTM_IMPLEMENTATION

#endif // #ifndef __RW_TIME_H__
