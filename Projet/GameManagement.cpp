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

void GameManagement::changeturn()
{
	if (turn == 0) {
		turn = 1;
	}
	else {
		turn = 0;
	}
}

void GameManagement::gameloop()
{
	while (!isgamefinish()) {
		bool needinput = true;

		while (needinput) {
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

			needinput = !(b->move(xs, ys, xd, yd, turn));

			system("CLS");

			if (needinput) {
				cout << "Illegal command or move" << endl;
			}
		}
		changeturn();
	}

	system("CLS");

	b->display();

	if (b->inCheck(turn)) {
	//if (&b+turn) {
		if (turn == 0) {
			cout << "White win by checkmate" << endl << endl;
		}
		else {
			cout << "Black win by checkmate" << endl << endl;
		}
	}
	else {
		cout << "Draw by stalemate" << endl << endl;
	}
}

bool GameManagement::isgamefinish()
{
	return (b->canplay(turn) == false);
}
