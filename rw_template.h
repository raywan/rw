///////////////////////////////////////////////////////////////////////////////
// NOTE(ray): Template file to create other libraries.
//            Global replace MYLIB with the library name e.g. MATH.
//            Global replace RWNAMESPACE with the namespace e.g. RWM.
//            Edit file header.
///////////////////////////////////////////////////////////////////////////////

/*
  FILE: rw_MYLIBFILENAME.h
  VERSION: 0.1.0
  DESCRIPTION: My awesome description.
  AUTHOR: Raymond Wan
  USAGE: Very clear usage instructions.

  NOTE(ray): To quickly navigate through the file,
             sections and/or subsections are available to jump to.
  SECTIONS:
    1. __TYPES
    2. __API
    3. __MACROS
    4. __IMPLEMENTATION
*/

#ifndef __RW_MYLIB_H__
#define __RW_MYLIB_H__

#if defined(RWNAMESPACE_STATIC)
  #define RWNAMESPACE_DEF static
#elif defined(RWNAMESPACE_HEADER_ONLY)
  #define RWNAMESPACE_DEF static inline
#else
  #define RWNAMESPACE_DEF extern
#endif

///////////////////////////////////////////////////////////////////////////////
// __TYPES
///////////////////////////////////////////////////////////////////////////////

#ifndef RWNAMESPACE_STANDALONE
#include "rw_types.h"
#endif

#if defined(RWNAMESPACE_STANDALONE) || !defined(__RW_TYPES_H__)
// TODO(ray): Paste the definitions of types here from rw_types.h
#endif // #if defined(RWNAMESPACE_STANDALONE) && !defined(__RW_TYPES_H__)

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
// __MACROS
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// __IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////

#if defined(RWNAMESPACE_IMPLEMENTATION) || defined(RWNAMESPACE_HEADER_ONLY)


#endif // #ifdef RWNAMESPACE_IMPLEMENTATION

#endif // #ifndef __RW_MYLIB_H__
