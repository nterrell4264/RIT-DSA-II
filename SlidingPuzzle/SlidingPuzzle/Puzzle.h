#pragma once
#include "Vertex.h"

#include <iostream>
#include <stdio.h>
using namespace std;

class Puzzle
{
public:
	Puzzle(int dimension = 1);
	~Puzzle();
	Puzzle(const Puzzle& other); //Copy constructor
	Puzzle& operator= (const Puzzle& other); //Copy assignment

	Vertex** board;
	int sideLength;
	int boardSize;
	int emptyIndex;

	void Display();
	Vertex* GetEmpty();
};

