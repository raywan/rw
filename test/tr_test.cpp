#include "tr_test.h"
#include <assert.h>
#include <stdio.h>
#define RWTR_IMPLEMENTATION
#include "../rw_transform.h"

#define EPSILON 0.00001f

void v3_assert_eq(Vec3 *v, float x, float y, float z) {
	assert(v->x == x);
	assert(v->y == y);
	assert(v->z == z);
}

void v4_assert_eq(Vec4 *v, float x, float y, float z, float w) {
	assert(v->x == x);
	assert(v->y == y);
	assert(v->z == z);
	assert(v->w == w);
}

void run_tr_test() {
	printf("run_tr_test");

	Vec3 v3 = v3_init(1.0f, 2.0f, 3.0f);
	Vec4 v4 = v4_init(1.0f, 2.0f, 3.0f, 4.0f);

	// Scaling
	Transform scale_tr = tr_init_scale(2.0f, 2.0f, 2.0f);
	Vec3 scaled_v3 = tr_v3_apply(&scale_tr, v3);
	v3_assert_eq(&scaled_v3, 2.0f, 4.0f, 6.0f);
	Vec4 scaled_v4 = tr_v4_apply(&scale_tr, v4);
	v4_assert_eq(&scaled_v4, 2.0f, 4.0f, 6.0f, 4.0f);

	// Translate
	Transform translate_tr = tr_init_translate(2.0f, 2.0f, 2.0f);
	Vec3 translated_v3 = tr_v3_apply(&translate_tr, v3);
	v3_assert_eq(&translated_v3, 3.0f, 4.0f, 5.0f);

	Vec4 translated_v4 = tr_v4_apply(&translate_tr, v4);
	v4_assert_eq(&translated_v4, 9.0f, 10.0f, 11.0f, 4.0f);

	puts(" - PASSED");
}
