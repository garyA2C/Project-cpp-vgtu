#include "GameManagement.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

GameManagement::GameManagement(Board* argb)
{
	b = argb;
	turn = 1;
}

GameManagement::~GameManagement()
{
	delete b;
}

//for alternate between white and black's turn
void GameManagement::changeturn()
{
	if (turn == 0) {
		turn = 1;
	}
	else {
		turn = 0;
	}
}

//main loop for the game
void GameManagement::gameloop()
{

	while (!isgamefinish()) {
		bool needinput = true;

		while (needinput) { //loop for every turn of the player (until the command entered is correct)
			int xs, ys, xd, yd;

			if (turn == 0) {
				cout << "Black";
			}
			else {
				cout << "White";
			}
			cout << " to play" << endl << endl;
			b->display();

			cout << "Format : SourceLine SourceColumn DestinationLine DestinationColumn" << endl;
			cout << "Enter move : ";
			cin >> xs;
			cin >> ys;
			cin >> xd;
			cin >> yd;

			needinput = !(b->move(xs, ys, xd, yd, turn));	//we try to perform the move

			system("CLS");

			if (needinput) {	//if the move is correct, the loop will let the other player play, if not, we display that it didn't work and reloop
				cout << "Illegal command or move" << endl;
			}
		}
		changeturn();
	}

	system("CLS");

	b->display();

	if (b->inCheck(turn)) {		//if the player cannot play and is in check, it's checkmate
	//if (&b+turn) {
		if (turn == 0) {
			cout << "White win by checkmate" << endl << endl;
		}
		else {
			cout << "Black win by checkmate" << endl << endl;
		}
	}
	else {
		cout << "Draw by stalemate" << endl << endl;		//else it's stalemate
	}
}

bool GameManagement::isgamefinish()
{
	return (b->canplay(turn) == false); //the game is finish if one of the player cannot play anymore
}
