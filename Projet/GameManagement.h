#pragma once
#include "Board.h"

class GameManagement
{
	public:
		GameManagement(Board* argb);
		~GameManagement();
		void changeturn();
		void gameloop();
		bool isgamefinish();
		
	private:
		Board* b;
		int turn;
};