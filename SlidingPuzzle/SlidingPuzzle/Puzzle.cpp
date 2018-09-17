#include "stdafx.h"
#include "Puzzle.h"

Puzzle::Puzzle(int dimension = 1)
{
	sideLength = dimension;
	boardSize = sideLength * sideLength;
	if (board == nullptr) {
		board = new Vertex*[boardSize];
		for (int i = 0; i < boardSize; i += sideLength) {
			for (int j = 0; j < sideLength; j++) {
				board[i + j] = new Vertex(i + j, i + j + 1);
			}
		}
	}
	emptyIndex = boardSize - 1;
}


Puzzle::~Puzzle()
{
	delete[] board;
}

Vertex* Puzzle::GetEmpty() {
	return board[emptyIndex];
}