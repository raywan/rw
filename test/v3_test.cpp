#include "v3_test.h"
#include <assert.h>
#include <stdio.h>
#include "../rw_math.h"

#define EPSILON 0.00001f

void v3_assert_eq(Vec3 v, float x, float y, float z) {
	assert(v.x == x);
	assert(v.y == y);
	assert(v.z == z);
}

void run_v3_test() {
	printf("run_v3_test");

	Vec3 v = v3_zero();
	v3_assert_eq(v, 0.0f, 0.0f, 0.0f);
	v = v3_init(1.0f, 2.0f, 3.0f);
	v3_assert_eq(v, 1.0f, 2.0f, 3.0f);
	Vec3 v2 = v3_init(1.0f, 2.0f, 3.0f);
	v3_assert_eq(v2, 1.0f, 2.0f, 3.0f);

	// Negation
	v3_assert_eq(-v2, -1.0f, -2.0f, -3.0f);

	// Add
	Vec3 add_result = v3_add(v, v2);
	v3_assert_eq(add_result, 2.0f, 4.0f, 6.0f);
	v3_assert_eq(v + v2, 2.0f, 4.0f, 6.0f);

	// Subtract
	Vec3 subtract_result = v3_subtract(v, v2);
	v3_assert_eq(subtract_result, 0.0f, 0.0f, 0.0f);
	v3_assert_eq(v - v2, 0.0f, 0.0f, 0.0f);

	// Scalar multiplication
	Vec3 scalar_mult_result = v3_scalar_mult(2.0f, v);
	v3_assert_eq(scalar_mult_result, 2.0f, 4.0f, 6.0f);
	v3_assert_eq(2.0f * v, 2.0f, 4.0f, 6.0f);
	v3_assert_eq(v * 2.0f, 2.0f, 4.0f, 6.0f);

	// Scalar division
	Vec3 scalar_div_result = v3_scalar_div(v3_init(2.0f, 4.0f, 6.0f), 2.0f);
	v3_assert_eq(scalar_div_result, 1.0f, 2.0f, 3.0f);

	// Length squared
	float length_squared = v3_length_squared(v);
	assert(length_squared == 14.0f);

	// Length
	float length = v3_length(v);
	assert(length == rw_sqrt(14.0f));

	// Normalize
	Vec3 normalized = v3_normalize(v);
	for (int i = 0; i < 3; i++) {
		assert(normalized.e[i] - v.e[i]/length < EPSILON);
	}

	// Hadamard
	Vec3 hadamard_result = v3_hadamard(v, v2);
	v3_assert_eq(hadamard_result, 1.0f, 4.0f, 9.0f);
	v3_assert_eq(v * v2, 1.0f, 4.0f, 9.0f);

	// Inner
	float inner_result = v3_inner(v, v2);
	assert(inner_result == 14.0f);

	// Cross
	Vec3 cross_result = v3_cross(v3_init(1.0f, 3.0f, 3.0f), v3_init(4.0f, 5.0f, 3.0f));
	v3_assert_eq(cross_result, -6.0f, 9.0f, -7.0f);

	// lerp
	Vec3 lerp_result = v3_lerp(v, 0.5f, v3_init(3.0f, 2.0f, 1.0f));
	v3_assert_eq(lerp_result, 2.0f, 2.0f, 2.0f);

	// Mutations via operator overload
	v += v3_init(1.0f, 2.0f, 3.0f);
	v3_assert_eq(v, 2.0f, 4.0f, 6.0f);
	v -= v3_init(1.0f, 2.0f, 3.0f);
	v3_assert_eq(v, 1.0f, 2.0f, 3.0f);
	v *= 2.0f;
	v3_assert_eq(v, 2.0f, 4.0f, 6.0f);

	printf(" - PASSED\n");
}
