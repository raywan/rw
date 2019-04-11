#include "tr_test.h"
#include <assert.h>
#include <stdio.h>
#define RWTR_IMPLEMENTATION
#include "../rw_transform.h"

#define EPSILON 0.00001f

static inline void rwm_v3_assert_eq(Vec3 *v, float x, float y, float z) {
	assert(v->x == x);
	assert(v->y == y);
	assert(v->z == z);
}

static inline void rwm_v4_assert_eq(Vec4 *v, float x, float y, float z, float w) {
	assert(v->x == x);
	assert(v->y == y);
	assert(v->z == z);
	assert(v->w == w);
}

void run_rwtr_test() {
	printf("run_rwtr_test");

	Vec3 v3 = rwm_v3_init(1.0f, 2.0f, 3.0f);
	Vec4 v4 = rwm_v4_init(1.0f, 2.0f, 3.0f, 4.0f);

	// Init using matrix
  Mat4 m = rwm_m4_diagonal(2.0f);
	m.e[3][3] = 1.0f;
	Transform tr = rwtr_init_m4(&m);
	rwm_m4_assert_eq(&tr.t,
		2.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	rwm_m4_assert_eq(&tr.t_inv,
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// Scaling
	Transform scale_tr = rwtr_init_scale(2.0f, 2.0f, 2.0f);
	Vec3 scaled_v3 = rwtr_v3_apply(&scale_tr, v3);
	rwm_v3_assert_eq(&scaled_v3, 2.0f, 4.0f, 6.0f);
	Vec4 scaled_v4 = rwtr_v4_apply(&scale_tr, v4);
	rwm_v4_assert_eq(&scaled_v4, 2.0f, 4.0f, 6.0f, 4.0f);

	// Translate
	Transform translate_tr = rwtr_init_translate(2.0f, 2.0f, 2.0f);
	Vec3 translated_v3 = rwtr_v3_apply(&translate_tr, v3);
	rwm_v3_assert_eq(&translated_v3, v3.x, v3.y, v3.z);
	translated_v3 = rwtr_pt3_apply(&translate_tr, v3);
	rwm_v3_assert_eq(&translated_v3, 3.0f, 4.0f, 5.0f);

	Vec4 translated_v4 = rwtr_v4_apply(&translate_tr, v4);
	rwm_v4_assert_eq(&translated_v4, 9.0f, 10.0f, 11.0f, 4.0f);

	puts(" - PASSED");
}
