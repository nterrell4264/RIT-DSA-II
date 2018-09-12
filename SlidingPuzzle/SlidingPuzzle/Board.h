#pragma once

#include <algorithm>
#include <vector>
#include "Vertex.h"
#include <stack>

#include <iostream>
#include <stdio.h>
using namespace std;

class Board
{
public:
	Board(int dimension);
	~Board();

	#pragma region Variables
	Vertex** board;
	int sideLength = 1;
	int boardSize;
	int emptyIndex;
	//Solving variables
	vector<Vertex*>* path = nullptr;
	int pathLength = 0;
	int* finalPath = nullptr;
	int finalPathLength = INT_MAX;
	#pragma endregion

	#pragma region Functions
	void ScramblePuzzle();
	void DisplayPuzzle();
	#pragma endregion
private:
	#pragma region Algorithms
	int HillPath(); //Hill-climbing iterative function
	int AStarPath(int index); //A* recursive function
	#pragma endregion

	#pragma region Helper functions
	Vertex** SimulateMove(int moveIndex);
	vector<Vertex**> AdjacencyDistances(Vertex* vertex); //Returns a sorted list of a vertex's neighbors using the distance heuristic
	int CheckProgress(Vertex** checkBoard);
	void SetShortestPath();
	#pragma endregion
};

bool sortMove(const Vertex** a, const Vertex** b); //Function that compares two heuristic values to find the lowest

