#ifndef __RW_TYPES_H__
#define __RW_TYPES_H__

#include <stdint.h>

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
} Vec4;

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
} Mat4;

typedef union Quaternion {
  // xi + yj + zk + w
  struct { float x, y, z, w; };
  float e[4];
} Quaternion;

typedef struct Transform {
  Mat4 m;
  Mat4 m_inv;
} Transform;

typedef union Rect2 {
  float min_px, min_py, max_px, max_py;
  struct {
    Vec2 min_p;
    Vec2 max_p;
  };
} Rect2;

typedef union Rect3 {
  float min_px, min_py, min_pz, max_px, max_py, max_pz;
  struct {
    Vec3 min_p;
    Vec3 max_p;
  };
} Rect3;

#endif
