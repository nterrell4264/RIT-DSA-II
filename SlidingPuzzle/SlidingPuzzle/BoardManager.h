#pragma once

#include <algorithm>
#include <vector>
#include <stack>

#include "Puzzle.h"

#include <iostream>
#include <stdio.h>
using namespace std;

class BoardManager
{
public:
	BoardManager();
	~BoardManager();

	#pragma region Variables
	Puzzle* puzzle;
	//Solving variables
	vector<Vertex*>* path = nullptr;
	int pathLength = 0;
	int* finalPath = nullptr;
	int finalPathLength = INT_MAX;
	#pragma endregion

	#pragma region Functions
	void SetPuzzle(int dimension);
	void ScramblePuzzle();
	void DisplayPuzzle();
	void SetShortestPath();
	#pragma endregion
private:
	#pragma region Algorithms
	int HillPath(); //Hill-climbing iterative function
	int AStarPath(int index); //A* recursive function
	//Helper functions
	Puzzle SimulateMove(int moveIndex);
	vector<Puzzle> AdjacencyDistances(int index); //Returns a sorted list of possible moves using the distance heuristic
	#pragma endregion
};

bool sortMove(const Puzzle a, const Puzzle b); //Function that compares two heuristic values to find the lowest
int CheckProgress(Puzzle checkBoard);

