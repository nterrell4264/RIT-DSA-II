#pragma once
#include "Vertex.h"

class Puzzle
{
public:
	Puzzle(int dimension = 1);
	~Puzzle();

	Vertex** board;
	int sideLength;
	int boardSize;
	int emptyIndex;

	Vertex* GetEmpty();
};

