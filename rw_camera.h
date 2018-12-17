// NOTE(ray): I don't know if I really want this

#ifndef __RW_CAMERA_H__
#define __RW_CAMERA_H__

#include "rw_math.h"

typedef struct Camera {
  Vec3 up;
  Vec3 position;
  Vec3 target;
  float fov_y;
}

#endif
