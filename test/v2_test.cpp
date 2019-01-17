#include "v2_test.h"
#include <assert.h>
#include <stdio.h>
#include "../rw_math.h"

#define EPSILON 0.00001f

static inline void v2_assert_eq(Vec2 v, float x, float y) {
	assert(v.x == x);
	assert(v.y == y);
}

void run_v2_test() {
	printf("run_v2_test");

	Vec2 v = v2_zero();
	v2_assert_eq(v, 0.0f, 0.0f);
	v = v2_init(1.0f, 2.0f);
	v2_assert_eq(v, 1.0f, 2.0f);
	Vec2 v2 = v2_init(1.0f, 2.0f);
	v2_assert_eq(v2, 1.0f, 2.0f);

	// Negation
	v2_assert_eq(-v2, -1.0f, -2.0f);

	// Add
	Vec2 add_result = v2_add(v, v2);
	v2_assert_eq(add_result, 2.0f, 4.0f);
	v2_assert_eq(v + v2, 2.0f, 4.0f);

	// Subtract
	Vec2 subtract_result = v2_subtract(v, v2);
	v2_assert_eq(subtract_result, 0.0f, 0.0f);
	v2_assert_eq(v - v2, 0.0f, 0.0f);

	// Scalar multiplication
	Vec2 scalar_mult_result = v2_scalar_mult(2.0f, v);
	v2_assert_eq(scalar_mult_result, 2.0f, 4.0f);
	v2_assert_eq(2.0f * v, 2.0f, 4.0f);
	v2_assert_eq(v * 2.0f, 2.0f, 4.0f);

	// Scalar division
	Vec2 scalar_div_result = v2_scalar_div(v2_init(2.0f, 4.0f), 2.0f);
	v2_assert_eq(scalar_div_result, 1.0f, 2.0f);

	// Length squared
	float length_squared = v2_length_squared(v);
	assert(length_squared == 5.0f);

	// Length
	float length = v2_length(v);
	assert(length == rw_sqrt(5.0f));

	// Normalize
	Vec2 normalized = v2_normalize(v);
	for (int i = 0; i < 2; i++) {
		assert(normalized.e[i] - v.e[i]/length < EPSILON);
	}

	// Hadamard
	Vec2 hadamard_result = v2_hadamard(v, v2);
	v2_assert_eq(hadamard_result, 1.0f, 4.0f);
	v2_assert_eq(v * v2, 1.0f, 4.0f);

	// Inner
	float inner_result = v2_inner(v, v2);
	assert(inner_result == 5.0f);

	// lerp
	Vec2 lerp_result = v2_lerp(v, 0.5f, v2_init(3.0f, 2.0f));
	v2_assert_eq(lerp_result, 2.0f, 2.0f);

	// Mutations via operator overload
	v += v2_init(1.0f, 2.0f);
	v2_assert_eq(v, 2.0f, 4.0f);
	v -= v2_init(1.0f, 2.0f);
	v2_assert_eq(v, 1.0f, 2.0f);
	v *= 2.0f;
	v2_assert_eq(v, 2.0f, 4.0f);

	printf(" - PASSED\n");
}