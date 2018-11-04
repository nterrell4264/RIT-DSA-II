#pragma once
#include "Include.h"

class Shape
{
public:
	Shape(float xPos = 0, float yPos = 0, float zPos = 0);
	~Shape();

	//Data
	vec3 position;
	vec3 rotation;

	Mesh* mesh;

	//Data-related functions
	void Update();
	void Translate(float dx = 0.f, float dy = 0.f, float dz = 0.f);
	void Rotate(float rx = 0.f, float ry = 0.f, float rz = 0.f);
	void Reset();
};

