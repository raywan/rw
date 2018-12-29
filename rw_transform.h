#ifndef __RW_TRANSFORM_H__
#define __RW_TRANSFORM_H__

// Detect compiler type (for intrinsics)
#if !defined(RW_DISABLE_INTRINSICS)
#define RW_USE_INTRINSICS
#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#include <x86intrin.h>
#elif defined(__MSC_VER)
#include <intrin.h>
#endif
#endif // #if !defined(RW_DISABLE_INTRINSICS)

#if defined(RWT_STATIC)
  #define RWT_DEF static
#elif defined(RWT_HEADER_ONLY)
  #define RWT_DEF static inline
#else
  #define RWT_DEF extern
#endif

#include "rw_math.h"

///////////////////////////////////////////////////////////////////////////////
// __API
///////////////////////////////////////////////////////////////////////////////

typedef struct Transform {
	Mat4 t;
	Mat4 t_inv;
} Transform;

#ifdef __cplusplus
extern "C" {

RWT_DEF Transform tr_init_translate(float x, float y, float z);
RWT_DEF Transform tr_init_scale(float x, float y, float z);
RWT_DEF Transform tr_init_rotate_x(float angle);
RWT_DEF Transform tr_init_rotate_y(float angle);
RWT_DEF Transform tr_init_rotate_z(float angle);
RWT_DEF Transform tr_compose(Transform tr1, Transform tr2);
RWT_DEF Vec3 tr_v3_apply(Transform tr, Vec3 v);
RWT_DEF Vec4 tr_v4_apply(Transform tr, Vec4 v);

#ifdef __cplusplus
}
#endif

#ifdef RWT_IMPLEMENTATION

RWT_DEF Transform tr_init_translate(float x, float y, float z) {
	Transform result;
	result.t = m4_identity();
	result.t_inv = m4_identity();
	return result;
}

RWT_DEF Transform tr_init_scale(float x, float y, float z);
RWT_DEF Transform tr_init_rotate_x(float angle);
RWT_DEF Transform tr_init_rotate_y(float angle);
RWT_DEF Transform tr_init_rotate_z(float angle);
RWT_DEF Transform tr_compose(Transform tr1, Transform tr2);
RWT_DEF Vec3 tr_v3_apply(Transform tr, Vec3 v);
RWT_DEF Vec4 tr_v4_apply(Transform tr, Vec4 v);

#endif // ifdef RWT_IMPLEMENTATION

#endif // #ifndef __RW_TRANSFORM_H__
