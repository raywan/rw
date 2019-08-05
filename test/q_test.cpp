#include <assert.h>
#include <stdio.h>
#include "../rw_math.h"

static inline void rwm_q_assert_eq(Quaternion q, float x, float y, float z, float w) {
	assert(ABS(q.x - x) < EPSILON);
	assert(ABS(q.y - y) < EPSILON);
	assert(ABS(q.z - z) < EPSILON);
	assert(ABS(q.w - w) < EPSILON);
}

void run_rwm_q_test() {
	printf("run_rwm_q_test");
  Quaternion r1 = rwm_q_init_rotation(rwm_v3_init(0.69, 2.0, 0.45), rwm_to_radians(43.0));
  Quaternion r2 = rwm_q_init_rotation(rwm_v3_init(0.0, 1.0, 0.0), rwm_to_radians(45.0));
  Mat4 rot_mat_general = rwm_q_to_m4(r1);
  Mat4 rot_mat = rwm_q_rotation_to_m4(r1);

  // NOTE(ray): Values computed with https://www.andre-gaschler.com/rotationconverter/
  //rwm_q_assert_eq(r, 0.0f, 0.382683f, 0.0f, 0.923879f);
  rwm_q_assert_eq(r1, 0.116914, 0.3388812, 0.0762483, 0.9304176);
	rwm_m4_assert_eq(&rot_mat_general,
    0.7586915, -0.0626455, 0.6484310, 0.0f,
    0.2211254, 0.9610347, -0.1658795, 0.0f,
    -0.6127731, 0.2692359, 0.7429813, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	rwm_m4_assert_eq(&rot_mat,
    0.7586915, -0.0626455, 0.6484310, 0.0f,
    0.2211254, 0.9610347, -0.1658795, 0.0f,
    -0.6127731, 0.2692359, 0.7429813, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

  rot_mat = rwm_q_rotation_to_m4(r2);
	rwm_m4_assert_eq(&rot_mat,
    0.7071068, 0.0000000, 0.7071068, 0.0f,
    0.0000000, 1.0000000, 0.0000000, 0.0f,
    -0.7071068, 0.0000000, 0.7071068, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

  Quaternion conj_r = rwm_q_conjugate(r1);
  rwm_q_assert_eq(conj_r, -0.116914, -0.3388812, -0.0762483, 0.9304176);

  Quaternion inv_r = rwm_q_inverse(r1);
  rwm_q_assert_eq(inv_r, -0.116914, -0.3388812, -0.0762483, 0.9304176);

	puts(" - PASSED");
}
