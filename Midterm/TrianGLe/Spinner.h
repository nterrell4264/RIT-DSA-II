#pragma once
#include "Shape.h"

#include <tuple>
using namespace std;

class Spinner
{
public:
	Spinner(Shape** shapes, int count);
	Spinner();
	~Spinner();

	tuple<Shape*,bool>*** objects; //tuple is used for Dijkstra's
	Shape* starter;
	void StartSpin();
	void StopSpin(Shape** shapes, int shapeCount);
	void SpinOff(Shape** shapes, int shapeCount); //Makeshift spinner function because real one doesn't work
private:
	void SpinOut(int x, int y, int z); //Recursive spinning algorithm
};

