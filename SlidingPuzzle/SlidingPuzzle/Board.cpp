#include "stdafx.h"
#include "Board.h"


Board::Board(int dimension)
{
	sideLength = dimension;
	boardSize = sideLength * sideLength;
	if (board == nullptr) {
		board = new Vertex*[boardSize];
		for (int i = 0; i < boardSize; i += sideLength) {
			for (int j = 0; j < sideLength; j++) {
				board[i + j] = new Vertex(i + j);
			}
		}
	}
	emptyIndex = boardSize - 1;
}

Board::~Board()
{
	delete[] board;
}

void Board::ScramblePuzzle() {

}

void Board::DisplayPuzzle() {
	cout << "-------------" << endl;
	for (int i = 0; i < boardSize; i += sideLength) {
		for (int j = 0; j < sideLength; j++) {
			cout << "|";
			if (i + j + 1 < 10) cout << " ";
			if (i + j + 1 == boardSize) cout << "  ";
			else cout << *(board + i + j);
		}
		cout << "|" << endl;
	}
	cout << "-------------" << endl;
}

int Board::AStarPath(int index)
{
	Vertex* vertex = board[index];
	if ((*vertex).visited < pathLength - 3) return INT_MAX;
	//Add vertex to path
	(*path).push_back(vertex);
	pathLength++;
	if (CheckProgress() == boardSize) { //Reached end
		SetShortestPath();
		(*path).pop_back();
		pathLength--;
		return pathLength;
	}
	(*vertex).visited = pathLength;
	//Recursively finds next step, in order of distance from the endpoint
	int curPath = INT_MAX;
	int shortPath = INT_MAX;
	for (Vertex* neighbor : AdjacencyDistances(vertex)) {
		curPath = AStarPath((*neighbor).position);
		if (curPath < shortPath) shortPath = curPath;
	}
	//Removes vertex from path once we're done with it
	(*path).pop_back();
	pathLength--;
	return shortPath;
}

vector<Vertex**> Board::AdjacencyDistances(Vertex* vertex) {
	vector<Vertex**> neighbors(0);
	//Finds valid neighbors
	if (*((*vertex).adjacencies)) { //Right
		neighbors.push_back(SimulateMove((*vertex).position + 1));
	}
	if (*((*vertex).adjacencies + 1)) { //Up
		neighbors.push_back(board[(*vertex).position - sideLength]);
	}
	if (*((*vertex).adjacencies + 2)) { //Left
		neighbors.push_back(board[(*vertex).position - 1]);
	}
	if (*((*vertex).adjacencies + 3)) { //Down
		neighbors.push_back(board[(*vertex).position + sideLength]);
	}
	sort(neighbors.begin(), neighbors.end(), sortMove); //Sorts list in ascending order by heuristics value
	return neighbors;
}

bool sortMove(const Vertex** a, const Vertex** b) {
	return CheckProgress(a) < CheckProgress(b);
}

void Board::SetShortestPath()
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

//Returns how many tiles are in their final position
int Board::CheckProgress(Vertex** checkBoard) {
	int closeness = 0;
	for (int i = 0; i < boardSize; i++) { //Checks that all numbers are in place (last number represents the empty space)
		if (checkBoard[i]->number == i + 1) closeness++;
	}
	return closeness;
}