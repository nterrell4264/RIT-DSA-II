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
	int* finalPath = nullptr;
	int finalPathLength = INT_MAX;
	//Hill-climbing variables
	Puzzle* current;
	vector<Puzzle*>* seenPuzzles;
	#pragma endregion

	#pragma region Algorithms
	int AStarPath(Puzzle* move); //A* recursive function
	bool HillPath(); //Hill-climbing iterative function
	//Helper functions
	void MakeMove(int moveIndex);
	Puzzle* SimulateMove(Puzzle* moveBoard, int moveIndex);

	vector<Puzzle*>* AdjacencyDistances(Puzzle* move); //Returns a sorted list of possible moves using the distance heuristic
	bool NotRepeat(Puzzle* checkBoard);
	void SetShortestPath();
	#pragma endregion
};

bool sortMove(Puzzle* const a, Puzzle* const b); //Function that compares two heuristic values to find the lowest
int CheckProgress(Puzzle* checkBoard);

