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

#if defined(RWTR_STATIC)
  #define RWTR_DEF static
#elif defined(RWTR_HEADER_ONLY)
  #define RWTR_DEF static inline
#else
  #define RWTR_DEF extern
#endif

#include "rw_math.h"

///////////////////////////////////////////////////////////////////////////////
// __API
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

RWTR_DEF Transform tr_init_m4(Mat4 *m);
RWTR_DEF Transform tr_init_translate(float x, float y, float z);
RWTR_DEF Transform tr_init_scale(float x, float y, float z);
RWTR_DEF Transform tr_init_rotate_x(float degrees);
RWTR_DEF Transform tr_init_rotate_y(float degrees);
RWTR_DEF Transform tr_init_rotate_z(float degrees);
RWTR_DEF Transform tr_init_rotate(Vec3 axis, float degrees);
RWTR_DEF Transform tr_invert(Transform *tr);
RWTR_DEF Transform tr_compose(Transform *tr1, Transform *tr2);
RWTR_DEF Transform tr_compose_n(Transform **transforms, unsigned num_transforms);
RWTR_DEF Vec3 tr_v3_apply(Transform *tr, Vec3 v);
RWTR_DEF Vec4 tr_v4_apply(Transform *tr, Vec4 v);

#ifdef __cplusplus
}
#endif

#ifdef RWTR_IMPLEMENTATION

#include <math.h>

RWTR_DEF Transform tr_init_m4(Mat4 *m) {
	Transform result;
	result.t = *m;
	result.t_inv = m4_inverse(*m);
	return result;
}

RWTR_DEF Transform tr_init_translate(float x, float y, float z) {
	Transform result;

	result.t = m4_identity();
	result.t.e[0][3] = x;
	result.t.e[1][3] = y;
	result.t.e[2][3] = z;

	result.t_inv = m4_identity();
	result.t_inv.e[0][3] = -x;
	result.t_inv.e[1][3] = -y;
	result.t_inv.e[2][3] = -z;

	return result;
}

RWTR_DEF Transform tr_init_scale(float x, float y, float z) {
	Transform result;

	result.t = m4_identity();
	result.t.e[0][0] = x;
	result.t.e[1][1] = y;
	result.t.e[2][2] = z;

	result.t_inv = m4_identity();
	result.t_inv.e[0][0] = 1/x;
	result.t_inv.e[1][1] = 1/y;
	result.t_inv.e[2][2] = 1/z;

	return result;
}

RWTR_DEF Transform tr_init_rotate_x(float degrees) {
	Transform result;

	result.t = m4_identity();
	result.t.e[1][1] = cosf(to_radians(degrees));
	result.t.e[1][2] = -sinf(to_radians(degrees));
	result.t.e[2][1] = sinf(to_radians(degrees));
	result.t.e[2][2] = cosf(to_radians(degrees));

	result.t_inv = m4_transpose(result.t);

	return result;
}

RWTR_DEF Transform tr_init_rotate_y(float degrees) {
	Transform result;

	result.t = m4_identity();
	result.t.e[0][0] = cosf(to_radians(degrees));
	result.t.e[0][2] = sinf(to_radians(degrees));
	result.t.e[2][0] = -sinf(to_radians(degrees));
	result.t.e[2][2] = cosf(to_radians(degrees));

	result.t_inv = m4_transpose(result.t);

	return result;
}

RWTR_DEF Transform tr_init_rotate_z(float degrees) {
	Transform result;

	result.t = m4_identity();
	result.t.e[0][0] = cosf(to_radians(degrees));
	result.t.e[0][1] = -sinf(to_radians(degrees));
	result.t.e[1][0] = sinf(to_radians(degrees));
	result.t.e[1][1] = cosf(to_radians(degrees));

	result.t_inv = m4_transpose(result.t);

	return result;

}

RWTR_DEF Transform tr_init_rotate(Vec3 axis, float degrees) {
	Vec3 a = v3_normalize(axis);
	float sin_t = sinf(to_radians(degrees));
	float cos_t = cosf(to_radians(degrees));

	Transform result;

	// Compute
	result.t = m4_identity();

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

	result.t_inv = m4_transpose(result.t);

	return result;
}

RWTR_DEF Transform tr_invert(Transform *tr) {
	Transform result;
	result.t = m4_identity();
	result.t_inv = m4_identity();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.t.e[i][j] = tr->t_inv.e[i][j];
			result.t_inv.e[i][j] = tr->t.e[i][j];
		}
	}
	return result;
}

RWTR_DEF Transform tr_compose(Transform *tr1, Transform *tr2) {
	Transform result;
	result.t = m4_multiply(tr1->t, tr2->t);
	result.t_inv = m4_multiply(tr2->t_inv, tr1->t_inv);
	return result;
}

// Imagine that we're multiplying by a Vec4 where the 4th entry is 1
RWTR_DEF Vec3 tr_v3_apply(Transform *tr, Vec3 v) {
	Vec3 result;
	result.x = tr->t.e[0][0]*v.x + tr->t.e[0][1]*v.y + tr->t.e[0][2]*v.z + tr->t.e[0][3];
	result.y = tr->t.e[1][0]*v.x + tr->t.e[1][1]*v.y + tr->t.e[1][2]*v.z + tr->t.e[1][3];
	result.z = tr->t.e[2][0]*v.x + tr->t.e[2][1]*v.y + tr->t.e[2][2]*v.z + tr->t.e[2][3];
	return result;
}

RWTR_DEF Vec4 tr_v4_apply(Transform *tr, Vec4 v) {
	Vec4 result;
	result.x = tr->t.e[0][0]*v.x + tr->t.e[0][1]*v.y + tr->t.e[0][2]*v.z + tr->t.e[0][3]*v.w;
	result.y = tr->t.e[1][0]*v.x + tr->t.e[1][1]*v.y + tr->t.e[1][2]*v.z + tr->t.e[1][3]*v.w;
	result.z = tr->t.e[2][0]*v.x + tr->t.e[2][1]*v.y + tr->t.e[2][2]*v.z + tr->t.e[2][3]*v.w;
	result.w = tr->t.e[3][0]*v.x + tr->t.e[3][1]*v.y + tr->t.e[3][2]*v.z + tr->t.e[3][3]*v.w;
	return result;
}

RWTR_DEF Transform tr_compose_n(Transform **transforms, unsigned num_transforms) {
	// TODO(ray): Assert that there is greater than 1 transform
	Transform result = *(transforms[0]);
	for (int i = 1; i < num_transforms; i++) {
		result.t = m4_multiply(result.t, transforms[i]->t);
		result.t_inv = m4_multiply(result.t_inv, transforms[i]->t_inv);
	}
	return result;
}

#endif // ifdef RWTR_IMPLEMENTATION

#endif // #ifndef __RW_TRANSFORM_H__