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
#include <Quaternion.h>

// three local variables with the hardcoded file names
const char* flatLandModelName		= "./models/flatland.dem";
const char* stripeLandModelName	= "./models/stripeland.dem";
const char* rollingLandModelName	= "./models/rollingland.dem";
const char* sphereModelName		= "./models/spheroid.face";
const char* dodecahedronModelName	= "./models/dodecahedron.face";

// the speed of camera movement
const float cameraSpeed = 5.0;

// this is 60 fps nominal speed
const float frameTime = 0.0166667;	

// permanent downwards vector for gravity
const Cartesian3 gravity(0.0, 0.0, -9.8);

// radius of the sphere
const float sphereRadius = 1.0;

const Homogeneous4 sunDirection(0.5, -0.5, 0.3, 0.0);
const GLfloat groundColour[4] = { 0.2, 0.5, 0.2, 1.0 };
const GLfloat ballColour[4] = { 0.6, 0.6, 0.6, 1.0 };
const GLfloat sunAmbient[4] = {0.1, 0.1, 0.1, 1.0 };
const GLfloat sunDiffuse[4] = {0.7, 0.7, 0.7, 1.0 };
const GLfloat blackColour[4] = {0.0, 0.0, 0.0, 1.0};

// constructor
SceneModel::SceneModel()
	{ // constructor
	// load the object models from files
	sphereModel.ReadFileIndexedFace(sphereModelName);
	dodecahedronModel.ReadFileIndexedFace(dodecahedronModelName);
	flatLandModel.ReadFileTerrainData(flatLandModelName, 3);
	stripeLandModel.ReadFileTerrainData(stripeLandModelName, 3);
	rollingLandModel.ReadFileTerrainData(rollingLandModelName, 3);
	
	// set the reference for the terrain model to use
 	activeLandModel = &flatLandModel;
	
	// set the initial view matrix
	viewMatrix = Matrix4::Translate(Cartesian3(0.0, 15.0, -10.0));
	
	// and set the frame number to 0
	frameNumber = 0;

	// set flags for initial configuration
	useSphere = true;
		
	// and initial launch angle
	launchAngle = 0.0;
	
	// call the reset routine to initialise the ball position
	ResetPhysics();
	} // constructor

// routine that updates the scene for the next frame
void SceneModel::Update()
	{ // Update()
	// increment the frame counter
	frameNumber++;

	// The rest depends on whether we have the sphere or the dodecahedron.  
	// For simplicity, we will code it redundantly
	if (useSphere)
		{ // using the sphere
	
		// YOUR CODE GOES HERE

		} // using the sphere
	else
		{ // using the dodecahedron
	
		// YOUR CODE GOES HERE

		} // using the dodecahedron
	} // Update()

// routine to tell the scene to render itself
void SceneModel::Render()
	{ // Render()
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

	// set the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	
	// start with the identity
	glLoadIdentity();

	// add the final rotation from z-up to z-backwords
	glRotatef(-90.0, 1.0, 0.0, 0.0);

	// now compute the view matrix by combining camera translation & rotation
	columnMajorMatrix columnMajorViewMatrix = viewMatrix.columnMajor();
	glMultMatrixf(columnMajorViewMatrix.coordinates);

	// set the light position
	glLightfv(GL_LIGHT0, GL_POSITION, &(sunDirection.x));

	// and set a material colour for the ground
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, groundColour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackColour);
	glMaterialfv(GL_FRONT, GL_EMISSION, blackColour);

	// render the terrain
	activeLandModel->Render();

	// set the colour for the ball
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ballColour);

	// and update the modelview matrix

	// YOUR CODE GOES HERE
	// YOU WILL NEED TO SPECIFY LOCATION & ORIENTATION OF THE BALL HERE
	glTranslatef(0.0, 0.0, 0.0);

	// now render the ball
	if (useSphere)
	 	sphereModel.Render();
	else
		dodecahedronModel.Render();
	} // Render()	

// camera control events: WASD for motion
void SceneModel::EventCameraForward()
	{ // EventCameraForward()
	// update the camera matrix
	viewMatrix = Matrix4::Translate(Cartesian3(0.0, -1.0, 0.0) * cameraSpeed) * viewMatrix;
	} // EventCameraForward()

void SceneModel::EventCameraBackward()
	{ // EventCameraBackward()
	// update the camera matrix
	viewMatrix = Matrix4::Translate(Cartesian3(0.0, 1.0, 0.0) * cameraSpeed) * viewMatrix;
	} // EventCameraBackward()

void SceneModel::EventCameraLeft()
	{ // EventCameraLeft()
	// update the camera matrix
	viewMatrix = Matrix4::Translate(Cartesian3(1.0, 0.0, 0.0) * cameraSpeed) * viewMatrix;
	} // EventCameraLeft()
	
void SceneModel::EventCameraRight()
	{ // EventCameraRight()
	// update the camera matrix
	viewMatrix = Matrix4::Translate(Cartesian3(-1.0, 0.0, 0.0) * cameraSpeed) * viewMatrix;
	} // EventCameraRight()

// camera control events: RF for vertical motion
void SceneModel::EventCameraUp()
	{ // EventCameraUp()
	// update the camera matrix
	viewMatrix = Matrix4::Translate(Cartesian3(0.0, 0.0, -1.0) * cameraSpeed) * viewMatrix;
	} // EventCameraUp()
	
void SceneModel::EventCameraDown()
	{ // EventCameraDown()
	// update the camera matrix
	viewMatrix = Matrix4::Translate(Cartesian3(0.0, 0.0, 1.0) * cameraSpeed) * viewMatrix;
	} // EventCameraDown()

// camera rotation events: QE for left and right
void SceneModel::EventCameraTurnLeft()
	{ // EventCameraTurnLeft()
	// separate the translation & rotation
	Matrix4 rotation = viewMatrix.GetRotationMatrix();
	Cartesian3 translation = viewMatrix.GetTranslationVector();
	
	// find the delta of the rotation
	Matrix4 rotationDelta = Matrix4::RotateZ(2.0f);
	
	// update the translation vector from the rotation delta
	Cartesian3 newTranslation = rotationDelta * translation;

	// update the rotation matrix
	rotation = rotationDelta * rotation;

	// now update the view matrix
	viewMatrix = Matrix4::Translate(newTranslation) * rotation;
	} // EventCameraTurnLeft()

void SceneModel::EventCameraTurnRight()
	{ // EventCameraTurnRight()
	// separate the translation & rotation
	Matrix4 rotation = viewMatrix.GetRotationMatrix();
	Cartesian3 translation = viewMatrix.GetTranslationVector();
	
	// find the delta of the rotation
	Matrix4 rotationDelta = Matrix4::RotateZ(-2.0f);
	
	// update the translation vector from the rotation delta
	Cartesian3 newTranslation = rotationDelta * translation;

	// update the rotation matrix
	rotation = rotationDelta * rotation;

	// now update the view matrix
	viewMatrix = Matrix4::Translate(newTranslation) * rotation;
	} // EventCameraTurnRight()

// routine to reset the simulation
void SceneModel::ResetPhysics()
	{ // ResetPhysics()
	// use different code depending on the model
	if (useSphere)
		{ // sphere

		// YOUR CODE GOES HERE

		} // sphere
	else
		{ // dodecahedron
	
		// YOUR CODE GOES HERE

		} // dodecahedron

	} // ResetPhysics()
	
// routine to switch between flat land and rolling land
void SceneModel::SwitchLand()
	{ // SwitchLand()
	// toggle between terrains
	if (activeLandModel == &flatLandModel)
		activeLandModel = &stripeLandModel;
	else if (activeLandModel == &stripeLandModel)
		activeLandModel = &rollingLandModel;
	else if (activeLandModel == &rollingLandModel)
		activeLandModel = &flatLandModel;
	} // SwitchLand()
	
// routine to switch between sphere and dodecahedron
void SceneModel::SwitchModel()
	{ // SwitchModel()
	// toggle between models
	useSphere = !useSphere;
	// and reset the physics
	ResetPhysics();
	} // SwitchModel()
	
// routine to rotate launch direction to the left
void SceneModel::RotateLaunchLeft()
	{ // RotateLaunchLeft()
	// just change by 5 degrees
	launchAngle -= 5.0;
	} // RotateLaunchLeft()

// and to rotate to right
void SceneModel::RotateLaunchRight()
	{ // RotateLaunchRight()
	// just change by 5 degrees
	launchAngle += 5.0;
	} // RotateLaunchRight()

