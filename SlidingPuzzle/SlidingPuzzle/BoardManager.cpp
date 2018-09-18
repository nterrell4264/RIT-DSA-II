#include "stdafx.h"
#include "BoardManager.h"

#pragma region Constuctor/Destructor
BoardManager::BoardManager()
{
	puzzle = new Puzzle(1);
	path = new vector<Puzzle*>();
	seenPuzzles = new vector<Puzzle*>();
}

BoardManager::~BoardManager()
{
	delete puzzle;

	for (int i = 0; i < path->size(); i++) delete (*path)[i];
	delete path;
	delete[] finalPath;

	delete current;
	for (int i = 0; i < seenPuzzles->size(); i++) delete (*seenPuzzles)[i];
	delete seenPuzzles;
}
#pragma endregion

#pragma region Puzzle Interfacing
void BoardManager::SetPuzzle(int dimension) {
	delete puzzle;
	puzzle = new Puzzle(dimension);
}
void BoardManager::ScramblePuzzle() {
	vector<Puzzle*> moves;
	int nextMove;
	//Loop that makes a random amount of random moves
	for (int i = 0; i < 128; i++) {
		moves = *AdjacencyDistances(puzzle);
		nextMove = rand() % moves.size();
		puzzle = moves[nextMove];
	}
}
void BoardManager::DisplayPuzzle() {
	puzzle->Display();
}

//Algorithm stuff
void BoardManager::SolveAStar() {
	path->clear();
	AStarPath(puzzle);
	for (int i = 0; i < finalPathLength; i++) {
		int move = finalPath[i];
		cout << "Move tile " << puzzle->board[finalPath[i]]->number;
		MakeMove(move);
		DisplayPuzzle();
	}
}
void BoardManager::SolveHill() {
	path->clear();
	seenPuzzles->clear();
	if (HillPath()) {
		for (int i = 0; i < finalPathLength; i++) {
			int move = finalPath[i];
			cout << "Move tile " << puzzle->board[finalPath[i]]->number << endl;
			MakeMove(move);
			DisplayPuzzle();
		}
	}
	else cout << "Unable to find path with hill-climbing." << endl;
}

void BoardManager::SetShortestPath()
{
	if (finalPath != nullptr) //Deletes previous shortest path if it exists
	{
		delete[] finalPath;
	}
	//Creates and populates array with coordinates of path's vertices
	finalPathLength = path->size() - 1;
	finalPath = new int[finalPathLength];
	for (int i = 0; i < finalPathLength; i++) {
		Puzzle stepBoard = *(*path)[i + 1];
		finalPath[i] = stepBoard.emptyIndex;
	}
}
#pragma endregion

#pragma region Solution finding
int BoardManager::AStarPath(Puzzle* move)
{
	move->Display();
	Vertex* vertex = move->GetEmpty();
	if ((*vertex).visited > path->size() - 3) { //Spot has been empty in the last three moves (only possible if it was just moved into or a square is about to be made)
		return INT_MAX;
	}
	//Add vertex to path
	path->push_back(move);
	//cout << CheckProgress(path->back()) << endl;
	if (CheckProgress(path->back()) == 0) { //Reached end
		SetShortestPath();
		(*path).pop_back();
		return path->size();
	}
	(*vertex).visited = path->size();
	//Recursively finds next step, in order of distance from the endpoint
	int curPath = INT_MAX;
	int shortPath = INT_MAX;
	vector<Puzzle*>* neighbors = AdjacencyDistances(move);
	for (Puzzle* neighbor : *neighbors) {
		curPath = AStarPath(neighbor);
		if (curPath < shortPath) shortPath = curPath;
		else delete neighbor;
	}
	//Clean-up
	delete neighbors;
	(*path).pop_back();
	return shortPath;
}
bool BoardManager::HillPath() {
	path->push_back(puzzle);
	while (path->size() > 0) {
		current = path->back();
		//current->Display();
		//cout << CheckProgress(current) << endl;
		if (CheckProgress(current) == 0) { //Reached end
			SetShortestPath();
			return true;
		}
		seenPuzzles->push_back(current);
		bool hasNew = false;
		vector<Puzzle*>* neighbors = AdjacencyDistances(current);
		for (int i = neighbors->size() - 1; i >= 0; i--) {
			Puzzle* neighbor = (*neighbors)[i];
			if (NotRepeat(neighbor)) {
				path->push_back(neighbor);
				hasNew = true;
			}
		}
		delete neighbors;
		if (!hasNew) path->pop_back();
	}
	return false;
}

//Calculates the closeness of each move into the empty position and returns it
vector<Puzzle*>* BoardManager::AdjacencyDistances(Puzzle* move) {
	vector<Puzzle*>* neighbors = new vector<Puzzle*>(0);
	int index = move->emptyIndex;
	//Finds valid neighbors
	if (index % puzzle->sideLength < puzzle->sideLength - 1) { //Right
		neighbors->push_back(SimulateMove(move, index + 1));
	}
	if (index / puzzle->sideLength > 0) { //Up
		neighbors->push_back(SimulateMove(move, index - puzzle->sideLength));
	}
	if (index % puzzle->sideLength > 0) { //Left
		neighbors->push_back(SimulateMove(move, index - 1));
	}
	if (index / puzzle->sideLength != puzzle->sideLength - 1) { //Down
		neighbors->push_back(SimulateMove(move, index + puzzle->sideLength));
	}
	sort(neighbors->begin(), neighbors->end(), sortMove); //Sorts list in ascending order by heuristics value
	return neighbors;
}

void BoardManager::MakeMove(int moveIndex) { //Wrapper function lel
	puzzle = SimulateMove(puzzle, moveIndex);
}
Puzzle* BoardManager::SimulateMove(Puzzle* moveBoard, int moveIndex) {
	Puzzle* newPuzzle = new Puzzle(*moveBoard);
	newPuzzle->GetEmpty()->number = newPuzzle->board[moveIndex]->number;
	newPuzzle->board[moveIndex]->number = newPuzzle->boardSize;
	newPuzzle->emptyIndex = moveIndex;
	return newPuzzle;
}

bool sortMove(Puzzle* const a, Puzzle* const b) {
	return CheckProgress(a) < CheckProgress(b);
}

//Returns the collective distance from the current tile state to the final one
int CheckProgress(Puzzle* checkBoard) {
	int closeness = 0;
	for (int i = 0; i < checkBoard->boardSize; i++) { //Checks that all numbers are in place (last number represents the empty space)
		closeness += abs(checkBoard->board[i]->number - i - 1) / checkBoard->sideLength + abs(checkBoard->board[i]->number - i - 1) % checkBoard->sideLength;
	}
	return closeness;
}
bool BoardManager::NotRepeat(Puzzle* checkBoard) {
	for (int i = 0; i < seenPuzzles->size(); i++) {
		Puzzle* config = (*seenPuzzles)[i];
		for (int j = 0; j < checkBoard->boardSize; j++) {
			if (checkBoard->board[j]->number != config->board[j]->number) break;
			if (j == checkBoard->boardSize - 1) return false; //Hit all values without finding a difference
		}
	}
	return true;
}
#pragma endregion