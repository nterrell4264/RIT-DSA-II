#include "stdafx.h"
#include "Board.h"

Board* board;

int main()
{
	board = new Board(4);
	board->ScramblePuzzle();
	board->DisplayPuzzle();
    return 0;
}