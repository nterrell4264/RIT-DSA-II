#include "stdafx.h"
#include <stdlib.h>
#include <string>

#include "BoardManager.h"

BoardManager* boards;
string input = "";
//int charput = NULL;

int main()
{
	boards = new BoardManager();
	boards->SetPuzzle(3);
	cout << "Welcome to the sliding puzzle solver. Type a command or type \"help\" for help." << endl;
	while (input != "quit") {
		getline(cin, input);
		if (input == "help") {
			cout << "The following commands are possible:" << endl;
			//cout << "size: Resizes the puzzle." << endl;
			cout << "scramble: Scrambles the puzzle." << endl;
			cout << "hill: Solves the puzzle with the hill-climbing algorithm." << endl;
			cout << "astar: Solves the puzzle with the A* algorithm." << endl;
			cout << "print: Prints puzzle." << endl;
			cout << "quit: Quits the program." << endl;
		}
		/*if (input == "size") {
			cout << "Input the dimension of the square: ";
			cin >> charput;
			if (isdigit(charput)) boards->SetPuzzle(charput);
		}*/
		if (input == "scramble") {
			boards->ScramblePuzzle();
			cout << "Scrambled puzzle:" << endl;
			boards->DisplayPuzzle();
		}
		if (input == "hill") {
			boards->SolveHill();
			boards->DisplayPuzzle();
		}
		if (input == "astar") {
			boards->SolveAStar();
			boards->DisplayPuzzle();
		}
		if (input == "print") {
			boards->DisplayPuzzle();
		}
	}
	delete boards;
    return 0;
}