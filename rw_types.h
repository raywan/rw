/*
  FILE: rw_type.h
  VERSION: 0.1.0
  DESCRIPTION: Define or redefines common types.
  AUTHOR: Raymond Wan
  USAGE: Just include this file

  NOTE(ray): To quickly navigate through the file,
             sections and/or subsections are available to jump to.
  SECTIONS:
    1. __CORE
    2. __DEF
*/

#ifndef __RW_TYPES_H__
#define __RW_TYPES_H__

#include <stdint.h>

// Detect compiler type (for intrinsics)
#if !defined(RW_DISABLE_INTRINSICS)
#define RW_USE_INTRINSICS
#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#include <x86intrin.h>
#elif defined(__MSC_VER)
#include <intrin.h>
#endif
#endif // #if !defined(RW_DISABLE_INTRINSICS)

///////////////////////////////////////////////////////////////////////////////
// __CORE
///////////////////////////////////////////////////////////////////////////////

#if !defined(internal)
#define internal static
#endif
#define local_persist static
#define global static

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;

typedef intptr_t intptr;
typedef uintptr_t uintptr;


///////////////////////////////////////////////////////////////////////////////
// __DEF
///////////////////////////////////////////////////////////////////////////////

// NOTE(ray): I don't remember why I moved the math types into here.
// I should probably be able to move them back into rw_math.h
// Is there ever a case where I need the types and not the corresponding functions?

// NOTE(ray): Be able to only include "core" types
#if !defined(RWTYPES_CORE_ONLY)

typedef union Vec2 {
  struct { float x, y; };
  struct { float u, v; };
  float e[2];
} Vec2;

typedef union Vec3 {
  struct { float x, y, z; };
  struct { float r, g, b; };
  struct { float u, v, w; };
  float e[3];
} Vec3;

typedef union Vec4 {
  struct { float x, y, z, w; };
  struct { float r, g, b, a; };
  float e[4];
#if defined(RW_USE_INTRINSICS)
  __m128 m;
#endif
} Vec4;

typedef Vec2 Point2;
typedef Vec3 Point3;
typedef Vec4 Point4;
typedef Vec3 Normal3;

typedef union Mat3 {
  // NOTE(ray): row major
  struct {
    float e00, e01, e02;
    float e10, e11, e12;
    float e20, e21, e22;
  };
  float e[3][3];
} Mat3;

typedef union Mat4 {
  struct {
    float e00, e01, e02, e03;
    float e10, e11, e12, e13;
    float e20, e21, e22, e23;
    float e30, e31, e32, e33;
  };
  float e[4][4];
#if defined(RW_USE_INTRINSICS)
  __m128 row[4];
#endif
} Mat4;

typedef union Quaternion {
  // xi + yj + zk + w
  struct { float x, y, z, w; };
  float e[4];
} Quaternion;

typedef struct Transform {
  Mat4 t;
  Mat4 t_inv;
} Transform;

typedef union Rect2 {
  struct {
    Vec2 min_p;
    Vec2 max_p;
  };
  struct {
    float min_px, min_py;
    float max_px, max_py;
  };
  // NOTE(ray): idx 0 is the min point, and idx 1 is the max point
  Vec3 p[2];
} Rect2;

typedef union Rect3 {
  struct {
    Vec3 min_p;
    Vec3 max_p;
  };
  struct {
    float min_px, min_py, min_pz;
    float max_px, max_py, max_pz;
  };
  // NOTE(ray): idx 0 is the min point, and idx 1 is the max point
  Vec3 p[2];
} Rect3;

#endif // #if !defined(RWTYPES_CORE_ONLY)

#endif // #ifndef __RW_TYPES_H__
