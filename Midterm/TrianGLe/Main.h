#pragma once
#include "shader.h"
#include "Shape.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Window data
const GLint WIDTH = 800, HEIGHT = 600;
GLuint colorbuffer;

//Shape
Shape** rings;
const int parts = 16;

//Functions
Shape* MakeRing(float originX, float originY, float originZ, float ringRadius, float ringWidth, GLuint shader);