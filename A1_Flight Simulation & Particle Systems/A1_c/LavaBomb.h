#ifndef LAVABOMB_H
#define LAVABOMB_H

#include "Matrix4.h"
#include "Random.h"

class LavaBomb
{
public:
  LavaBomb();
  
  void Update(float gravity, Matrix4 world2OpenGLMatrix);

  Cartesian3 direction;
  Cartesian3 position;
  Matrix4 matrix;

  float minimumSpeed = 60.0f;
  float maximumSpeed = 300.0f;
  float mininumAngle = 45.0f;
};

#endif // LAVABOMB_H

