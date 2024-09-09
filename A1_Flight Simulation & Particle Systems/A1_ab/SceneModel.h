///////////////////////////////////////////////////
//
//	Hamish Carr
//	October, 2023
//
//	------------------------
//	SceneModel.h
//	------------------------
//	
//	The model of the scene
//	
///////////////////////////////////////////////////

#ifndef __SCENE_MODEL_H
#define __SCENE_MODEL_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "HomogeneousFaceSurface.h"
#include "Terrain.h"
#include "Matrix4.h"
#include "Random.h"
#include "LavaBomb.h"

class SceneModel								
	{ // class SceneModel
	public:	
	  // we'll have three geometric surfaces: one for the ground (and volcano)
	  // one for the plane 
	  // and one for the lava bomb(s)
	  Terrain groundModel;
	  HomogeneousFaceSurface planeModel;
	  HomogeneousFaceSurface lavaBombModel;
	  
	  SceneModel();
	  
	  // a matrix that specifies the mapping from world coordinates to those assumed	  
	  // by OpenGL
	  Matrix4 world2OpenGLMatrix;
	  Matrix4 light2OpenGLMatrix;
	  Matrix4 plane2OpenGLMatrix;
	
	  // routine that updates the scene for the next frame
	  void Update();

	  // routine to tell the scene to render itself
	  void Render();

	  //controlling the sence
	  float angleYaw = 0;
	  float anglePitch = 0;
	  float angleRoll = 0;

	  float planeYaw;
	  float planePitch;
	  float planeRoll;

	  float planeSpeed = 0;
	  float posX = 0;
	  float posY = 0;
	  float posZ = 0;

	  Matrix4 rotationMatrix;
	  Matrix4 traslationMatrix;

	  Cartesian3 planePosition;
	  
	  void ChangeSpeed(float speed);
	  void SetSpeed(float speed);
	  void RotateYaw(float angle);
	  void RotatePitch(float angle);
	  void RotateRoll(float angle);
	  void updatePosition();

	  int frameCounter = 0;
	  std::vector<LavaBomb> lavaBombs;
	  void generateLavaBombs();
	  void updateLavaBombs();

	  bool isLavaCollideLava(LavaBomb a, LavaBomb b);
	  bool isLavaCollidePlane(LavaBomb a);
	  bool isLavaCollideGround(LavaBomb a);
	  bool isPLaneCollideGround();

	  void destroyLavaBomb();

	}; // class SceneModel

#endif
