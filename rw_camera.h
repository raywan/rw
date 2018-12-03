// NOTE(ray): I don't know if I really want this

#ifndef __RW_CAMERA_H__
#define __RW_CAMERA_H__

#include "rw_math.h"

typedef struct Camera {
  vec3 up;
  vec3 position;
  vec3 target;
}

#endif
