#include <assert.h>
#include <stdio.h>
#include "../rw_math.h"

static inline void rwm_v4_assert_eq(Vec4 v, float x, float y, float z, float w) {
	assert(ABS(v.x - x) < EPSILON);
	assert(ABS(v.y - y) < EPSILON);
	assert(ABS(v.z - z) < EPSILON);
	assert(ABS(v.w - w) < EPSILON);
}

void run_rwm_v4_test() {
	printf("run_rwm_v4_test");

	Vec4 v = rwm_v4_zero();
	rwm_v4_assert_eq(v, 0.0f, 0.0f, 0.0f, 0.0f);
	v = rwm_v4_init(1.0f, 2.0f, 3.0f, 4.0f);
	rwm_v4_assert_eq(v, 1.0f, 2.0f, 3.0f, 4.0f);
	Vec4 v2 = rwm_v4_init(1.0f, 2.0f, 3.0f, 4.0f);
	rwm_v4_assert_eq(v2, 1.0f, 2.0f, 3.0f, 4.0f);

	// Negation
	rwm_v4_assert_eq(-v2, -1.0f, -2.0f, -3.0f, -4.0f);

	// Add
	Vec4 add_result = rwm_v4_add(v, v2);
	rwm_v4_assert_eq(add_result, 2.0f, 4.0f, 6.0f, 8.0f);
	rwm_v4_assert_eq(v + v2, 2.0f, 4.0f, 6.0f, 8.0f);

	// Subtract
	Vec4 subtract_result = rwm_v4_subtract(v, v2);
	rwm_v4_assert_eq(subtract_result, 0.0f, 0.0f, 0.0f, 0.0f);
	rwm_v4_assert_eq(v - v2, 0.0f, 0.0f, 0.0f, 0.0f);

	// Scalar multiplication
	Vec4 scalar_mult_result = rwm_v4_scalar_mult(2.0f, v);
	rwm_v4_assert_eq(scalar_mult_result, 2.0f, 4.0f, 6.0f, 8.0f);
	rwm_v4_assert_eq(2.0f * v, 2.0f, 4.0f, 6.0f, 8.0f);
	rwm_v4_assert_eq(v * 2.0f, 2.0f, 4.0f, 6.0f, 8.0f);

	// Scalar division
	Vec4 scalar_div_result = rwm_v4_scalar_div(rwm_v4_init(2.0f, 4.0f, 6.0f, 8.0f), 2.0f);
	rwm_v4_assert_eq(scalar_div_result, 1.0f, 2.0f, 3.0f, 4.0f);

	// Length squared
	float length_squared = rwm_v4_length_squared(v);
	assert(length_squared == 30.0f);

	// Length
	float length = rwm_v4_length(v);
	assert(length == rwm_sqrt(30.0f));

	// Normalize
	Vec4 normalized = rwm_v4_normalize(v);
	for (int i = 0; i < 4; i++) {
		assert(normalized.e[i] - v.e[i]/length < EPSILON);
	}

	// Hadamard
	Vec4 hadamard_result = rwm_v4_hadamard(v, v2);
	rwm_v4_assert_eq(hadamard_result, 1.0f, 4.0f, 9.0f, 16.0f);
	rwm_v4_assert_eq(v * v2, 1.0f, 4.0f, 9.0f, 16.0f);

	// Inner
	float inner_result = rwm_v4_inner(v, v2);
	assert(inner_result == 30.0f);

	// lerp
	Vec4 lerp_result = rwm_v4_lerp(v, 0.5f, rwm_v4_init(4.0f, 3.0f, 2.0f, 1.0f));
	rwm_v4_assert_eq(lerp_result, 2.5f, 2.5f, 2.5f, 2.5f);

	// Mutations via operator overload
	v += rwm_v4_init(1.0f, 2.0f, 3.0f, 4.0f);
	rwm_v4_assert_eq(v, 2.0f, 4.0f, 6.0f, 8.0f);
	v -= rwm_v4_init(1.0f, 2.0f, 3.0f, 4.0f);
	rwm_v4_assert_eq(v, 1.0f, 2.0f, 3.0f, 4.0f);
	v *= 2.0f;
	rwm_v4_assert_eq(v, 2.0f, 4.0f, 6.0f, 8.0f);

	printf(" - PASSED\n");
}
