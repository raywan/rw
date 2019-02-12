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

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float r32;
typedef double r64;

typedef intptr_t intptr;
typedef uintptr_t uintptr;

///////////////////////////////////////////////////////////////////////////////
// __DEF
///////////////////////////////////////////////////////////////////////////////

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
  // idx 0 is the min point, and idx 1 is the max point
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
  // idx 0 is the min point, and idx 1 is the max point
  Vec3 p[2];
} Rect3;

#endif
