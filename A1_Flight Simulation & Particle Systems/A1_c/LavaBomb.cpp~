#include "LavaBomb.h"
#include <math.h>

LavaBomb::LavaBomb(){
  position = Cartesian3(-38500, -4000, 0);
  direction =  RandomUnitVectorInUpwardsCone(mininumAngle*(M_PI / 180.0), minimumSpeed, maximumSpeed);
}

void LavaBomb::Update(float gravity, Matrix4 world2OpenGLMatrix) {
  // Update the position of the LavaBomb based on its speed and gravity
  direction.z -= gravity;
  Cartesian3 move;
  
  // every frame move
  move.x = direction.x;
  move.y = direction.y;
  move.z = direction.z - (gravity / 2);

  position.x += move.x;
  position.y += move.y;
  position.z += move.z;
  
  matrix = world2OpenGLMatrix * Matrix4::Translate(position);
}
