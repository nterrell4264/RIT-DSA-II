#include "stdafx.h"
#include "BoardManager.h"

BoardManager* boards;

int main()
{
	boards = new BoardManager();
	boards->SetPuzzle(4);
	boards->ScramblePuzzle();
	boards->DisplayPuzzle();
	boards->SolveAStar();
    return 0;
}