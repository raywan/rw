#include <iostream>
#include <assert.h>
#include "../rw_types.h"
#define RWM_IMPLEMENTATION
#include "../rw_math.h"
#include "foo.h"

using namespace std;
int main() {
  f();
  cout << "Hello world" << endl;
  vec2 v = v2_zero();
  vec3 v2 = v3_init(1.0, 2.0, 3.0);
  vec3 v3 = v3_init(1.0, 2.0, 3.0);
  float c = clamp(0.0, -1.0f, 2.0);
  assert(c == 0.0);
  c = clamp(-1.0, 0.0f, 2.0);
  assert(c == 0.0);
  c = clamp(-1.0, 3.0f, 2.0);
  assert(c == 2.0);

  v2_puts(&v);
  v3_puts(&v2);
  v3_puts(&v3);
  vec3 a = (v2 + v3)*2.0;
  v3_puts(&a);
  printf("%f\n", v3_length(a));

}
