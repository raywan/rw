#include <assert.h>
#include <stdio.h>
#include "../rw_math.h"

#define EPSILON 0.00001f

static inline void rwm_m4_assert_eq(Mat4 *m, float t00, float t01, float t02, float t03,
                    float t10, float t11, float t12, float t13,
                    float t20, float t21, float t22, float t23,
                    float t30, float t31, float t32, float t33)
{
  assert(m->e[0][0] == t00);
  assert(m->e[0][1] == t01);
  assert(m->e[0][2] == t02);
  assert(m->e[0][3] == t03);
  assert(m->e[1][0] == t10);
  assert(m->e[1][1] == t11);
  assert(m->e[1][2] == t12);
  assert(m->e[1][3] == t13);
  assert(m->e[2][0] == t20);
  assert(m->e[2][1] == t21);
  assert(m->e[2][2] == t22);
  assert(m->e[2][3] == t23);
  assert(m->e[3][0] == t30);
  assert(m->e[3][1] == t31);
  assert(m->e[3][2] == t32);
  assert(m->e[3][3] == t33);
}

void run_rwm_m4_test() {
	printf("run_rwm_m4_test");
	Mat4 m = rwm_m4_diagonal(2.0f);
	rwm_m4_assert_eq(&m,
		2.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 2.0f
	);

	m = rwm_m4_identity();
	rwm_m4_assert_eq(&m,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Mat4 m2 = rwm_m4_init_f(
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f,
		9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f
	);
	rwm_m4_assert_eq(&m2,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f,
		9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f
	);

	Mat4 m3 = rwm_m4_init_v4(
		rwm_v4_init(1.0f, 2.0f, 3.0f, 4.0f),
		rwm_v4_init(5.0f, 6.0f, 7.0f, 8.0f),
		rwm_v4_init(9.0f, 10.0f, 11.0f, 12.0f),
		rwm_v4_init(13.0f, 14.0f, 15.0f, 16.0f)
	);
	rwm_m4_assert_eq(&m3,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f,
		9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f
	);

	// Transpose
	Mat4 transpose_m = rwm_m4_transpose(m2);
	rwm_m4_assert_eq(&transpose_m,
		1.0f, 5.0f, 9.0f, 13.0f,
		2.0f, 6.0f, 10.0f, 14.0f,
		3.0f, 7.0f, 11.0f, 15.0f,
		4.0f, 8.0f, 12.0f, 16.0f
	);

	// Trace
	float trace_result = rwm_m4_trace(m2);
	assert(trace_result == 34.0f);

	// Add
	Mat4 add_m = rwm_m4_add(m2, m3);
	rwm_m4_assert_eq(&add_m,
		2.0f, 4.0f, 6.0f, 8.0f,
		10.0f, 12.0f, 14.0f, 16.0f,
		18.0f, 20.0f, 22.0f, 24.0f,
		26.0f, 28.0f, 30.0f, 32.0f
	);

	// Subtract
	Mat4 subtract_m = rwm_m4_subtract(m2, m3);
	rwm_m4_assert_eq(&subtract_m,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);

	// Scalar multiplication
	Mat4 scalar_mult_m = rwm_m4_scalar_mult(2.0f, m2);
	rwm_m4_assert_eq(&scalar_mult_m,
		2.0f, 4.0f, 6.0f, 8.0f,
		10.0f, 12.0f, 14.0f, 16.0f,
		18.0f, 20.0f, 22.0f, 24.0f,
		26.0f, 28.0f, 30.0f, 32.0f
	);

	// Multiplication
	Mat4 mult_m = rwm_m4_multiply(m2, m3);
	rwm_m4_assert_eq(&mult_m,
		90.0f, 100.0f, 110.0f, 120.0f,
		202.0f, 228.0f, 254.0f, 280.0f,
		314.0f, 356.0f, 398.0f, 440.0f,
		426.0f, 484.0f, 542.0f, 600.0f
	);

	// Hadamard
	Mat4 hadamard_m = rwm_m4_hadamard(m2, m3);
	rwm_m4_assert_eq(&hadamard_m,
		1.0f, 4.0f, 9.0f, 16.0f,
		25.0f, 36.0f, 49.0f, 64.0f,
		81.0f, 100.0f, 121.0f, 144.0f,
		169.0f, 196.0f, 225.0f, 256.0f
	);

	// Inverse
	Mat4 inverse_m = rwm_m4_inverse(rwm_m4_init_f(
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 2.0f, 1.0f, 2.0f,
		1.0f, 1.0f, 1.0f, 0.0f,
		1.0f, 4.0f, 2.0f, 3.0f
	));
	rwm_m4_assert_eq(&inverse_m,
		-1.0f, 2.0f, 1.0f, -1.0f,
		-2.0f, 1.0f, 1.0f, 0.0f,
		3.0f, -3.0f, -1.0f, 1.0f,
		1.0f, 0.0f, -1.0f, 0.0f
	);

	printf(" - PASSED\n");
}
