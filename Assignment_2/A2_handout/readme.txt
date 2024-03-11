# COMP 5823M Assignment 2

Name: Simiao Wang
Student ID: 201702881
University Email: sc23s2w@leeds.ac.uk
Personal Email: mickeymiao2023@163.com
Completion Date: January 04, 2024
University of Leeds 2023-2024

## How to Execute My Code

Note: I only tested on feng_linux (due to account issues, the lab computer lacks a qmake environment and cannot configure environment variables).

### If you need to recompile

1. Enter the command `qmake -project QT+=opengl LIBS+=-lGLU`.
2. Enter the command `qmake`.
3. Enter the command `make`.
4. Enter the command `./A2_handout` to execute the program.

### If you want to execute the program directly

1. Enter the command `./A2_handout`.

## Code Functionalities

### SceneModel.cpp

This class primarily implements the determination and transformation of various states of characters, the logic for character movement, and the assessment of the relationship between characters and the height of the terrain. Additionally, it implements action blending.

### BVHData.cpp

This type is mainly used to implement the reading of BVH files, matrix transformations, and the rendering of skeletons between joints and joints.

