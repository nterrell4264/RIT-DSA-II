#include "stdafx.h"
#include "Puzzle.h"

Puzzle::Puzzle(int dimension)
{
	sideLength = dimension;
	boardSize = sideLength * sideLength;
	board = new Vertex*[boardSize];
	for (int i = 0; i < boardSize; i += sideLength) {
		for (int j = 0; j < sideLength; j++) {
			board[i + j] = new Vertex(i + j + 1);
		}
	}
	emptyIndex = boardSize - 1;
}

Puzzle::~Puzzle()
{
	delete[] board;
}

//Copy assignment
Puzzle::Puzzle (const Puzzle& other)
{
	if (this != &other) {
		sideLength = other.sideLength;
		boardSize = sideLength * sideLength;
		emptyIndex = other.emptyIndex;
		board = new Vertex*[boardSize];
		for (int i = 0; i < boardSize; i += sideLength) {
			for (int j = 0; j < sideLength; j++) {
				board[i + j] = new Vertex(*other.board[i + j]);
				//*(board[i + j]) = *(other.board[i + j]);
			}
		}
	}
}
//Copy assignment
Puzzle& Puzzle::operator= (const Puzzle& other)
{
	if (this != &other) {
		sideLength = other.sideLength;
		boardSize = sideLength * sideLength;
		emptyIndex = other.emptyIndex;
		board = new Vertex*[boardSize];
		for (int i = 0; i < boardSize; i += sideLength) {
			for (int j = 0; j < sideLength; j++) {
				board[i + j] = new Vertex(*other.board[i + j]);
				//*(board[i + j]) = *(other.board[i + j]);
			}
		}
	}
	return *this;
}

void Puzzle::Display() {
	cout << "-------------" << endl;
	for (int i = 0; i < boardSize; i += sideLength) {
		for (int j = 0; j < sideLength; j++) {
			cout << "|";
			if (board[i + j]->number < 10) cout << " ";
			if (board[i + j]->number == boardSize) cout << "  ";
			else cout << board[i + j]->number;
		}
		cout << "|" << endl;
	}
	cout << "-------------" << endl;
}
Vertex* Puzzle::GetEmpty() {
	return board[emptyIndex];
}