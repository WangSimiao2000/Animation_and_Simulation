# COMP 5823M Assignment 1

Name: Simiao Wang
Student ID: 201702881
University Email: sc23s2w@leeds.ac.uk
Personal Email: mickeymiao2023@163.com
Completion Date: November 16, 2023
University of Leeds 2023-2024

## Notes

1. The main content of this assignment code is concentrated in SceneModel.cpp, LavaBomb.cpp, and FlightSimulatorWidget.cpp.
2. Despite extensive contemplation and multiple code revisions (it is currently 3:21 AM, and I am still modifying the code), a unresolved bug occurred during the completion of task objective c. Please refer to the "Bug Description" section for specifics.
3. If you wish to check the completion status of parts a or b of my assignment, please open the folder named sc23s2w_A1_ab. This code removes the modifications I made while completing task C, only implementing the requirements of parts a and b.
4. To check the completion status of part c of my assignment, please open the folder named sc23s2w_A1_c.

## Bug Description

After completing the steps for calculating and determining the aircraft's (camera's) height relative to the ground, running the program and steering the aircraft towards the volcano results in a program exit with the error: "Segmentation fault (core dumped)." I believe my code logic is capable of successfully achieving the goals of part c. However, due to this bug, I cannot conduct proper testing, which is perplexing. I hope the instructor can review my code logic and assign an appropriate score.

## How to Execute My Code

Note: I only tested on feng_linux (due to account issues, the lab computer lacks a qmake environment and cannot configure environment variables).

### If you need to recompile

1. Enter the command `qmake -project QT+=opengl LIBS+=-lGLU`.
2. Enter the command `qmake`.
3. Enter the command `make`.
4. Enter the command `./A1_handout` to execute the program.

### If you want to execute the program directly

1. Enter the command `./A1_handout`.

## Code Functionalities

### FlightSimulatorWidget.cpp

This code maps various keyboard keys and calls various methods from SceneModel.cpp to adjust speed, yaw angle, pitch angle, and roll angle.

### SceneModel.cpp

This part is the main logical part of the code and completes the following functionalities:
1. Initializes the world in the constructor, ensuring the ground is displayed correctly below the aircraft (camera).
2. Initializes the light source in the constructor, ensuring lighting displays map colors correctly and is not affected by position changes.
3. In Render(), correctly renders all lava bombs.
4. Methods such as RotateYaw(), RotatePitch(), RotateRoll(), ChangeSpeed(), and SetSpeed() control speed and angles.
5. In updatePosition(), transforms world coordinates to OpenGL coordinates, calculates aircraft ground coordinates, and calculates light OpenGL matrices.
6. generateLavaBombs() implements lava bomb generation.
7. updateLavaBombs() calculates lava bomb movement and updates the lava bomb matrix each frame.
8. isLavaCollideLava() determines lava bomb collisions.
9. isLavaCollidePlane() determines lava bomb collisions with the aircraft.
10. isLavaCollideGround() determines lava bomb collisions with the ground.
11. isPlaneCollideGround() determines aircraft collisions with the ground.
12. destroyLavaBomb() destroys one of two colliding lava bombs and handles lava bomb destruction when it reaches the ground.

### LavaBomb.cpp

This code initializes certain lava bomb properties and calculates its position and velocity each frame based on gravity acceleration during updates.

======== ======== ======== ======== ======== ======== ========= ======== ======== ======== ========

# COMP 5823M Assignment 1

姓名: 王思淼
学号: 201702881
学校邮箱: sc23s2w@leeds.ac.uk
生活邮箱: mickeymiao2023@163.com
完成日期: 2023年11月16日
University of leeds 2023-2024

## 注意事项

1. 本作业代码的主要内容集中于SceneModel.cpp, LavaBomb.cpp, 以及FlightSimulatorWidget.cpp中
2. 尽管我思考了很久并且多次修改代码(我现在是凌晨3:21,我仍在修改代码), 但是任务目标的c项的完成过程中仍出现了未解决的bug, 具体请看"bug描述"部分
3. 如果想要检查我的a或者b部分的作业完成情况, 请打开名为sc23s2w_A1_ab的文件夹, 这份代码删除了我在完成作业C时进行的修改, 仅实现了作业的ab两部分的要求
4. 如果想要检查我的c部分的作业完成情况, 请打开名为sc23s2w_A1_c的文件夹

## BUG描述

我在结束计算飞机(摄像机)相对于地面高度计算和判断的步骤后, 运行程序并控制飞机驶向火山, 在快要抵达火山的位置时, 程序退出并报错:"Segmentation fault (core dumped)", 我认为我的代码逻辑是可以正常完成c部分的目标的, 但是因为这个Bug无法正常进行测试, 让我感到奇怪, 也希望老师能检查我的代码逻辑并给我适当的分数

## 如何执行我的代码

注意, 我只在feng_linux上进行测试(由于账号问题, lab的电脑没有qmake环境, 并且也无法配置环境变量)

### 如果你需要重新编译

1. 输入指令qmake -project QT+=opengl LIBS+=-lGLU
2. 输入指令qmake
3. 输入指令make
4. 输入指令./A1_handout执行程序

### 如果你想直接执行程序

1. 输入指令./A1_handout

## 各代码功能

### FlightSimulatorWidget.cpp

此代码中完成了各个键盘按键的映射, 并且调用SceneModel.cpp里的各项方法来对速度, 偏航角度, 桶滚角度, 俯仰角度进行调整

### SceneModel.cpp

此部分为代码的主要逻辑部分, 主要完成了以下功能:
1. 在构造函数中完成了对世界的初始化, 使得地面能正常显示于飞机(相机)的下方
2. 在构造函数中完成了光源的初始化, 使得光照能使地图正常显示颜色, 并且不受位置移动影响
3. 在Render()中完成了对所有岩浆球的正确渲染
4. RotateYaw()方法,RotatePitch()方法, RotateRoll()方法, ChangeSpeed()方法, SetSpeed()方法完成了对速度角度的控制
5. 在updatePosition()中完成了对world2OpenGLMatrix的变换, 完成了对飞机的地面坐标的计算, 完成了对light2OpenGLMatrix的计算
6. generateLavaBombs()完成了对岩浆球生成的实现
7. updateLavaBombs()完成了对岩浆球每一帧运动的计算以及岩浆球矩阵的更新
8. isLavaCollideLava()完成了对岩浆球间互相碰撞的判断
9. isLavaCollidePlane()完成了对岩浆球碰撞飞机的判断
10. isLavaCollideGround()完成了对岩浆球于地面的碰撞判断
11. isPLaneCollideGround()完成了飞机与地面碰撞的判断
12. destroyLavaBomb()完成了对两个相撞岩浆球的其中一个进行销毁, 也完成了岩浆球落到地面进行销毁的任务

### LavaBomb.cpp

此代码完成了对岩浆球部分属性的初始化, 完成了岩浆球每帧更新时根据重力加速度对其位置和速度的计算