/*
  FILE: rw_math.h
  VERSION: 0.2.0
  DESCRIPTION: Math library for games/graphics.
  AUTHOR: Raymond Wan
  USAGE: Simply including the file will only give you declarations (see __API)
    To include the implementation,
      #define RWM_IMPLEMENTATION
    OR if you want this to be header only,
      #define RWM_HEADER_ONLY
    To use the fast inverse sqrt intrinsic, also include before
      #define RWM_USE_MM_RSQRT

  NOTE(ray): To quickly navigate through the file,
             sections and/or subsections are available to jump to.
  SECTIONS:
    1. __MACROS
    2. __TYPES
    3. __API
    4. __IMPLEMENTATION
      4.1. __VEC2
      4.2. __VEC3
      4.3. __VEC4
      4.4. __MAT4
      4.5. __QUATERNION
      4.6. __RECT2
      4.7. __RECT3
*/

#ifndef __RW_MATH_H__
#define __RW_MATH_H__

// Detect compiler type (for intrinsics)
#if !defined(RW_DISABLE_INTRINSICS)
#define RW_USE_INTRINSICS
#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#include <x86intrin.h>
#elif defined(__MSC_VER)
#include <intrin.h>
#endif
#endif // #if !defined(RW_DISABLE_INTRINSICS)

#if defined(RWM_STATIC)
  #define RWM_DEF static
#elif defined(RWM_HEADER_ONLY)
  #define RWM_DEF static inline
#else
  #define RWM_DEF extern
#endif


///////////////////////////////////////////////////////////////////////////////
// __TYPES
///////////////////////////////////////////////////////////////////////////////

#if !defined(RWM_STANDALONE)
#include "rw_types.h"
#endif

#if defined(RWM_STANDALONE) || !defined(__RW_TYPES_H__)
// TODO(ray): Paste the definitions of types here from rw_types.h
#endif // #if defined(RWM_STANDALONE) && !defined(__RW_TYPES_H__)

///////////////////////////////////////////////////////////////////////////////
// __API
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

// __UTILITY
RWM_DEF float rwm_lerp(float a, float t, float b);
RWM_DEF float rwm_clamp(float lower, float val, float upper);
RWM_DEF float rwm_clamp01(float val);
RWM_DEF float rwm_to_radians(float degrees);
RWM_DEF float rwm_to_degrees(float radians);
RWM_DEF float rwm_sqrt(float val);
RWM_DEF float rwm_rsqrt(float val);

// __VEC2
RWM_DEF void rwm_v2_puts(Vec2 *v);
RWM_DEF void rwm_v2_printf(const char *label, Vec2 *v);
RWM_DEF Vec2 rwm_v2_init(float x, float y);
RWM_DEF Vec2 rwm_v2_zero();
RWM_DEF Vec2 rwm_v2_add(Vec2 a, Vec2 b);
RWM_DEF Vec2 rwm_v2_subtract(Vec2 a, Vec2 b);
RWM_DEF Vec2 rwm_v2_scalar_mult(float a, Vec2 v);
RWM_DEF Vec2 rwm_v2_scalar_div(Vec2 v, float a);
RWM_DEF float rwm_v2_length_squared(Vec2 v);
RWM_DEF float rwm_v2_length(Vec2 v);
RWM_DEF Vec2 rwm_v2_normalize(Vec2 v);
RWM_DEF Vec2 rwm_v2_hadamard(Vec2 a, Vec2 b);
RWM_DEF float rwm_v2_inner(Vec2 a, Vec2 b);
RWM_DEF Vec2 rwm_v2_lerp(Vec2 a, float t, Vec2 b);

// __VEC3
RWM_DEF void rwm_v3_puts(Vec3 *v);
RWM_DEF void rwm_v3_printf(const char *label, Vec3 *v);
RWM_DEF Vec3 rwm_v3_init(float x, float y, float z);
RWM_DEF Vec3 rwm_v3_zero();
RWM_DEF Vec3 rwm_v3_add(Vec3 a, Vec3 b);
RWM_DEF Vec3 rwm_v3_subtract(Vec3 a, Vec3 b);
RWM_DEF Vec3 rwm_v3_scalar_mult(float a, Vec3 v);
RWM_DEF Vec3 rwm_v3_scalar_div(Vec3 v, float a);
RWM_DEF float rwm_v3_length_squared(Vec3 v);
RWM_DEF float rwm_v3_length(Vec3 v);
RWM_DEF Vec3 rwm_v3_normalize(Vec3 v);
RWM_DEF Vec3 rwm_v3_hadamard(Vec3 a, Vec3 b);
RWM_DEF float rwm_v3_inner(Vec3 a, Vec3 b);
RWM_DEF Vec3 rwm_v3_cross(Vec3 a, Vec3 b);
RWM_DEF Vec3 rwm_v3_lerp(Vec3 a, float t, Vec3 b);

// __VEC4
RWM_DEF void rwm_v4_puts(Vec4 *v);
RWM_DEF void rwm_v4_printf(const char *label, Vec4 *v);
RWM_DEF Vec4 rwm_v4_init(float x, float y, float z, float w);
RWM_DEF Vec4 rwm_v4_zero();
RWM_DEF Vec4 rwm_v4_add(Vec4 a, Vec4 b);
RWM_DEF Vec4 rwm_v4_subtract(Vec4 a, Vec4 b);
RWM_DEF Vec4 rwm_v4_scalar_mult(float a, Vec4 v);
RWM_DEF Vec4 rwm_v4_scalar_div(Vec4 v, float a);
RWM_DEF float rwm_v4_length_squared(Vec4 v);
RWM_DEF float rwm_v4_length(Vec4 v);
RWM_DEF Vec4 rwm_v4_normalize(Vec4 v);
RWM_DEF Vec4 rwm_v4_hadamard(Vec4 a, Vec4 b);
RWM_DEF float rwm_v4_inner(Vec4 a, Vec4 b);
RWM_DEF Vec4 rwm_v4_lerp(Vec4 a, float t, Vec4 b);

// __MAT4
RWM_DEF void rwm_m4_puts(Mat4 *m);
RWM_DEF Mat4 rwm_m4_diagonal(float a);
RWM_DEF Mat4 rwm_m4_identity();
RWM_DEF Mat4 rwm_m4_init_v4(Vec4 r0, Vec4 r1, Vec4 r2, Vec4 r3);
RWM_DEF Mat4 rwm_m4_init_f(float t00, float t01, float t02, float t03, float t10, float t11, float t12, float t13, float t20, float t21, float t22, float t23, float t30, float t31, float t32, float t33);
RWM_DEF Mat4 rwm_m4_transpose(Mat4 m);
RWM_DEF float rwm_m4_trace(Mat4 m);
RWM_DEF Mat4 rwm_m4_add(Mat4 a, Mat4 b);
RWM_DEF Mat4 rwm_m4_subtract(Mat4 a, Mat4 b);
RWM_DEF Mat4 rwm_m4_scalar_mult(float a, Mat4 m);
RWM_DEF Mat4 rwm_m4_multiply(Mat4 a, Mat4 b);
RWM_DEF Mat4 rwm_m4_hadamard(Mat4 a, Mat4 b);
RWM_DEF Mat4 rwm_m4_inverse(Mat4 m);

// __QUATERNION
RWM_DEF Quaternion rwm_q_init(float x, float y, float z, float w);
RWM_DEF Quaternion rwm_q_identity();
RWM_DEF Quaternion rwm_q_init_v4(Vec4 v);
RWM_DEF float rwm_q_length(Quaternion q);

// __RECT2
RWM_DEF Rect2 rwm_r2_init_limit();
RWM_DEF Rect2 rwm_r2_init(float min_x, float min_y, float max_x, float max_y);
RWM_DEF Rect2 rwm_r2_init_v2(Vec2 min_p, Vec2 max_p);
RWM_DEF Rect2 rwm_r2_intersection(Rect2 a, Rect2 b);
RWM_DEF bool rwm_r2_overlaps(Rect2 a, Rect2 b);
RWM_DEF bool rwm_r2_pt_inside(Rect2 r, Vec2 p);
RWM_DEF bool rwm_r2_pt_inside_excl(Rect2 r, Vec2 p);
RWM_DEF Rect2 rwm_r2_expand(Rect2 r, float delta);
RWM_DEF Vec2 rwm_r2_diagonal(Rect2 r);
RWM_DEF float rwm_r2_surface_area(Rect2 r);
RWM_DEF int rwm_r2_max_extent(Rect2 r); // Returns index of the longest axis
RWM_DEF Vec2 rwm_r2_offset(Rect2 r, Vec2 p); // Returns p relative to the box

// __RECT3
RWM_DEF Rect3 rwm_r3_init_limit();
RWM_DEF Rect3 rwm_r3_init(float min_x, float min_y, float min_z, float max_x, float max_y, float max_z);
RWM_DEF Rect3 rwm_r3_init_v3(Vec3 min_p, Vec3 max_p);
RWM_DEF Rect3 rwm_r3_init_p(Point3 p);
RWM_DEF Rect3 rwm_r3_union(Rect3 r1, Rect3 r2);
RWM_DEF Rect3 rwm_r3_union_p(Rect3 r1, Point3 p);
RWM_DEF Rect3 rwm_r3_intersection(Rect3 a, Rect3 b);
RWM_DEF bool rwm_r3_overlaps(Rect3 a, Rect3 b);
RWM_DEF bool rwm_r3_pt_inside(Rect3 r, Vec3 p);
RWM_DEF bool rwm_r3_pt_inside_excl(Rect3 r, Vec3 p);
RWM_DEF Rect3 rwm_r3_expand(Rect3 r, float delta);
RWM_DEF Vec3 rwm_r3_diagonal(Rect3 r);
RWM_DEF float rwm_r3_surface_area(Rect3 r);
RWM_DEF float rwm_r3_volume(Rect3 r);
RWM_DEF int rwm_r3_max_extent(Rect3 r); // Returns index of the longest axis
RWM_DEF Vec3 rwm_r3_offset(Rect3 r, Vec3 p); // Returns p relative to the box

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
// __VEC2_op
RWM_DEF Vec2 operator+(Vec2 a, Vec2 b);
RWM_DEF Vec2 &operator+=(Vec2 &a, Vec2 b);
RWM_DEF Vec2 operator-(Vec2 a);
RWM_DEF Vec2 operator-(Vec2 a, Vec2 b);
RWM_DEF Vec2 &operator-=(Vec2 &a, Vec2 b);
RWM_DEF Vec2 operator*(float a, Vec2 v);
RWM_DEF Vec2 operator*(Vec2 v, float a);
RWM_DEF Vec2 operator*(Vec2 a, Vec2 b);
RWM_DEF Vec2 &operator*=(Vec2 &v, float a);

// __VEC3_op
RWM_DEF Vec3 operator+(Vec3 a, Vec3 b);
RWM_DEF Vec3 &operator+=(Vec3 &a, Vec3 b);
RWM_DEF Vec3 operator-(Vec3 a);
RWM_DEF Vec3 operator-(Vec3 a, Vec3 b);
RWM_DEF Vec3 &operator-=(Vec3 &a, Vec3 b);
RWM_DEF Vec3 operator*(float a, Vec3 v);
RWM_DEF Vec3 operator*(Vec3 v, float a);
RWM_DEF Vec3 operator*(Vec3 a, Vec3 b);
RWM_DEF Vec3 &operator*=(Vec3 &v, float a);

// __VEC3_op
RWM_DEF Vec4 operator+(Vec4 a, Vec4 b);
RWM_DEF Vec4 &operator+=(Vec4 &a, Vec4 b);
RWM_DEF Vec4 operator-(Vec4 a);
RWM_DEF Vec4 operator-(Vec4 a, Vec4 b);
RWM_DEF Vec4 &operator-=(Vec4 &a, Vec4 b);
RWM_DEF Vec4 operator*(float a, Vec4 v);
RWM_DEF Vec4 operator*(Vec4 v, float a);
RWM_DEF Vec4 operator*(Vec4 a, Vec4 b);
RWM_DEF Vec4 &operator*=(Vec4 &v, float a);
// TODO(ray): Add Matrix ops
#endif


///////////////////////////////////////////////////////////////////////////////
// __MACROS
///////////////////////////////////////////////////////////////////////////////

#if !defined(PI)
#define PI 3.14159265358979323846
#endif

#if !defined(INV_PI)
#define INV_PI 0.31830988618379067154
#endif

#if !defined(SQUARE)
#define SQUARE(x) ((x) * (x))
#endif

#if !defined(ABS)
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#endif

#if !defined(MIN)
#define MIN(a,b) \
  ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _b : _a; })
#endif

#if !defined(MAX)
#define MAX(a,b) \
  ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })
#endif

#if !defined(TO_RADIANS)
#define TO_RADIANS(deg) (deg * (PI/180.0f))
#endif

#if !defined(TO_DEGREES)
#define TO_DEGREES(rad) (rad * (180.0f/PI))
#endif

///////////////////////////////////////////////////////////////////////////////
// __IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////

#if defined(RWM_IMPLEMENTATION) || defined(RWM_HEADER_ONLY)

#include <math.h> // sqrt
#include <stdio.h> // printf
#include <float.h> // FLT_MAX

///////////////////////////////////////////////////////////////////////////////
// __UTILITY
///////////////////////////////////////////////////////////////////////////////

RWM_DEF float rwm_lerp(float a, float t, float b) {
  float result = ((1.0f - t) * a) + (t * b);
  return result;
}

RWM_DEF float rwm_clamp(float lower, float val, float upper) {
  if (val < lower) return lower;
  else if (val > upper) return upper;
  return val;
}

RWM_DEF float rwm_clamp01(float val) {
  float result = rwm_clamp(0.0f, val, 1.0f);
  return result;
}

RWM_DEF float rwm_to_radians(float degrees) {
  float result = degrees * (PI/180.0f);
  return result;
}

RWM_DEF float rwm_to_degrees(float radians) {
  float result = radians * (180.0f/PI);
  return result;
}

RWM_DEF float rwm_sqrt(float val) {
  float result;
#if defined(RW_USE_INTRINSICS)
  // _mm_set_ss : copy a 32 bit float to the lower element, zero the upper three
  // _mm_sqrt_ss : computes sqrt of lower 32 bit float
  // __mm_cvtss_f32 : copies lower 32 bit float to destination type (float)
  result = _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(val)));
#else
  result = sqrt(val);
#endif
  return result;
}

RWM_DEF float rwm_rsqrt(float val) {
  float result;
#if defined(RW_USE_INTRINSICS) && defined(RWM_USE_MM_RSQRT)
  result = _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(val)));
#else
  result = 1.0f/sqrt(val);
#endif
  return result;
}


///////////////////////////////////////////////////////////////////////////////
// __VEC2
///////////////////////////////////////////////////////////////////////////////

RWM_DEF void rwm_v2_puts(Vec2 *v) {
  printf("[%f, %f]\n", v->x, v->y);
}

RWM_DEF void rwm_v2_printf(const char *label, Vec2 *v) {
  printf("%s: [%f, %f]\n", label, v->e[0], v->e[1]);
}

RWM_DEF Vec2 rwm_v2_init(float x, float y) {
  Vec2 result = { x, y };
  return result;
}

RWM_DEF Vec2 rwm_v2_zero() {
  Vec2 result = { 0.0f, 0.0f };
  return result;
}

RWM_DEF Vec2 rwm_v2_add(Vec2 a, Vec2 b) {
  Vec2 result = {
    a.x + b.x,
    a.y + b.y
  };
  return result;
}

RWM_DEF Vec2 rwm_v2_subtract(Vec2 a, Vec2 b) {
  Vec2 result = {
    a.x - b.x,
    a.y - b.y
  };
  return result;
}

RWM_DEF Vec2 rwm_v2_scalar_mult(float a, Vec2 v) {
  Vec2 result = { a * v.x, a * v.y };
  return result;
}

RWM_DEF Vec2 rwm_v2_scalar_div(Vec2 v, float a) {
  // TODO(ray): Assert we're not dividing by 0
  Vec2 result = { v.x/a, v.y/a };
  return result;
}

RWM_DEF float rwm_v2_length_squared(Vec2 v) {
  return SQUARE(v.x) + SQUARE(v.y);
}

RWM_DEF float rwm_v2_length(Vec2 v) {
  return rwm_sqrt(SQUARE(v.x) + SQUARE(v.y));
}

RWM_DEF Vec2 rwm_v2_normalize(Vec2 v) {
  float inv_norm = rwm_rsqrt(rwm_v2_length_squared(v));
  Vec2 result = {
    v.x * inv_norm,
    v.y * inv_norm
  };
  return result;
}

RWM_DEF Vec2 rwm_v2_hadamard(Vec2 a, Vec2 b) {
  Vec2 result;
  result.x = a.x * b.x;
  result.y = a.y * b.y;
  return result;
}

RWM_DEF float rwm_v2_inner(Vec2 a, Vec2 b) {
  return (a.x * b.x) +
         (a.y * b.y);
}

RWM_DEF Vec2 rwm_v2_lerp(Vec2 a, float t, Vec2 b) {
  Vec2 result;
  result.x = rwm_lerp(a.x, t, b.x);
  result.y = rwm_lerp(a.y, t, b.y);
  return result;
}

// __VEC2_op
#ifdef __cplusplus
RWM_DEF Vec2 operator+(Vec2 a, Vec2 b) {
  Vec2 result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  return result;
}

RWM_DEF Vec2 &operator+=(Vec2 &a, Vec2 b) {
  a.x += b.x;
  a.y += b.y;
  return a;
}

RWM_DEF Vec2 operator-(Vec2 a) {
  Vec2 result;
  result.x = -a.x;
  result.y = -a.y;
  return result;
}

RWM_DEF Vec2 operator-(Vec2 a, Vec2 b) {
  Vec2 result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  return result;
}

RWM_DEF Vec2 &operator-=(Vec2 &a, Vec2 b) {
  a.x -= b.x;
  a.y -= b.y;
  return a;
}

RWM_DEF Vec2 operator*(float a, Vec2 v) {
  Vec2 result;
  result.x = a * v.x;
  result.y = a * v.y;
  return result;
}

RWM_DEF Vec2 operator*(Vec2 v, float a) {
  Vec2 result;
  result.x = a * v.x;
  result.y = a * v.y;
  return result;
}

RWM_DEF Vec2 operator*(Vec2 a, Vec2 b) {
  Vec2 result = rwm_v2_hadamard(a, b);
  return result;
}


RWM_DEF Vec2 &operator*=(Vec2 &v, float a) {
  v.x *= a;
  v.y *= a;
  return v;
}

#endif // #ifndef __cplusplus for Vec2

///////////////////////////////////////////////////////////////////////////////
// __VEC3
///////////////////////////////////////////////////////////////////////////////

RWM_DEF void rwm_v3_puts(Vec3 *v) {
  printf("[%f, %f, %f]\n", v->x, v->y, v->z);
}

RWM_DEF void rwm_v3_printf(const char *label, Vec3 *v) {
  printf("%s: [%f, %f, %f]\n", label, v->e[0], v->e[1], v->e[2]);
}

RWM_DEF Vec3 rwm_v3_init(float x, float y, float z) {
  Vec3 result = { x, y, z };
  return result;
}

RWM_DEF Vec3 rwm_v3_zero() {
  Vec3 result = { 0.0f, 0.0f, 0.0f };
  return result;
}

RWM_DEF Vec3 rwm_v3_add(Vec3 a, Vec3 b) {
  Vec3 result = {
    a.x + b.x,
    a.y + b.y,
    a.z + b.z
  };
  return result;
}

RWM_DEF Vec3 rwm_v3_subtract(Vec3 a, Vec3 b) {
  Vec3 result = {
    a.x - b.x,
    a.y - b.y,
    a.z - b.z
  };
  return result;
}

RWM_DEF Vec3 rwm_v3_scalar_mult(float a, Vec3 v) {
  Vec3 result = {
    a * v.x,
    a * v.y,
    a * v.z
  };
  return result;
}

RWM_DEF Vec3 rwm_v3_scalar_div(Vec3 v, float a) {
  // TODO(ray): Assert we're not dividing by 0
  Vec3 result = {
    v.x/a,
    v.y/a,
    v.z/a
  };
  return result;
}

RWM_DEF float rwm_v3_length_squared(Vec3 v) {
  return SQUARE(v.x) + SQUARE(v.y) + SQUARE(v.z);
}

RWM_DEF float rwm_v3_length(Vec3 v) {
  return rwm_sqrt(SQUARE(v.x) + SQUARE(v.y) + SQUARE(v.z));
}

RWM_DEF Vec3 rwm_v3_normalize(Vec3 v) {
  float inv_norm = rwm_rsqrt(rwm_v3_length_squared(v));
  Vec3 result = {
    v.x * inv_norm,
    v.y * inv_norm,
    v.z * inv_norm
  };
  return result;
}

RWM_DEF Vec3 rwm_v3_hadamard(Vec3 a, Vec3 b) {
  Vec3 result;
  result.x = a.x * b.x;
  result.y = a.y * b.y;
  result.z = a.z * b.z;
  return result;
}

RWM_DEF float rwm_v3_inner(Vec3 a, Vec3 b) {
  return (a.x * b.x) +
         (a.y * b.y) +
         (a.z * b.z);
}

RWM_DEF Vec3 rwm_v3_cross(Vec3 a, Vec3 b) {
  Vec3 result;
  result.x = (a.y * b.z) - (a.z * b.y);
  result.y = (a.z * b.x) - (a.x * b.z);
  result.z = (a.x * b.y) - (a.y * b.x);
  return result;
}

RWM_DEF Vec3 rwm_v3_lerp(Vec3 a, float t, Vec3 b) {
  Vec3 result;
  result.x = rwm_lerp(a.x, t, b.x);
  result.y = rwm_lerp(a.y, t, b.y);
  result.z = rwm_lerp(a.z, t, b.z);
  return result;
}

// __VEC3_op
#ifdef __cplusplus
RWM_DEF Vec3 operator+(Vec3 a, Vec3 b) {
  Vec3 result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  result.z = a.z + b.z;
  return result;
}

RWM_DEF Vec3 &operator+=(Vec3 &a, Vec3 b) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return a;
}

RWM_DEF Vec3 operator-(Vec3 a) {
  Vec3 result;
  result.x = -a.x;
  result.y = -a.y;
  result.z = -a.z;
  return result;
}

RWM_DEF Vec3 operator-(Vec3 a, Vec3 b) {
  Vec3 result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;
  return result;
}

RWM_DEF Vec3 &operator-=(Vec3 &a, Vec3 b) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return a;
}

RWM_DEF Vec3 operator*(float a, Vec3 v) {
  Vec3 result;
  result.x = a * v.x;
  result.y = a * v.y;
  result.z = a * v.z;
  return result;
}

RWM_DEF Vec3 operator*(Vec3 v, float a) {
  Vec3 result;
  result.x = a * v.x;
  result.y = a * v.y;
  result.z = a * v.z;
  return result;
}

RWM_DEF Vec3 operator*(Vec3 a, Vec3 b) {
  Vec3 result = rwm_v3_hadamard(a, b);
  return result;
}


RWM_DEF Vec3 &operator*=(Vec3 &v, float a) {
  v.x *= a;
  v.y *= a;
  v.z *= a;
  return v;
}

#endif // #ifdef __cplusplus for Vec3

///////////////////////////////////////////////////////////////////////////////
// __VEC4
///////////////////////////////////////////////////////////////////////////////

RWM_DEF void rwm_v4_puts(Vec4 *v) {
  printf("[%f, %f, %f, %f]\n", v->x, v->y, v->z, v->w);
}

RWM_DEF void rwm_v4_printf(const char *label, Vec4 *v) {
  printf("%s: [%f, %f, %f, %f]\n", label, v->x, v->y, v->z, v->w);
}

RWM_DEF Vec4 rwm_v4_init(float x, float y, float z, float w) {
  Vec4 result;
#if defined(RW_USE_INTRINSICS)
  result.m = _mm_setr_ps(x, y, z, w);
#else
  result = { x, y, z, w };
#endif
  return result;
}

RWM_DEF Vec4 rwm_v4_zero() {
  Vec4 result = { 0.0f, 0.0f, 0.0f, 0.0f };
  return result;
}

RWM_DEF Vec4 rwm_v4_add(Vec4 a, Vec4 b) {
  Vec4 result;
#if defined(RW_USE_INTRINSICS)
  result.m = _mm_add_ps(a.m, b.m);
#else
  result = {
    a.x + b.x,
    a.y + b.y,
    a.z + b.z,
    a.w + b.w
  };
#endif
  return result;
}

RWM_DEF Vec4 rwm_v4_subtract(Vec4 a, Vec4 b) {
  Vec4 result;
#if defined(RW_USE_INTRINSICS)
  result.m = _mm_sub_ps(a.m, b.m);
#else
  result = {
    a.x - b.x,
    a.y - b.y,
    a.z - b.z,
    a.w - b.w
  };
#endif
  return result;
}

RWM_DEF Vec4 rwm_v4_scalar_mult(float a, Vec4 v) {
  Vec4 result;
#if defined(RW_USE_INTRINSICS)
  result.m = _mm_mul_ps(_mm_set1_ps(a), v.m);
#else
  result = {
    a * v.x,
    a * v.y,
    a * v.z,
    a * v.w
  };
#endif
  return result;
}

RWM_DEF Vec4 rwm_v4_scalar_div(Vec4 v, float a) {
  // TODO(ray): Assert we're not dividing by 0
  Vec4 result = {
    v.x/a,
    v.y/a,
    v.z/a,
    v.w/a
  };
  return result;
}

RWM_DEF float rwm_v4_length_squared(Vec4 v) {
  return SQUARE(v.x) + SQUARE(v.y) + SQUARE(v.z) + SQUARE(v.w);
}

RWM_DEF float rwm_v4_length(Vec4 v) {
  return rwm_sqrt(SQUARE(v.x) + SQUARE(v.y) + SQUARE(v.z) + SQUARE(v.w));
}

RWM_DEF Vec4 rwm_v4_normalize(Vec4 v) {
  float inv_norm = rwm_rsqrt(rwm_v4_length_squared(v));
  Vec4 result = {
    v.x * inv_norm,
    v.y * inv_norm,
    v.z * inv_norm,
    v.w * inv_norm
  };
  return result;
}

RWM_DEF Vec4 rwm_v4_hadamard(Vec4 a, Vec4 b) {
  Vec4 result;
#if defined(RW_USE_INTRINSICS)
  result.m = _mm_mul_ps(a.m, b.m);
#else
  result.x = a.x * b.x;
  result.y = a.y * b.y;
  result.z = a.z * b.z;
  result.w = a.w * b.w;
#endif
  return result;
}

RWM_DEF float rwm_v4_inner(Vec4 a, Vec4 b) {
  return (a.x * b.x) +
         (a.y * b.y) +
         (a.z * b.z) +
         (a.w * b.w);
}

RWM_DEF Vec4 rwm_v4_lerp(Vec4 a, float t, Vec4 b) {
  Vec4 result;
#if defined(RW_USE_INTRINSICS)
  result.m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(1.0f-t), a.m), _mm_mul_ps(_mm_set_ps1(t), b.m));
#else
  result.x = rwm_lerp(a.x, t, b.x);
  result.y = rwm_lerp(a.y, t, b.y);
  result.z = rwm_lerp(a.z, t, b.z);
  result.w = rwm_lerp(a.w, t, b.w);
#endif
  return result;
}

// __VEC4_op
#ifdef __cplusplus
RWM_DEF Vec4 operator+(Vec4 a, Vec4 b) {
  Vec4 result = rwm_v4_add(a, b);
  return result;
}

RWM_DEF Vec4 &operator+=(Vec4 &a, Vec4 b) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  a.w += b.w;
  return a;
}

RWM_DEF Vec4 operator-(Vec4 a) {
  Vec4 result;
  result.x = -a.x;
  result.y = -a.y;
  result.z = -a.z;
  result.w = -a.w;
  return result;
}

RWM_DEF Vec4 operator-(Vec4 a, Vec4 b) {
  Vec4 result = rwm_v4_subtract(a, b);
  return result;
}

RWM_DEF Vec4 &operator-=(Vec4 &a, Vec4 b) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  a.w -= b.w;
  return a;
}

RWM_DEF Vec4 operator*(float a, Vec4 v) {
  Vec4 result = rwm_v4_scalar_mult(a, v);
  return result;
}

RWM_DEF Vec4 operator*(Vec4 v, float a) {
  Vec4 result = rwm_v4_scalar_mult(a, v);
  return result;
}

RWM_DEF Vec4 operator*(Vec4 a, Vec4 b) {
  Vec4 result = rwm_v4_hadamard(a, b);
  return result;
}

RWM_DEF Vec4 &operator*=(Vec4 &v, float a) {
  v.x *= a;
  v.y *= a;
  v.z *= a;
  v.w *= a;
  return v;
}

#endif // #ifdef __cplusplus for Vec4

///////////////////////////////////////////////////////////////////////////////
// __MAT4
///////////////////////////////////////////////////////////////////////////////

RWM_DEF void rwm_m4_puts(Mat4 *m) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      printf("%f, ", m->e[i][j]);
    }
    puts("");
  }
  puts("");
}

RWM_DEF Mat4 rwm_m4_diagonal(float a) {
  Mat4 result = { 0.0f };
  result.e[0][0] = a;
  result.e[1][1] = a;
  result.e[2][2] = a;
  result.e[3][3] = a;
  return result;
}

RWM_DEF Mat4 rwm_m4_identity() {
  Mat4 result = rwm_m4_diagonal(1.0f);
  return result;
}

RWM_DEF Mat4 rwm_m4_init_v4(Vec4 r0, Vec4 r1, Vec4 r2, Vec4 r3) {
  Mat4 result;
#if defined(RW_USE_INTRINSICS)
  result.row[0] = _mm_setr_ps(r0.x, r0.y, r0.z, r0.w);
  result.row[1] = _mm_setr_ps(r1.x, r1.y, r1.z, r1.w);
  result.row[2] = _mm_setr_ps(r2.x, r2.y, r2.z, r2.w);
  result.row[3] = _mm_setr_ps(r3.x, r3.y, r3.z, r3.w);
#else
  result.e[0][0] = r0.x;
  result.e[0][1] = r0.y;
  result.e[0][2] = r0.z;
  result.e[0][3] = r0.w;
  result.e[1][0] = r1.x;
  result.e[1][1] = r1.y;
  result.e[1][2] = r1.z;
  result.e[1][3] = r1.w;
  result.e[2][0] = r2.x;
  result.e[2][1] = r2.y;
  result.e[2][2] = r2.z;
  result.e[2][3] = r2.w;
  result.e[3][0] = r3.x;
  result.e[3][1] = r3.y;
  result.e[3][2] = r3.z;
  result.e[3][3] = r3.w;
#endif
  return result;

}

RWM_DEF Mat4 rwm_m4_init_f(float t00, float t01, float t02, float t03,
                    float t10, float t11, float t12, float t13,
                    float t20, float t21, float t22, float t23,
                    float t30, float t31, float t32, float t33)
{
  Mat4 result;
#if defined(RW_USE_INTRINSICS)
  result.row[0] = _mm_setr_ps(t00, t01, t02, t03);
  result.row[1] = _mm_setr_ps(t10, t11, t12, t13);
  result.row[2] = _mm_setr_ps(t20, t21, t22, t23);
  result.row[3] = _mm_setr_ps(t30, t31, t32, t33);
#else
  result.e[0][0] = t00;
  result.e[0][1] = t01;
  result.e[0][2] = t02;
  result.e[0][3] = t03;
  result.e[1][0] = t10;
  result.e[1][1] = t11;
  result.e[1][2] = t12;
  result.e[1][3] = t13;
  result.e[2][0] = t20;
  result.e[2][1] = t21;
  result.e[2][2] = t22;
  result.e[2][3] = t23;
  result.e[3][0] = t30;
  result.e[3][1] = t31;
  result.e[3][2] = t32;
  result.e[3][3] = t33;
#endif
  return result;
}

RWM_DEF Mat4 rwm_m4_transpose(Mat4 m) {
  Mat4 result;

#if defined(RW_USE_INTRINSICS)
  for (int i = 0; i < 4; i++) {
    result.row[i] = m.row[i];
  }
  _MM_TRANSPOSE4_PS(result.row[0], result.row[1], result.row[2], result.row[3]);
#else
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result.e[i][j] = m.e[j][i];
    }
  }
#endif
  return result;
}

RWM_DEF float rwm_m4_trace(Mat4 m) {
  float result = m.e[0][0] + m.e[1][1] + m.e[2][2] + m.e[3][3];
  return result;
}

RWM_DEF Mat4 rwm_m4_add(Mat4 a, Mat4 b) {
  // TODO(ray): Add intrinsic version
  Mat4 result = { 0.0f };
  result.e00 = a.e00 + b.e00;
  result.e01 = a.e01 + b.e01;
  result.e02 = a.e02 + b.e02;
  result.e03 = a.e03 + b.e03;
  result.e10 = a.e10 + b.e10;
  result.e11 = a.e11 + b.e11;
  result.e12 = a.e12 + b.e12;
  result.e13 = a.e13 + b.e13;
  result.e20 = a.e20 + b.e20;
  result.e21 = a.e21 + b.e21;
  result.e22 = a.e22 + b.e22;
  result.e23 = a.e23 + b.e23;
  result.e30 = a.e30 + b.e30;
  result.e31 = a.e31 + b.e31;
  result.e32 = a.e32 + b.e32;
  result.e33 = a.e33 + b.e33;

  return result;
}

RWM_DEF Mat4 rwm_m4_subtract(Mat4 a, Mat4 b) {
  // TODO(ray): Add intrinsic version
  Mat4 result = { 0.0f };
  result.e00 = a.e00 - b.e00;
  result.e01 = a.e01 - b.e01;
  result.e02 = a.e02 - b.e02;
  result.e03 = a.e03 - b.e03;
  result.e10 = a.e10 - b.e10;
  result.e11 = a.e11 - b.e11;
  result.e12 = a.e12 - b.e12;
  result.e13 = a.e13 - b.e13;
  result.e20 = a.e20 - b.e20;
  result.e21 = a.e21 - b.e21;
  result.e22 = a.e22 - b.e22;
  result.e23 = a.e23 - b.e23;
  result.e30 = a.e30 - b.e30;
  result.e31 = a.e31 - b.e31;
  result.e32 = a.e32 - b.e32;
  result.e33 = a.e33 - b.e33;

  return result;
}

RWM_DEF Mat4 rwm_m4_scalar_mult(float a, Mat4 m) {
  // TODO(ray): Add intrinsic version
  Mat4 result = { 0.0f };
  result.e00 = a * m.e00;
  result.e01 = a * m.e01;
  result.e02 = a * m.e02;
  result.e03 = a * m.e03;
  result.e10 = a * m.e10;
  result.e11 = a * m.e11;
  result.e12 = a * m.e12;
  result.e13 = a * m.e13;
  result.e20 = a * m.e20;
  result.e21 = a * m.e21;
  result.e22 = a * m.e22;
  result.e23 = a * m.e23;
  result.e30 = a * m.e30;
  result.e31 = a * m.e31;
  result.e32 = a * m.e32;
  result.e33 = a * m.e33;
  return result;
}

RWM_DEF Mat4 rwm_m4_multiply(Mat4 a, Mat4 b) {
  // TODO(ray): Add intrinsic version
  Mat4 result = { 0.0f };

  result.e00 = (a.e00 * b.e00) + (a.e01 * b.e10) + (a.e02 * b.e20) + (a.e03 * b.e30);
  result.e01 = (a.e00 * b.e01) + (a.e01 * b.e11) + (a.e02 * b.e21) + (a.e03 * b.e31);
  result.e02 = (a.e00 * b.e02) + (a.e01 * b.e12) + (a.e02 * b.e22) + (a.e03 * b.e32);
  result.e03 = (a.e00 * b.e03) + (a.e01 * b.e13) + (a.e02 * b.e23) + (a.e03 * b.e33);

  result.e10 = (a.e10 * b.e00) + (a.e11 * b.e10) + (a.e12 * b.e20) + (a.e13 * b.e30);
  result.e11 = (a.e10 * b.e01) + (a.e11 * b.e11) + (a.e12 * b.e21) + (a.e13 * b.e31);
  result.e12 = (a.e10 * b.e02) + (a.e11 * b.e12) + (a.e12 * b.e22) + (a.e13 * b.e32);
  result.e13 = (a.e10 * b.e03) + (a.e11 * b.e13) + (a.e12 * b.e23) + (a.e13 * b.e33);

  result.e20 = (a.e20 * b.e00) + (a.e21 * b.e10) + (a.e22 * b.e20) + (a.e23 * b.e30);
  result.e21 = (a.e20 * b.e01) + (a.e21 * b.e11) + (a.e22 * b.e21) + (a.e23 * b.e31);
  result.e22 = (a.e20 * b.e02) + (a.e21 * b.e12) + (a.e22 * b.e22) + (a.e23 * b.e32);
  result.e23 = (a.e20 * b.e03) + (a.e21 * b.e13) + (a.e22 * b.e23) + (a.e23 * b.e33);

  result.e30 = (a.e30 * b.e00) + (a.e31 * b.e10) + (a.e32 * b.e20) + (a.e33 * b.e30);
  result.e31 = (a.e30 * b.e01) + (a.e31 * b.e11) + (a.e32 * b.e21) + (a.e33 * b.e31);
  result.e32 = (a.e30 * b.e02) + (a.e31 * b.e12) + (a.e32 * b.e22) + (a.e33 * b.e32);
  result.e33 = (a.e30 * b.e03) + (a.e31 * b.e13) + (a.e32 * b.e23) + (a.e33 * b.e33);

  return result;
}

RWM_DEF Mat4 rwm_m4_hadamard(Mat4 a, Mat4 b) {
  Mat4 result = { 0.0f };
  result.e00 = a.e00 * b.e00;
  result.e01 = a.e01 * b.e01;
  result.e02 = a.e02 * b.e02;
  result.e03 = a.e03 * b.e03;
  result.e10 = a.e10 * b.e10;
  result.e11 = a.e11 * b.e11;
  result.e12 = a.e12 * b.e12;
  result.e13 = a.e13 * b.e13;
  result.e20 = a.e20 * b.e20;
  result.e21 = a.e21 * b.e21;
  result.e22 = a.e22 * b.e22;
  result.e23 = a.e23 * b.e23;
  result.e30 = a.e30 * b.e30;
  result.e31 = a.e31 * b.e31;
  result.e32 = a.e32 * b.e32;
  result.e33 = a.e33 * b.e33;
  return result;
}

// http://www.euclideanspace.com/Maths/algebra/Matrix/functions/inverse/fourD/index.htm
RWM_DEF Mat4 rwm_m4_inverse(Mat4 m) {
  Mat4 result = { 0.0f };

  float det =
    m.e03 * m.e12 * m.e21 * m.e30-m.e02 * m.e13 * m.e21 * m.e30-m.e03 * m.e11 * m.e22 * m.e30+m.e01 * m.e13 * m.e22 * m.e30 +
    m.e02 * m.e11 * m.e23 * m.e30-m.e01 * m.e12 * m.e23 * m.e30-m.e03 * m.e12 * m.e20 * m.e31+m.e02 * m.e13 * m.e20 * m.e31 +
    m.e03 * m.e10 * m.e22 * m.e31-m.e00 * m.e13 * m.e22 * m.e31-m.e02 * m.e10 * m.e23 * m.e31+m.e00 * m.e12 * m.e23 * m.e31 +
    m.e03 * m.e11 * m.e20 * m.e32-m.e01 * m.e13 * m.e20 * m.e32-m.e03 * m.e10 * m.e21 * m.e32+m.e00 * m.e13 * m.e21 * m.e32 +
    m.e01 * m.e10 * m.e23 * m.e32-m.e00 * m.e11 * m.e23 * m.e32-m.e02 * m.e11 * m.e20 * m.e33+m.e01 * m.e12 * m.e20 * m.e33 +
    m.e02 * m.e10 * m.e21 * m.e33-m.e00 * m.e12 * m.e21 * m.e33-m.e01 * m.e10 * m.e22 * m.e33+m.e00 * m.e11 * m.e22 * m.e33;

  if (det == 0.0) return rwm_m4_identity();

  float inv_det = 1.0f/det;
  result.e00 = inv_det * (m.e12*m.e23*m.e31 - m.e13*m.e22*m.e31 + m.e13*m.e21*m.e32 - m.e11*m.e23*m.e32 - m.e12*m.e21*m.e33 + m.e11*m.e22*m.e33);
  result.e01 = inv_det * (m.e03*m.e22*m.e31 - m.e02*m.e23*m.e31 - m.e03*m.e21*m.e32 + m.e01*m.e23*m.e32 + m.e02*m.e21*m.e33 - m.e01*m.e22*m.e33);
  result.e02 = inv_det * (m.e02*m.e13*m.e31 - m.e03*m.e12*m.e31 + m.e03*m.e11*m.e32 - m.e01*m.e13*m.e32 - m.e02*m.e11*m.e33 + m.e01*m.e12*m.e33);
  result.e03 = inv_det * (m.e03*m.e12*m.e21 - m.e02*m.e13*m.e21 - m.e03*m.e11*m.e22 + m.e01*m.e13*m.e22 + m.e02*m.e11*m.e23 - m.e01*m.e12*m.e23);
  result.e10 = inv_det * (m.e13*m.e22*m.e30 - m.e12*m.e23*m.e30 - m.e13*m.e20*m.e32 + m.e10*m.e23*m.e32 + m.e12*m.e20*m.e33 - m.e10*m.e22*m.e33);
  result.e11 = inv_det * (m.e02*m.e23*m.e30 - m.e03*m.e22*m.e30 + m.e03*m.e20*m.e32 - m.e00*m.e23*m.e32 - m.e02*m.e20*m.e33 + m.e00*m.e22*m.e33);
  result.e12 = inv_det * (m.e03*m.e12*m.e30 - m.e02*m.e13*m.e30 - m.e03*m.e10*m.e32 + m.e00*m.e13*m.e32 + m.e02*m.e10*m.e33 - m.e00*m.e12*m.e33);
  result.e13 = inv_det * (m.e02*m.e13*m.e20 - m.e03*m.e12*m.e20 + m.e03*m.e10*m.e22 - m.e00*m.e13*m.e22 - m.e02*m.e10*m.e23 + m.e00*m.e12*m.e23);
  result.e20 = inv_det * (m.e11*m.e23*m.e30 - m.e13*m.e21*m.e30 + m.e13*m.e20*m.e31 - m.e10*m.e23*m.e31 - m.e11*m.e20*m.e33 + m.e10*m.e21*m.e33);
  result.e21 = inv_det * (m.e03*m.e21*m.e30 - m.e01*m.e23*m.e30 - m.e03*m.e20*m.e31 + m.e00*m.e23*m.e31 + m.e01*m.e20*m.e33 - m.e00*m.e21*m.e33);
  result.e22 = inv_det * (m.e01*m.e13*m.e30 - m.e03*m.e11*m.e30 + m.e03*m.e10*m.e31 - m.e00*m.e13*m.e31 - m.e01*m.e10*m.e33 + m.e00*m.e11*m.e33);
  result.e23 = inv_det * (m.e03*m.e11*m.e20 - m.e01*m.e13*m.e20 - m.e03*m.e10*m.e21 + m.e00*m.e13*m.e21 + m.e01*m.e10*m.e23 - m.e00*m.e11*m.e23);
  result.e30 = inv_det * (m.e12*m.e21*m.e30 - m.e11*m.e22*m.e30 - m.e12*m.e20*m.e31 + m.e10*m.e22*m.e31 + m.e11*m.e20*m.e32 - m.e10*m.e21*m.e32);
  result.e31 = inv_det * (m.e01*m.e22*m.e30 - m.e02*m.e21*m.e30 + m.e02*m.e20*m.e31 - m.e00*m.e22*m.e31 - m.e01*m.e20*m.e32 + m.e00*m.e21*m.e32);
  result.e32 = inv_det * (m.e02*m.e11*m.e30 - m.e01*m.e12*m.e30 - m.e02*m.e10*m.e31 + m.e00*m.e12*m.e31 + m.e01*m.e10*m.e32 - m.e00*m.e11*m.e32);
  result.e33 = inv_det * (m.e01*m.e12*m.e20 - m.e02*m.e11*m.e20 + m.e02*m.e10*m.e21 - m.e00*m.e12*m.e21 - m.e01*m.e10*m.e22 + m.e00*m.e11*m.e22);

  return result;
}

///////////////////////////////////////////////////////////////////////////////
// __QUATERNION
///////////////////////////////////////////////////////////////////////////////

RWM_DEF Quaternion rwm_q_init(float x, float y, float z, float w) {
  Quaternion result = { x, y, z, w };
  return result;
}

RWM_DEF Quaternion rwm_q_identity() {
  Quaternion result = { 0.0f, 0.0f, 0.0f, 1.0f };
  return result;
}

RWM_DEF Quaternion rwm_q_init_v4(Vec4 v) {
  Quaternion result = { v.x, v.y, v.z, v.w };
  return result;
}

//RWM_DEF Quaternion rwm_q_add(Quaternion q1, Quaternion q2) {
//}

//RWM_DEF Quaternion rwm_q_subtract(Quaternion q1, Quaternion q2) {
//}

//RWM_DEF Quaternion rwm_q_mult(Quaternion q1, Quaternion q2) {
//}

//RWM_DEF Quaternion rwm_q_scalar_mult(float a, Quaternion q) {
//}

//RWM_DEF Quaternion rwm_q_scalar_div(Quaternion q, float f) {
//}

//RWM_DEF float rwm_q_inner(Quaternion q1, Quaternion q2) {
//}

RWM_DEF float rwm_q_length(Quaternion q) {
#if defined(RW_USE_INTRINSICS)
  float result = rwm_sqrt(SQUARE(q.x) + SQUARE(q.y) + SQUARE(q.z) + SQUARE(q.w));
#else
  float result = sqrt(SQUARE(q.x) + SQUARE(q.y) + SQUARE(q.z) + SQUARE(q.w));
#endif
  return result;
}

RWM_DEF Quaternion rwm_q_inverse(Quaternion q) {
  // conjugate of q times length squared
  // TODO(ray): Assert that the length isn't 0
  float len = rwm_q_length(q);
  Quaternion result = q;
  result.x *= -1/SQUARE(len);
  result.y *= -1/SQUARE(len);
  result.z *= -1/SQUARE(len);
  return result;
}

RWM_DEF Quaternion rwm_q_normalize(Quaternion q) {
  float inv_len = rwm_rsqrt(SQUARE(q.x) + SQUARE(q.y) + SQUARE(q.z) + SQUARE(q.w));
  Quaternion result = {
    q.x * inv_len,
    q.y * inv_len,
    q.z * inv_len,
    q.w * inv_len
  };
  return result;
}

#ifdef __cplusplus
// TODO(ray): Quaternion operator overloading here
#endif // #ifdef __cplusplus for quaternion

///////////////////////////////////////////////////////////////////////////////
// __RECT2
///////////////////////////////////////////////////////////////////////////////

// TODO(ray): Define later
//RWM_DEF Rect2 rwm_r2_init_limit();
//RWM_DEF Rect2 rwm_r2_init(float min_x, float min_y, float max_x, float max_y);
//RWM_DEF Rect2 rwm_r2_init_v2(Vec2 min_p, Vec2 max_p);
//RWM_DEF Rect2 rwm_r2_intersection(Rect2 a, Rect2 b);
//RWM_DEF bool rwm_r2_overlaps(Rect2 a, Rect2 b);
//RWM_DEF bool rwm_r2_pt_inside(Rect2 r, Vec2 p);
//RWM_DEF bool rwm_r2_pt_inside_excl(Rect2 r, Vec2 p);
//RWM_DEF Rect2 rwm_r2_expand(Rect2 r, float delta);
//RWM_DEF Vec2 rwm_r2_diagonal(Rect2 r);
//RWM_DEF float rwm_r2_surface_area(Rect2 r);
//RWM_DEF int rwm_r2_max_extent(Rect2 r);

///////////////////////////////////////////////////////////////////////////////
// __RECT3
///////////////////////////////////////////////////////////////////////////////

RWM_DEF Rect3 rwm_r3_init_limit() {
  Rect3 result = {
    -FLT_MAX, -FLT_MAX, -FLT_MAX,
    FLT_MAX, FLT_MAX, FLT_MAX
  };
  return result;
}

RWM_DEF Rect3 rwm_r3_init(float min_x, float min_y, float min_z, float max_x, float max_y, float max_z) {
  Rect3 result = {
    min_x, min_y, min_z,
    max_x, max_y, max_z
  };
  return result;
}

RWM_DEF Rect3 rwm_r3_init_p(Vec3 p) {
  Rect3 result = {
    p.x, p.y, p.z,
    p.x, p.y, p.z
  };
  return result;
}

RWM_DEF Rect3 rwm_r3_init_v3(Vec3 p1, Vec3 p2) {
  Rect3 result;
  result.min_px = MIN(p1.x, p2.x);
  result.min_py = MIN(p1.y, p2.y);
  result.min_pz = MIN(p1.z, p2.z);
  result.max_px = MAX(p1.x, p2.x);
  result.max_py = MAX(p1.y, p2.y);
  result.max_pz = MAX(p1.z, p2.z);
  return result;
}

RWM_DEF Rect3 rwm_r3_union(Rect3 r1, Rect3 r2) {
  Rect3 result;
  result.min_px = MIN(r1.min_px, r2.min_px);
  result.min_py = MIN(r1.min_py, r2.min_py);
  result.min_pz = MIN(r1.min_pz, r2.min_pz);
  result.max_px = MAX(r1.max_px, r2.max_px);
  result.max_py = MAX(r1.max_py, r2.max_py);
  result.max_pz = MAX(r1.max_pz, r2.max_pz);
  return result;
}

RWM_DEF Rect3 rwm_r3_union_p(Rect3 r1, Point3 p) {
  Rect3 result;
  result.min_px = MIN(r1.min_px, p.x);
  result.min_py = MIN(r1.min_py, p.y);
  result.min_pz = MIN(r1.min_pz, p.z);
  result.max_px = MAX(r1.max_px, p.x);
  result.max_py = MAX(r1.max_py, p.y);
  result.max_pz = MAX(r1.max_pz, p.z);
  return result;
}

RWM_DEF Rect3 rwm_r3_intersection(Rect3 a, Rect3 b) {
  Rect3 result = { 0.0f };
  result.min_px = MAX(a.min_px, b.min_px);
  result.min_py = MAX(a.min_py, b.min_py);
  result.min_pz = MAX(a.min_pz, b.min_pz);
  result.max_px = MIN(a.max_px, b.max_px);
  result.max_py = MIN(a.max_py, b.max_py);
  result.max_pz = MIN(a.max_pz, b.max_pz);
  return result;
}

RWM_DEF bool rwm_r3_overlaps(Rect3 a, Rect3 b) {
  int x = (a.max_px >= b.min_px) && (a.min_px <= b.max_px);
  int y = (a.max_py >= b.min_py) && (a.min_py <= b.max_py);
  int z = (a.max_pz >= b.min_pz) && (a.min_pz <= b.max_pz);
  return x && y && z;
}

RWM_DEF bool rwm_r3_pt_inside(Rect3 r, Vec3 p) {
  int x = p.x >= r.min_px && p.x <= r.max_px;
  int y = p.y >= r.min_py && p.y <= r.max_py;
  int z = p.z >= r.min_pz && p.z <= r.max_pz;
  return x && y && z;
}

RWM_DEF bool rwm_r3_pt_inside_excl(Rect3 r, Vec3 p) {
  int x = p.x > r.min_px && p.x < r.max_px;
  int y = p.y > r.min_py && p.y < r.max_py;
  int z = p.z > r.min_pz && p.z < r.max_pz;
  return x && y && z;
}

RWM_DEF Rect3 rwm_r3_expand(Rect3 r, float delta) {
  Rect3 result = {};
  Vec3 d = rwm_v3_init(delta, delta, delta);
  result.min_p = rwm_v3_subtract(r.min_p, d);
  result.max_p = rwm_v3_add(r.max_p, d);
  return result;
}

RWM_DEF Vec3 rwm_r3_diagonal(Rect3 r) {
  Vec3 result = rwm_v3_subtract(r.max_p, r.min_p);
  return result;
}

RWM_DEF float rwm_r3_surface_area(Rect3 r) {
  Vec3 diag = rwm_r3_diagonal(r);
  float result = 2.0f * (diag.x*diag.y + diag.x*diag.z + diag.y*diag.z);
  return result;
}

RWM_DEF float rwm_r3_volume(Rect3 r) {
  Vec3 diag = rwm_r3_diagonal(r);
  float result = diag.x * diag.y * diag.z;
  return result;
}

RWM_DEF int rwm_r3_max_extent(Rect3 r) {
  Vec3 diag = rwm_r3_diagonal(r);
  if (diag.x > diag.y && diag.x > diag.z) return 0;
  else if (diag.y > diag.z) return 1;
  return 2;
}

RWM_DEF Vec3 rwm_r3_offset(Rect3 r, Vec3 p) {
 Vec3 result = rwm_v3_subtract(p, r.min_p);
 if (r.max_px > r.min_px) result.x /= r.max_px - r.min_px;
 if (r.max_py > r.min_py) result.y /= r.max_py - r.min_py;
 if (r.max_pz > r.min_pz) result.z /= r.max_pz - r.min_pz;
 return result;
}

#endif // #ifdef RWM_IMPLEMENTATION

#endif // #ifndef __RW_MATH_H__
