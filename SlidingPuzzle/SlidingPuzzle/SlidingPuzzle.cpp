#include "stdafx.h"
#include "SlidingPuzzle.h"

int main()
{
	ScramblePuzzle();
	DisplayPuzzle();
    return 0;
}

void ScramblePuzzle() {

}

void DisplayPuzzle() {

}

bool CheckSolved() {
	for (int i = 0; i < boardSize; i++) { //Checks that all numbers are in place (last number represents the empty space)
		if (*(board + i) != i + 1) return false;
	}
}