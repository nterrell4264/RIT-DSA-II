#include "stdafx.h"
#include "BoardManager.h"

BoardManager* boards;

int main()
{
	boards = new BoardManager();
	boards->ScramblePuzzle();
	boards->DisplayPuzzle();
    return 0;
}