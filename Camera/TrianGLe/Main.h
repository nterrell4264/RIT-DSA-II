#pragma once
#include "Include.h"

//Window data
const GLint WIDTH = 800, HEIGHT = 600;
GLuint colorbuffer;

//Cameras
Camera** cameras;
Camera* mainCamera;
int camIndex = 0;
bool camKeyPressed = false;

//Shape stuff
Shape** rings;
//Mesh* ringMesh = nullptr;
const int ringCount = 10;
const int parts = 16;

Shape* MakeRing(float originX, float originY, float originZ, float ringRadius, float ringWidth, GLuint shader);

void mouseWrapper(GLFWwindow* window, double xpos, double ypos);