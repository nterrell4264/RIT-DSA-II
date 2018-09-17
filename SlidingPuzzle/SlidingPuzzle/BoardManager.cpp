#include "stdafx.h"
#include "BoardManager.h"

#pragma region Constuctor/Destructor
BoardManager::BoardManager()
{
	puzzle = new Puzzle(1);
}

BoardManager::~BoardManager()
{
	delete puzzle;
}
#pragma endregion

#pragma region Puzzle Interfacing
void BoardManager::SetPuzzle(int dimension) {
	delete puzzle;
	puzzle = new Puzzle(dimension);
}

void BoardManager::ScramblePuzzle() {
	vector<Puzzle> moves;
	int nextMove;
	//Loop that makes a random amount of random moves
	for (int i = 0; i < rand() % 64 + 128; i++) {
		moves = AdjacencyDistances(puzzle->GetEmpty()->position);
		nextMove = rand() % moves.size;
		*puzzle = moves[nextMove];
	}
}

void BoardManager::DisplayPuzzle() {
	cout << "-------------" << endl;
	for (int i = 0; i < puzzle->boardSize; i += puzzle->sideLength) {
		for (int j = 0; j < puzzle->sideLength; j++) {
			cout << "|";
			if (i + j + 1 < 10) cout << " ";
			if (i + j + 1 == puzzle->boardSize) cout << "  ";
			else cout << puzzle->board[i + j]->number;
		}
		cout << "|" << endl;
	}
	cout << "-------------" << endl;
}

void BoardManager::SetShortestPath()
{
	if (pathLength > finalPathLength)
	{
		return;
	}

	if (finalPath != nullptr) //Deletes previous shortest path if it exists
	{
		delete[] finalPath;
	}
	//Creates and populates array with coordinates of path's vertices
	finalPathLength = pathLength;
	finalPath = new int[finalPathLength];
	for (int i = 0; i < pathLength; i++) {
		finalPath[i] = (*path)[i]->position;
	}
}
#pragma endregion

#pragma region Solution finding
int BoardManager::AStarPath(int index)
{
	Vertex* vertex = puzzle->board[index];
	if ((*vertex).visited < pathLength - 3) { //Spot has been empty in the last three moves (only possible if it was just moved into or a square is about to be made)
		return INT_MAX;
	}
	//Add vertex to path
	(*path).push_back(vertex);
	pathLength++;
	if (CheckProgress(path->data) == puzzle->boardSize) { //Reached end
		SetShortestPath();
		(*path).pop_back();
		pathLength--;
		return pathLength;
	}
	(*vertex).visited = pathLength;
	//Recursively finds next step, in order of distance from the endpoint
	int curPath = INT_MAX;
	int shortPath = INT_MAX;
	for (Puzzle neighbor : AdjacencyDistances(index)) {
		curPath = AStarPath(neighbor.emptyIndex);
		if (curPath < shortPath) shortPath = curPath;
	}
	//Removes vertex from path once we're done with it
	(*path).pop_back();
	pathLength--;
	return shortPath;
}

//Calculates the closeness of each move into the empty position and returns it
vector<Puzzle> BoardManager::AdjacencyDistances(int index) {
	vector<Puzzle> neighbors(0);
	//Finds valid neighbors
	if (index % puzzle->sideLength < puzzle->sideLength - 1) { //Right
		neighbors.push_back(SimulateMove(index + 1));
	}
	if (index / puzzle->sideLength > 0) { //Up
		neighbors.push_back(SimulateMove(index - puzzle->sideLength));
	}
	if (index % puzzle->sideLength > 0) { //Left
		neighbors.push_back(SimulateMove(index - 1));
	}
	if (index / puzzle->sideLength != puzzle->sideLength - 1) { //Down
		neighbors.push_back(SimulateMove(index + puzzle->sideLength));
	}
	sort(neighbors.begin(), neighbors.end(), sortMove); //Sorts list in ascending order by heuristics value
	return neighbors;
}

Puzzle BoardManager::SimulateMove(int moveIndex) {
	Puzzle newPuzzle = *puzzle;
	Vertex* tempVertex = newPuzzle.board[newPuzzle.emptyIndex];
	newPuzzle.board[newPuzzle.emptyIndex] = newPuzzle.board[moveIndex];
	newPuzzle.board[moveIndex] = tempVertex;
	newPuzzle.emptyIndex = moveIndex;
	return newPuzzle;
}

bool sortMove(const Puzzle a, const Puzzle b) {
	return CheckProgress(a) < CheckProgress(b);
}

//Returns how many tiles are in their final position
int CheckProgress(Puzzle checkBoard) {
	int closeness = 0;
	for (int i = 0; i < checkBoard.boardSize; i++) { //Checks that all numbers are in place (last number represents the empty space)
		if (checkBoard.board[i]->number == i + 1) closeness++;
	}
	return closeness;
}
#pragma endregion