#pragma once
#include "shader.h"
#include "Spinner.h"

//Window data
const GLint WIDTH = 800, HEIGHT = 600;
GLuint colorbuffer;

//Shape
Shape** rings;
const int ringCount = 8;
const int parts = 16;

Shape* MakeRing(float originX, float originY, float originZ, float ringRadius, float ringWidth, GLuint shader);

//Spin functionality
Spinner spinner;