/*
  FILE: rw_transform.h
  VERSION: 0.1.0
  DESCRIPTION: Matrix transformation data structure and functions.
  AUTHOR: Raymond Wan
  DEPENDENCIES: rw_math.h
  USAGE: Simply including the file will only give you declarations (see __API)
    To include the implementation,
      #define RWTR_IMPLEMENTATION

  NOTE(ray): To quickly navigate through the file,
             sections and/or subsections are available to jump to.
  SECTIONS:
    1. __TYPES
    2. __API
    3. __MACROS
    4. __IMPLEMENTATION
*/

#ifndef __RW_TRANSFORM_H__
#define __RW_TRANSFORM_H__

// Detect compiler type (for intrinsics)
#if !defined(RW_DISABLE_INTRINSICS)
#define RW_USE_INTRINSICS
#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#include <x86intrin.h>
#elif defined(_WIN32)
#include <intrin.h>
#endif
#endif // #if !defined(RW_DISABLE_INTRINSICS)

#if defined(RWTR_STATIC)
  #define RWTR_DEF static
#elif defined(RWTR_HEADER_ONLY)
  #define RWTR_DEF static inline
#else
  #define RWTR_DEF extern
#endif


///////////////////////////////////////////////////////////////////////////////
// __TYPES
///////////////////////////////////////////////////////////////////////////////

#include "rw_math.h"

typedef enum RWTR_AXIS {
  RWTR_NO_AXIS = -1,
  RWTR_X_AXIS,
  RWTR_Y_AXIS,
  RWTR_Z_AXIS,
} RWTR_AXIS;

///////////////////////////////////////////////////////////////////////////////
// __API
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

RWTR_DEF Transform rwtr_init_m4(Mat4 *m);
RWTR_DEF Transform rwtr_init_translate(float x, float y, float z);
RWTR_DEF Transform rwtr_init_scale(float x, float y, float z);
RWTR_DEF Transform rwtr_init_rotate_x(float degrees);
RWTR_DEF Transform rwtr_init_rotate_y(float degrees);
RWTR_DEF Transform rwtr_init_rotate_z(float degrees);
RWTR_DEF Transform rwtr_init_rotate_q(Quaternion rotate_q);
RWTR_DEF Transform rwtr_init_rotate(Vec3 axis, float degrees);
RWTR_DEF Transform rwtr_invert(Transform *tr);
RWTR_DEF Transform rwtr_compose(Transform *tr1, Transform *tr2);
RWTR_DEF Transform rwtr_compose_n(Transform **transforms, unsigned num_transforms);
RWTR_DEF Transform rwtr_trs(Vec3 translate, Vec3 scale, unsigned int axis, float degrees);
RWTR_DEF Vec3 rwtr_v3_apply(Transform *tr, Vec3 v);
RWTR_DEF Point3 rwtr_pt3_apply(Transform *tr, Point3 p);
RWTR_DEF Normal3 rwtr_n3_apply(Transform *tr, Normal3 p);
RWTR_DEF Vec4 rwtr_v4_apply(Transform *tr, Vec4 v);
RWTR_DEF Rect3 rwtr_r3_apply(Transform *tr, Rect3 r);
RWTR_DEF Vec3 rwtr_v3_apply_inv(Transform *tr, Vec3 v);
RWTR_DEF Vec3 rwtr_pt3_apply_inv(Transform *tr, Point3 p);
RWTR_DEF Vec4 rwtr_v4_apply_inv(Transform *tr, Vec4 v);
RWTR_DEF Rect3 rwtr_r3_apply_inv(Transform *tr, Rect3 r);

#ifdef __cplusplus
}
#endif


///////////////////////////////////////////////////////////////////////////////
// __IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////

#ifdef RWTR_IMPLEMENTATION

#include <math.h>

RWTR_DEF Transform rwtr_init_m4(Mat4 *m) {
  Transform result;
  result.t = *m;
  result.t_inv = rwm_m4_inverse(*m);
  return result;
}

RWTR_DEF Transform rwtr_init_translate(float x, float y, float z) {
  Transform result;

  result.t = rwm_m4_identity();
  result.t.e[0][3] = x;
  result.t.e[1][3] = y;
  result.t.e[2][3] = z;

  result.t_inv = rwm_m4_identity();
  result.t_inv.e[0][3] = -x;
  result.t_inv.e[1][3] = -y;
  result.t_inv.e[2][3] = -z;

  return result;
}

RWTR_DEF Transform rwtr_init_scale(float x, float y, float z) {
  Transform result;

  result.t = rwm_m4_identity();
  result.t.e[0][0] = x;
  result.t.e[1][1] = y;
  result.t.e[2][2] = z;

  result.t_inv = rwm_m4_identity();
  result.t_inv.e[0][0] = 1/x;
  result.t_inv.e[1][1] = 1/y;
  result.t_inv.e[2][2] = 1/z;

  return result;
}

RWTR_DEF Transform rwtr_init_rotate_x(float degrees) {
  Transform result;

  result.t = rwm_m4_identity();
  result.t.e[1][1] = cosf(rwm_to_radians(degrees));
  result.t.e[1][2] = -sinf(rwm_to_radians(degrees));
  result.t.e[2][1] = sinf(rwm_to_radians(degrees));
  result.t.e[2][2] = cosf(rwm_to_radians(degrees));

  result.t_inv = rwm_m4_transpose(result.t);

  return result;
}

RWTR_DEF Transform rwtr_init_rotate_y(float degrees) {
  Transform result;

  result.t = rwm_m4_identity();
  result.t.e[0][0] = cosf(rwm_to_radians(degrees));
  result.t.e[0][2] = sinf(rwm_to_radians(degrees));
  result.t.e[2][0] = -sinf(rwm_to_radians(degrees));
  result.t.e[2][2] = cosf(rwm_to_radians(degrees));

  result.t_inv = rwm_m4_transpose(result.t);

  return result;
}

RWTR_DEF Transform rwtr_init_rotate_z(float degrees) {
  Transform result;

  result.t = rwm_m4_identity();
  result.t.e[0][0] = cosf(rwm_to_radians(degrees));
  result.t.e[0][1] = -sinf(rwm_to_radians(degrees));
  result.t.e[1][0] = sinf(rwm_to_radians(degrees));
  result.t.e[1][1] = cosf(rwm_to_radians(degrees));

  result.t_inv = rwm_m4_transpose(result.t);

  return result;
}

RWTR_DEF Transform rwtr_init_rotate_q(Quaternion rotate_q) {
  Transform result;
  result.t = rwm_q_to_m4(rotate_q);
  result.t_inv = rwm_q_to_m4(rwm_q_inverse(rotate_q));
  return result;
}

RWTR_DEF Transform rwtr_init_rotate(Vec3 axis, float degrees) {
  Transform result;
#if 0
  Vec3 a = rwm_v3_normalize(axis);
  float sin_t = sinf(rwm_to_radians(degrees));
  float cos_t = cosf(rwm_to_radians(degrees));


  // Compute
  result.t = rwm_m4_identity();

  // Rotation of first basis vector
  result.t.e[0][0] = SQUARE(a.x) + (1-SQUARE(a.x)) * cos_t;
  result.t.e[0][1] = a.x * a.y * (1-cos_t) - a.z * sin_t;
  result.t.e[0][2] = a.x * a.z * (1-cos_t) + a.y * sin_t;

  // Second
  result.t.e[1][0] = a.x * a.y * (1-cos_t) + a.z * sin_t;
  result.t.e[1][1] = SQUARE(a.y) + (1-SQUARE(a.y)) * cos_t;
  result.t.e[1][2] = a.y * a.z * (1-cos_t) - a.x * sin_t;

  // Third
  result.t.e[2][0] = a.x * a.z * (1-cos_t) - a.y * sin_t;
  result.t.e[2][1] = a.y * a.z * (1-cos_t) + a.x * sin_t;
  result.t.e[2][2] = SQUARE(a.z) + (1-SQUARE(a.z)) * cos_t;
#else
  Quaternion r = rwm_q_init_rotation(axis, rwm_to_radians(degrees));
  Quaternion r_inv = rwm_q_inverse(r);
  result.t = rwm_q_to_m4(r);
#endif

  result.t_inv = rwm_m4_transpose(result.t);

  return result;
}

RWTR_DEF Transform rwtr_invert(Transform *tr) {
  Transform result;
  result.t = rwm_m4_identity();
  result.t_inv = rwm_m4_identity();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result.t.e[i][j] = tr->t_inv.e[i][j];
      result.t_inv.e[i][j] = tr->t.e[i][j];
    }
  }
  return result;
}

RWTR_DEF Transform rwtr_compose(Transform *tr1, Transform *tr2) {
  Transform result;
  result.t = rwm_m4_multiply(tr1->t, tr2->t);
  result.t_inv = rwm_m4_multiply(tr2->t_inv, tr1->t_inv);
  return result;
}

RWTR_DEF Transform rwtr_compose_n(Transform **transforms, unsigned num_transforms) {
  // TODO(ray): Assert that there is greater than 1 transform
  Transform result = *(transforms[0]);
  for (int i = 1; i < num_transforms; i++) {
    result.t = rwm_m4_multiply(transforms[i]->t, result.t);
    result.t_inv = rwm_m4_multiply(result.t_inv, transforms[i]->t_inv);
  }
  return result;
}

RWTR_DEF Transform rwtr_trs(Vec3 translate, Vec3 scale, unsigned int axis, float degrees) {
  Transform t_tr = rwtr_init_translate(translate.x, translate.y, translate.z);
  Transform s_tr = rwtr_init_scale(scale.x, scale.y, scale.z);
  Transform r_tr;
  int num_transforms = 3;
  switch (axis) {
    case RWTR_X_AXIS:
      r_tr = rwtr_init_rotate_x(degrees);
      break;
    case RWTR_Y_AXIS:
      r_tr = rwtr_init_rotate_y(degrees);
      break;
    case RWTR_Z_AXIS:
      r_tr = rwtr_init_rotate_z(degrees);
      break;
    default:
      num_transforms = 2;
  }

  Transform *compose_list[3];
  if (num_transforms == 2) {
    compose_list[0] = &s_tr;
    compose_list[1] = &t_tr;
  } else {
    compose_list[0] = &s_tr;
    compose_list[1] = &r_tr;
    compose_list[2] = &t_tr;
  }

  Transform result = rwtr_compose_n(compose_list, num_transforms);
  return result;
}

// NOTE(ray): We make the distinction of transforming a Vector and a Point by a 4d matrix.
// The homogenous coordinate of a Vector will have w = 0 and a Point will have w = 1.
// This means that Vectors WILL NOT BE AFFECTED by translations.
RWTR_DEF Vec3 rwtr_v3_apply(Transform *tr, Vec3 v) {
  Vec3 result;
  result.x = tr->t.e[0][0]*v.x + tr->t.e[0][1]*v.y + tr->t.e[0][2]*v.z;
  result.y = tr->t.e[1][0]*v.x + tr->t.e[1][1]*v.y + tr->t.e[1][2]*v.z;
  result.z = tr->t.e[2][0]*v.x + tr->t.e[2][1]*v.y + tr->t.e[2][2]*v.z;
  return result;
}

RWTR_DEF Point3 rwtr_pt3_apply(Transform *tr, Point3 p) {
  Point3 result;
  result.x = tr->t.e[0][0]*p.x + tr->t.e[0][1]*p.y + tr->t.e[0][2]*p.z + tr->t.e[0][3];
  result.y = tr->t.e[1][0]*p.x + tr->t.e[1][1]*p.y + tr->t.e[1][2]*p.z + tr->t.e[1][3];
  result.z = tr->t.e[2][0]*p.x + tr->t.e[2][1]*p.y + tr->t.e[2][2]*p.z + tr->t.e[2][3];
  return result;
}

// NOTE(ray): Normals must be transformed in a special way
// We need to use the inverse transpose of the transformation
RWTR_DEF Normal3 rwtr_n3_apply(Transform *tr, Normal3 p) {
  Normal3 result;
  result.x = tr->t_inv.e[0][0]*p.x + tr->t_inv.e[1][0]*p.y + tr->t_inv.e[2][0]*p.z;
  result.y = tr->t_inv.e[0][1]*p.x + tr->t_inv.e[1][1]*p.y + tr->t_inv.e[2][1]*p.z;
  result.z = tr->t_inv.e[0][2]*p.x + tr->t_inv.e[1][2]*p.y + tr->t_inv.e[2][2]*p.z;
  return result;
}

RWTR_DEF Vec4 rwtr_v4_apply(Transform *tr, Vec4 v) {
  Vec4 result;
  result.x = tr->t.e[0][0]*v.x + tr->t.e[0][1]*v.y + tr->t.e[0][2]*v.z + tr->t.e[0][3]*v.w;
  result.y = tr->t.e[1][0]*v.x + tr->t.e[1][1]*v.y + tr->t.e[1][2]*v.z + tr->t.e[1][3]*v.w;
  result.z = tr->t.e[2][0]*v.x + tr->t.e[2][1]*v.y + tr->t.e[2][2]*v.z + tr->t.e[2][3]*v.w;
  result.w = tr->t.e[3][0]*v.x + tr->t.e[3][1]*v.y + tr->t.e[3][2]*v.z + tr->t.e[3][3]*v.w;
  return result;
}

RWTR_DEF Rect3 rwtr_r3_apply(Transform *tr, Rect3 r) {
  Rect3 result = rwm_r3_init_p(rwtr_pt3_apply(tr, r.min_p));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply(tr, rwm_v3_init(r.min_px, r.min_py, r.max_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply(tr, rwm_v3_init(r.min_px, r.max_py, r.min_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply(tr, rwm_v3_init(r.min_px, r.max_py, r.max_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply(tr, rwm_v3_init(r.max_px, r.min_py, r.min_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply(tr, rwm_v3_init(r.max_px, r.min_py, r.max_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply(tr, rwm_v3_init(r.max_px, r.max_py, r.min_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply(tr, rwm_v3_init(r.max_px, r.max_py, r.max_pz))));
  return result;
}

RWTR_DEF Vec3 rwtr_v3_apply_inv(Transform *tr, Vec3 v) {
  Vec3 result;
  result.x = tr->t_inv.e[0][0]*v.x + tr->t_inv.e[0][1]*v.y + tr->t_inv.e[0][2]*v.z;
  result.y = tr->t_inv.e[1][0]*v.x + tr->t_inv.e[1][1]*v.y + tr->t_inv.e[1][2]*v.z;
  result.z = tr->t_inv.e[2][0]*v.x + tr->t_inv.e[2][1]*v.y + tr->t_inv.e[2][2]*v.z;
  return result;
}

RWTR_DEF Vec3 rwtr_pt3_apply_inv(Transform *tr, Point3 p) {
  Vec3 result;
  result.x = tr->t_inv.e[0][0]*p.x + tr->t_inv.e[0][1]*p.y + tr->t_inv.e[0][2]*p.z + tr->t_inv.e[0][3];
  result.y = tr->t_inv.e[1][0]*p.x + tr->t_inv.e[1][1]*p.y + tr->t_inv.e[1][2]*p.z + tr->t_inv.e[1][3];
  result.z = tr->t_inv.e[2][0]*p.x + tr->t_inv.e[2][1]*p.y + tr->t_inv.e[2][2]*p.z + tr->t_inv.e[2][3];
  return result;
}

RWTR_DEF Vec4 rwtr_v4_apply_inv(Transform *tr, Vec4 v) {
  Vec4 result;
  result.x = tr->t_inv.e[0][0]*v.x + tr->t_inv.e[0][1]*v.y + tr->t_inv.e[0][2]*v.z + tr->t_inv.e[0][3]*v.w;
  result.y = tr->t_inv.e[1][0]*v.x + tr->t_inv.e[1][1]*v.y + tr->t_inv.e[1][2]*v.z + tr->t_inv.e[1][3]*v.w;
  result.z = tr->t_inv.e[2][0]*v.x + tr->t_inv.e[2][1]*v.y + tr->t_inv.e[2][2]*v.z + tr->t_inv.e[2][3]*v.w;
  result.w = tr->t_inv.e[3][0]*v.x + tr->t_inv.e[3][1]*v.y + tr->t_inv.e[3][2]*v.z + tr->t_inv.e[3][3]*v.w;
  return result;
}

RWTR_DEF Rect3 rwtr_r3_apply_inv(Transform *tr, Rect3 r) {
  Rect3 result = rwm_r3_init_p(rwtr_pt3_apply_inv(tr, r.min_p));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply_inv(tr, rwm_v3_init(r.min_px, r.min_py, r.max_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply_inv(tr, rwm_v3_init(r.min_px, r.max_py, r.min_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply_inv(tr, rwm_v3_init(r.min_px, r.max_py, r.max_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply_inv(tr, rwm_v3_init(r.max_px, r.min_py, r.min_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply_inv(tr, rwm_v3_init(r.max_px, r.min_py, r.max_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply_inv(tr, rwm_v3_init(r.max_px, r.max_py, r.min_pz))));
  result = rwm_r3_union(result, rwm_r3_init_p(rwtr_pt3_apply_inv(tr, rwm_v3_init(r.max_px, r.max_py, r.max_pz))));
  return result;
}

#endif // #ifdef RWTR_IMPLEMENTATION

#endif // #ifndef __RW_TRANSFORM_H__
