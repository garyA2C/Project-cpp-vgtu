#pragma once
#include "Piece.h"
#include <vector>
#include <tuple>


class Board
{
	public :
		Board();
		~Board();
		void display();
		void updatescore();
		bool operator+(int color);
		bool inCheck(int color);
		std::vector<int> whiteKingCoord();
		std::vector<int> blackKingCoord();
		bool canplay(int color);

		bool move(int xs, int ys, int xd, int yd, int color);

	private : 
        Piece* game[8][8];
		int score;
};

