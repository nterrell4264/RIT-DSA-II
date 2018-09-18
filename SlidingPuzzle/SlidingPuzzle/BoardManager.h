#pragma once

#include <algorithm>
#include <vector>
#include <stack>

#include "Puzzle.h"

class BoardManager
{
public:
	BoardManager();
	~BoardManager();

	#pragma region Functions
	void SetPuzzle(int dimension);
	void ScramblePuzzle();
	void DisplayPuzzle();

	void SolveAStar();
	void SolveHill();
	#pragma endregion
private:

	#pragma region Variables
	Puzzle* puzzle = nullptr;
	//Solving variables
	vector<Puzzle*>* path = nullptr;
	int pathLength = 0;
	int* finalPath = nullptr;
	int finalPathLength = INT_MAX;
	#pragma endregion

	#pragma region Algorithms
	int HillPath(); //Hill-climbing iterative function
	int AStarPath(Puzzle* move); //A* recursive function
	//Helper functions
	void MakeMove(int moveIndex);
	Puzzle* SimulateMove(Puzzle* moveBoard, int moveIndex);

	vector<Puzzle*>* AdjacencyDistances(Puzzle* move); //Returns a sorted list of possible moves using the distance heuristic
	void SetShortestPath();
	#pragma endregion
};

bool sortMove(Puzzle* const a, Puzzle* const b); //Function that compares two heuristic values to find the lowest
int CheckProgress(Puzzle* checkBoard);

