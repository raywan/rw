#include <assert.h>
#include <stdio.h>
#include "../rw_math.h"

static inline void rwm_v2_assert_eq(Vec2 v, float x, float y) {
	assert(ABS(v.x - x) < EPSILON);
	assert(ABS(v.y - y) < EPSILON);
}

void run_rwm_v2_test() {
	printf("run_rwm_v2_test");

	Vec2 v = rwm_v2_zero();
	rwm_v2_assert_eq(v, 0.0f, 0.0f);
	v = rwm_v2_init(1.0f, 2.0f);
	rwm_v2_assert_eq(v, 1.0f, 2.0f);
	Vec2 v2 = rwm_v2_init(1.0f, 2.0f);
	rwm_v2_assert_eq(v2, 1.0f, 2.0f);

	// Negation
	rwm_v2_assert_eq(-v2, -1.0f, -2.0f);

	// Add
	Vec2 add_result = rwm_v2_add(v, v2);
	rwm_v2_assert_eq(add_result, 2.0f, 4.0f);
	rwm_v2_assert_eq(v + v2, 2.0f, 4.0f);

	// Subtract
	Vec2 subtract_result = rwm_v2_subtract(v, v2);
	rwm_v2_assert_eq(subtract_result, 0.0f, 0.0f);
	rwm_v2_assert_eq(v - v2, 0.0f, 0.0f);

	// Scalar multiplication
	Vec2 scalar_mult_result = rwm_v2_scalar_mult(2.0f, v);
	rwm_v2_assert_eq(scalar_mult_result, 2.0f, 4.0f);
	rwm_v2_assert_eq(2.0f * v, 2.0f, 4.0f);
	rwm_v2_assert_eq(v * 2.0f, 2.0f, 4.0f);

	// Scalar division
	Vec2 scalar_div_result = rwm_v2_scalar_div(rwm_v2_init(2.0f, 4.0f), 2.0f);
	rwm_v2_assert_eq(scalar_div_result, 1.0f, 2.0f);

	// Length squared
	float length_squared = rwm_v2_length_squared(v);
	assert(length_squared == 5.0f);

	// Length
	float length = rwm_v2_length(v);
	assert(length == rwm_sqrt(5.0f));

	// Normalize
	Vec2 normalized = rwm_v2_normalize(v);
	for (int i = 0; i < 2; i++) {
		assert(normalized.e[i] - v.e[i]/length < EPSILON);
	}

	// Hadamard
	Vec2 hadamard_result = rwm_v2_hadamard(v, v2);
	rwm_v2_assert_eq(hadamard_result, 1.0f, 4.0f);
	rwm_v2_assert_eq(v * v2, 1.0f, 4.0f);

	// Inner
	float inner_result = rwm_v2_inner(v, v2);
	assert(inner_result == 5.0f);

	// lerp
	Vec2 lerp_result = rwm_v2_lerp(v, 0.5f, rwm_v2_init(3.0f, 2.0f));
	rwm_v2_assert_eq(lerp_result, 2.0f, 2.0f);

	// Mutations via operator overload
	v += rwm_v2_init(1.0f, 2.0f);
	rwm_v2_assert_eq(v, 2.0f, 4.0f);
	v -= rwm_v2_init(1.0f, 2.0f);
	rwm_v2_assert_eq(v, 1.0f, 2.0f);
	v *= 2.0f;
	rwm_v2_assert_eq(v, 2.0f, 4.0f);

	printf(" - PASSED\n");
}
