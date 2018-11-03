#pragma once
#include "Include.h"

//Window data
const GLint WIDTH = 800, HEIGHT = 600;
GLuint colorbuffer;
Camera* camera;

//Shape
Shape** rings;
const int ringCount = 10;
const int parts = 16;

Shape* MakeRing(float originX, float originY, float originZ, float ringRadius, float ringWidth, GLuint shader);