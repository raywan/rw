#include "v4_test.h"
#include <assert.h>
#include <stdio.h>
#include "../rw_math.h"

#define EPSILON 0.00001f
void v4_assert_eq(Vec4 v, float x, float y, float z, float w) {
	assert(v.x == x);
	assert(v.y == y);
	assert(v.z == z);
	assert(v.w == w);
}

void run_v4_test() {
	printf("run_v4_test");

	Vec4 v = v4_zero();
	v4_assert_eq(v, 0.0f, 0.0f, 0.0f, 0.0f);
	v = v4_init(1.0f, 2.0f, 3.0f, 4.0f);
	v4_assert_eq(v, 1.0f, 2.0f, 3.0f, 4.0f);
	Vec4 v2 = v4_init(1.0f, 2.0f, 3.0f, 4.0f);
	v4_assert_eq(v2, 1.0f, 2.0f, 3.0f, 4.0f);

	// Negation
	v4_assert_eq(-v2, -1.0f, -2.0f, -3.0f, -4.0f);

	// Add
	Vec4 add_result = v4_add(v, v2);
	v4_assert_eq(add_result, 2.0f, 4.0f, 6.0f, 8.0f);
	v4_assert_eq(v + v2, 2.0f, 4.0f, 6.0f, 8.0f);

	// Subtract
	Vec4 subtract_result = v4_subtract(v, v2);
	v4_assert_eq(subtract_result, 0.0f, 0.0f, 0.0f, 0.0f);
	v4_assert_eq(v - v2, 0.0f, 0.0f, 0.0f, 0.0f);

	// Scalar multiplication
	Vec4 scalar_mult_result = v4_scalar_mult(2.0f, v);
	v4_assert_eq(scalar_mult_result, 2.0f, 4.0f, 6.0f, 8.0f);
	v4_assert_eq(2.0f * v, 2.0f, 4.0f, 6.0f, 8.0f);
	v4_assert_eq(v * 2.0f, 2.0f, 4.0f, 6.0f, 8.0f);

	// Scalar division
	Vec4 scalar_div_result = v4_scalar_div(v4_init(2.0f, 4.0f, 6.0f, 8.0f), 2.0f);
	v4_assert_eq(scalar_div_result, 1.0f, 2.0f, 3.0f, 4.0f);

	// Length squared
	float length_squared = v4_length_squared(v);
	assert(length_squared == 30.0f);

	// Length
	float length = v4_length(v);
	assert(length == rw_sqrt(30.0f));

	// Normalize
	Vec4 normalized = v4_normalize(v);
	for (int i = 0; i < 4; i++) {
		assert(normalized.e[i] - v.e[i]/length < EPSILON);
	}

	// Hadamard
	Vec4 hadamard_result = v4_hadamard(v, v2);
	v4_assert_eq(hadamard_result, 1.0f, 4.0f, 9.0f, 16.0f);
	v4_assert_eq(v * v2, 1.0f, 4.0f, 9.0f, 16.0f);

	// Inner
	float inner_result = v4_inner(v, v2);
	assert(inner_result == 30.0f);

	// lerp
	Vec4 lerp_result = v4_lerp(v, 0.5f, v4_init(4.0f, 3.0f, 2.0f, 1.0f));
	v4_assert_eq(lerp_result, 2.5f, 2.5f, 2.5f, 2.5f);

	// Mutations via operator overload
	v += v4_init(1.0f, 2.0f, 3.0f, 4.0f);
	v4_assert_eq(v, 2.0f, 4.0f, 6.0f, 8.0f);
	v -= v4_init(1.0f, 2.0f, 3.0f, 4.0f);
	v4_assert_eq(v, 1.0f, 2.0f, 3.0f, 4.0f);
	v *= 2.0f;
	v4_assert_eq(v, 2.0f, 4.0f, 6.0f, 8.0f);

	printf(" - PASSED\n");
}
