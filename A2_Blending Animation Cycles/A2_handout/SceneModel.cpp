///////////////////////////////////////////////////
//
//	Hamish Carr
//	October, 2023
//
//	------------------------
//	SceneModel.cpp
//	------------------------
//	
//	The model of the scene
//
//	
///////////////////////////////////////////////////

#include "SceneModel.h"
#include <math.h>

// three local variables with the hardcoded file names
const char* groundModelName		= "./models/randomland.dem";
const char* characterModelName	= "./models/human_lowpoly_100.obj";
const char* motionBvhStand		= "./models/stand.bvh";
const char* motionBvhRun		= "./models/fast_run.bvh";
const char* motionBvhveerLeft	= "./models/veer_left.bvh";
const char* motionBvhveerRight	= "./models/veer_right.bvh";
const float cameraSpeed = 0.5;

const Homogeneous4 sunDirection(0.5, -0.5, 0.3, 1.0);
const GLfloat groundColour[4] = { 0.2, 0.5, 0.2, 1.0 };
const GLfloat boneColour[4] = { 0.7, 0.7, 0.4, 1.0 };
const GLfloat sunAmbient[4] = {0.1, 0.1, 0.1, 1.0 };
const GLfloat sunDiffuse[4] = {0.7, 0.7, 0.7, 1.0 };
const GLfloat blackColour[4] = {0.0, 0.0, 0.0, 1.0};

// constructor
SceneModel::SceneModel() : characterState(STAND)
	{ // constructor
	// load the object models from files
	groundModel.ReadFileTerrainData(groundModelName, 3);

	// load the animation data from files
	restPose.ReadFileBVH(motionBvhStand);
	runCycle.ReadFileBVH(motionBvhRun);
	veerLeftCycle.ReadFileBVH(motionBvhveerLeft);
	veerRightCycle.ReadFileBVH(motionBvhveerRight);

	tempCycle.ReadFileBVH(motionBvhStand);

	// set the world to opengl matrix
	world2OpenGLMatrix = Matrix4::RotateX(90.0);
	CameraTranslateMatrix = Matrix4::Translate(Cartesian3(-5, 15, -15.5));
	CameraRotationMatrix = Matrix4::RotateX(-30.0) * Matrix4::RotateZ(15.0);

	// initialize the character's position and rotation
	EventCharacterReset();

	// and set the frame number to 0
	frameNumber = 0;

	tempFlag = 0;

	} // constructor

// routine that updates the scene for the next frame
void SceneModel::Update()
	{ // Update()
	// increment the frame counter
	frameNumber++;
	// change height depends on the height of secen model
	characterLocation.z = groundModel.getHeight(characterLocation.x,characterLocation.y);
	// character move
	float angle = 5.0f;
	if(characterState == RUN)
	  {
	    Cartesian3 forwardDirection = characterRotation * Cartesian3(0.0f,-1.0f,0.0f);
	    characterLocation = characterLocation + forwardDirection * 0.5f;
	  }
	else if(characterState == VEER_LEFT)
	  {
	    Matrix4 newRotation = Matrix4::RotateZ(-angle);
	    characterRotation = characterRotation * newRotation;
	  }
	else if(characterState == VEER_RIGHT)
	  {
	    Matrix4 newRotation = Matrix4::RotateZ(angle);
	    characterRotation = characterRotation * newRotation;
	  }
	else if(characterState == STAND2RUN)
	  {
	    if(tempFlag == 12)
	      {
		//std::cout << "stop blend stand to run" << std::endl;
		characterState = RUN;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		//std::cout << "blending stand to run" << std::endl;
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = restPose.boneRotations[(frameNumber%1)][jointIndex];
		    Cartesian3 rotation2 = runCycle.boneRotations[(frameNumber%17)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }
	    
	    Cartesian3 forwardDirection = characterRotation * Cartesian3(0.0f,-1.0f,0.0f);
	    characterLocation = characterLocation + forwardDirection * 0.5f;
	  }
	else if(characterState == LEFT2RUN)
	  {
	    if(tempFlag == 12)
	      {
		//std::cout << "stop blend stand to run" << std::endl;
		characterState = RUN;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		//std::cout << "blending stand to run" << std::endl;
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = veerLeftCycle.boneRotations[(frameNumber%33)][jointIndex];
		    Cartesian3 rotation2 = runCycle.boneRotations[(frameNumber%17)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }
	    
	    Cartesian3 forwardDirection = characterRotation * Cartesian3(0.0f,-1.0f,0.0f);
	    characterLocation = characterLocation + forwardDirection * 0.5f;
	  }
	else if(characterState == RIGHT2RUN)
	  {
	    if(tempFlag == 12)
	      {
		//std::cout << "stop blend stand to run" << std::endl;
		characterState = RUN;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		//std::cout << "blending stand to run" << std::endl;
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = veerRightCycle.boneRotations[(frameNumber%33)][jointIndex];
		    Cartesian3 rotation2 = runCycle.boneRotations[(frameNumber%17)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }	    
	    Cartesian3 forwardDirection = characterRotation * Cartesian3(0.0f,-1.0f,0.0f);
	    characterLocation = characterLocation + forwardDirection * 0.5f;
	  }
	else if(characterState == RUN2STAND)
	  {
	    if(tempFlag == 12)
	      {
		characterState = STAND;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = runCycle.boneRotations[(frameNumber%17)][jointIndex];
		    Cartesian3 rotation2 = restPose.boneRotations[(frameNumber%1)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }	    
	    Cartesian3 forwardDirection = characterRotation * Cartesian3(0.0f,-1.0f,0.0f);
	    characterLocation = characterLocation + forwardDirection * 0.25f;
	  }
	else if(characterState == LEFT2STAND)
	  {
	    if(tempFlag == 12)
	      {
		characterState = STAND;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = veerLeftCycle.boneRotations[(frameNumber%33)][jointIndex];
		    Cartesian3 rotation2 = restPose.boneRotations[(frameNumber%1)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }	    
	    Matrix4 newRotation = Matrix4::RotateZ(-angle);
	    characterRotation = characterRotation * newRotation;
	  }
	else if(characterState == RIGHT2STAND)
	  {
	    if(tempFlag == 12)
	      {
		characterState = STAND;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = veerRightCycle.boneRotations[(frameNumber%33)][jointIndex];
		    Cartesian3 rotation2 = restPose.boneRotations[(frameNumber%1)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }	    
	    Matrix4 newRotation = Matrix4::RotateZ(angle);
	    characterRotation = characterRotation * newRotation;
	  }
	else if(characterState == STAND2LEFT)
	  {
	    if(tempFlag == 12)
	      {
		characterState = VEER_LEFT;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = restPose.boneRotations[(frameNumber%1)][jointIndex];
		    Cartesian3 rotation2 = veerLeftCycle.boneRotations[(frameNumber%33)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }	    
	    Matrix4 newRotation = Matrix4::RotateZ(-angle);
	    characterRotation = characterRotation * newRotation;
	  }
	else if(characterState == RUN2LEFT)
	  {
	    if(tempFlag == 12)
	      {
		characterState = VEER_LEFT;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = runCycle.boneRotations[(frameNumber%17)][jointIndex];
		    Cartesian3 rotation2 = veerLeftCycle.boneRotations[(frameNumber%33)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }	    
	    Matrix4 newRotation = Matrix4::RotateZ(-angle);
	    characterRotation = characterRotation * newRotation;
	  }
	else if(characterState == RIGHT2LEFT)
	  {
	    if(tempFlag == 12)
	      {
		characterState = VEER_LEFT;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = veerRightCycle.boneRotations[(frameNumber%33)][jointIndex];
		    Cartesian3 rotation2 = veerLeftCycle.boneRotations[(frameNumber%33)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }	    
	    Matrix4 newRotation = Matrix4::RotateZ(-angle);
	    characterRotation = characterRotation * newRotation;
	  }
	else if(characterState == STAND2RIGHT)
	  {
	    if(tempFlag == 12)
	      {
		characterState = VEER_RIGHT;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = restPose.boneRotations[(frameNumber%1)][jointIndex];
		    Cartesian3 rotation2 = veerRightCycle.boneRotations[(frameNumber%33)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }	    
	    Matrix4 newRotation = Matrix4::RotateZ(angle);
	    characterRotation = characterRotation * newRotation;
	  }
	else if(characterState == RUN2RIGHT)
	  {
	    if(tempFlag == 12)
	      {
		characterState = VEER_RIGHT;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = runCycle.boneRotations[(frameNumber%17)][jointIndex];
		    Cartesian3 rotation2 = veerRightCycle.boneRotations[(frameNumber%33)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }	    
	    Matrix4 newRotation = Matrix4::RotateZ(angle);
	    characterRotation = characterRotation * newRotation;
	  }
	else if(characterState == LEFT2RIGHT)
	  {
	    if(tempFlag == 12)
	      {
		characterState = VEER_RIGHT;
		tempFlag = 0;
	      }
	    else if(tempFlag < 12)
	      {
		tempFlag++;
		for(size_t jointIndex = 0; jointIndex < tempCycle.all_joints.size(); ++jointIndex)
		  {
		    Cartesian3 rotation1 = veerLeftCycle.boneRotations[(frameNumber%33)][jointIndex];
		    Cartesian3 rotation2 = veerRightCycle.boneRotations[(frameNumber%33)][jointIndex];
		    float weight = (tempFlag+1)/12.0f;
		    tempCycle.boneRotations[0][jointIndex] = (1-weight) * rotation1 + weight * rotation2;
		  }
	      }	    
	    Matrix4 newRotation = Matrix4::RotateZ(angle);
	    characterRotation = characterRotation * newRotation;
	  }
	} // Update()

// routine to tell the scene to render itself
void SceneModel::Render()
	{ // Render()
	
	  //std::cout << frameNumber << std::endl;
	  //std::cout << "" << std::endl;
	  
	// enable Z-buffering
	glEnable(GL_DEPTH_TEST);
	
	// set lighting parameters
	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, blackColour);
	glLightfv(GL_LIGHT0, GL_EMISSION, blackColour);
	
	// background is sky-blue
	glClearColor(0.7, 0.7, 1.0, 1.0);

	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// compute the view matrix by combining camera translation, rotation & world2OpenGL
	viewMatrix = world2OpenGLMatrix * CameraRotationMatrix * CameraTranslateMatrix;

	// compute the light position
  	Homogeneous4 lightDirection = world2OpenGLMatrix * CameraRotationMatrix * sunDirection;
  	
  	// turn it into Cartesian and normalise
  	Cartesian3 lightVector = lightDirection.Vector().unit();

	// and set the w to zero to force infinite distance
 	lightDirection.w = 0.0;
 	 	
	// pass it to OpenGL
	glLightfv(GL_LIGHT0, GL_POSITION, &(lightVector.x));

	// and set a material colour for the ground
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, groundColour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackColour);
	glMaterialfv(GL_FRONT, GL_EMISSION, blackColour);

	// render the terrain
	groundModel.Render(viewMatrix);

	// culculate the character
	Matrix4 characterViewMatrix = viewMatrix;
	Matrix4 characterTranslation = Matrix4::Translate(characterLocation);
	Matrix4 characterTransformation = characterTranslation * characterRotation;
	characterViewMatrix = characterViewMatrix * characterTransformation;
	
	// now set the colour to draw the bones
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, boneColour);
	
	//render the character
	switch(characterState){
	case STAND:
	  restPose.Render(characterViewMatrix, 0.05, (frameNumber%1));
	  std::cout<<"stand"<<std::endl;
	  break;
	case RUN:;
	  runCycle.Render(characterViewMatrix, 0.05, (frameNumber%17));
	  std::cout<<"run"<<std::endl;
	  break;
	case VEER_LEFT:
	  veerLeftCycle.Render(characterViewMatrix, 0.05, (frameNumber%33));
	  std::cout<<"veer left"<<std::endl;
	  break;
	case VEER_RIGHT:
	  veerRightCycle.Render(characterViewMatrix, 0.05, (frameNumber%33));
	  std::cout<<"veer right"<<std::endl;
	  break;
	default:
	  tempCycle.Render(characterViewMatrix, 0.05, (frameNumber%1));
	  std::cout<<"blending"<<std::endl;
	}
	} // Render()	

// camera control events: WASD for motion
void SceneModel::EventCameraForward()
	{ // EventCameraForward()
	// update the camera matrix
	CameraTranslateMatrix = CameraTranslateMatrix * CameraRotationMatrix.transpose() * Matrix4::Translate(Cartesian3(0.0f, -cameraSpeed, 0.0f)) * CameraRotationMatrix;
	} // EventCameraForward()

void SceneModel::EventCameraBackward()
	{ // EventCameraBackward()
	// update the camera matrix
	CameraTranslateMatrix = CameraTranslateMatrix * CameraRotationMatrix.transpose() * Matrix4::Translate(Cartesian3(0.0f, cameraSpeed, 0.0f)) * CameraRotationMatrix;
	} // EventCameraBackward()

void SceneModel::EventCameraLeft()
	{ // EventCameraLeft()
	// update the camera matrix
	CameraTranslateMatrix = CameraTranslateMatrix * CameraRotationMatrix.transpose() * Matrix4::Translate(Cartesian3(cameraSpeed, 0.0f, 0.0f)) * CameraRotationMatrix;
	} // EventCameraLeft()
	
void SceneModel::EventCameraRight()
	{ // EventCameraRight()
	// update the camera matrix
	CameraTranslateMatrix = CameraTranslateMatrix * CameraRotationMatrix.transpose() * Matrix4::Translate(Cartesian3(-cameraSpeed, 0.0f, 0.0f)) * CameraRotationMatrix;
	} // EventCameraRight()

// camera control events: RF for vertical motion
void SceneModel::EventCameraUp()
	{ // EventCameraUp()
	// update the camera matrix
	CameraTranslateMatrix = CameraTranslateMatrix * CameraRotationMatrix.transpose() * Matrix4::Translate(Cartesian3(0.0f, 0.0f, -cameraSpeed)) * CameraRotationMatrix;
	} // EventCameraUp()
	
void SceneModel::EventCameraDown()
	{ // EventCameraDown()
	// update the camera matrix
	CameraTranslateMatrix = CameraTranslateMatrix * CameraRotationMatrix.transpose() * Matrix4::Translate(Cartesian3(0.0f, 0.0f, cameraSpeed)) * CameraRotationMatrix;
	} // EventCameraDown()

// camera rotation events: QE for left and right
void SceneModel::EventCameraTurnLeft()
	{ // EventCameraTurnLeft()
	CameraRotationMatrix = CameraRotationMatrix * Matrix4::RotateZ(2.0f);
	} // EventCameraTurnLeft()

void SceneModel::EventCameraTurnRight()
	{ // EventCameraTurnRight()
	CameraRotationMatrix = CameraRotationMatrix * Matrix4::RotateZ(-2.0f);
	} // EventCameraTurnRight()
	
// character motion events: arrow keys for forward, backward, veer left & right
void SceneModel::EventCharacterTurnLeft()
	{ // EventCharacterTurnLeft()
	  if(characterState == STAND)
	    {
	      characterState = STAND2LEFT;
	    }
	  else if(characterState == VEER_RIGHT)
	    {
	      characterState = RIGHT2LEFT;
	    }
	  else if(characterState == RUN)
	    {
	      characterState = RUN2LEFT;
	    }	
	} // EventCharacterTurnLeft()
	
void SceneModel::EventCharacterTurnRight()
	{ // EventCharacterTurnRight()
	  if(characterState == STAND)
	    {
	      characterState = STAND2RIGHT;
	    }
	  else if(characterState == VEER_LEFT)
	    {
	      characterState = LEFT2RIGHT;
	    }
	  else if(characterState == RUN)
	    {
	      characterState = RUN2RIGHT;
	    }	
	} // EventCharacterTurnRight()
	
void SceneModel::EventCharacterForward()
	{ // EventCharacterForward()
	  if(characterState == STAND)
	    {
	      characterState = STAND2RUN;
	    }
	  else if(characterState == VEER_LEFT)
	    {
	      characterState = LEFT2RUN;
	    }
	  else if(characterState == VEER_RIGHT)
	    {
	      characterState = RIGHT2RUN;
	    }
	} // EventCharacterForward()
	
void SceneModel::EventCharacterBackward()
	{ // EventCharacterBackward()
	  if(characterState == RUN)
	    {
	      characterState = RUN2STAND;
	    }
	  else if(characterState == VEER_LEFT)
	    {
	      characterState = LEFT2STAND;
	    }
	  else if(characterState == VEER_RIGHT)
	    {
	      characterState = RIGHT2STAND;
	    }
	} // EventCharacterBackward()

// reset character to original position: p
void SceneModel::EventCharacterReset()
	{ // EventCharacterReset()
	this->characterLocation = Cartesian3(0, 0, 0);
	this->characterRotation = Matrix4::Identity();
	} // EventCharacterReset()
  
