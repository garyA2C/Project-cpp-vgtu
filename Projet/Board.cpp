#include "Board.h"
#include "Piece.h"
#include <iostream>
using namespace std;

Board::Board()
{
    //we initialise the board with null pointer
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            game[i][j] = nullptr;
        }
    }

    //we create classic chess board 
    for (int i = 0; i < 8; i++) {
        game[1][i] = new Pawn(1);
    }

    for (int i = 0; i < 8; i++) {
        game[6][i] = new Pawn(0);
    }

    game[0][0] = new Rook(1);
    game[0][1] = new Knight(1);
    game[0][2] = new Bishop(1);
    game[0][3] = new Queen(1);
    game[0][4] = new King(1);
    game[0][5] = new Bishop(1);
    game[0][6] = new Knight(1);
    game[0][7] = new Rook(1);

    game[7][0] = new Rook(0);
    game[7][1] = new Knight(0);
    game[7][2] = new Bishop(0);
    game[7][3] = new Queen(0);
    game[7][4] = new King(0);
    game[7][5] = new Bishop(0);
    game[7][6] = new Knight(0);
    game[7][7] = new Rook(0);

    score = 0;

    cout << "Board setup" << endl;

}

Board::~Board()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete game[i][j];
        }
    }
}

void Board::display() //for displaying the board
{
    cout << endl << endl;
    updatescore(); //we update the score
    cout << " Actual score for white : " << score << endl << endl;
    cout << "      0    1    2    3    4    5    6    7 " << endl;
    cout << "     ---- ---- ---- ---- ---- ---- ---- ----" << endl ;

    for (int i = 7; i >= 0; i--) {
        cout << " " << i << "  | ";
        for (int j = 0; j < 8; j++) {       //display each piece, line per line
            if (game[i][j]) {
                cout << game[i][j]->getpiece() << " | ";
            }
            else {
                cout << "   | ";
            }
        }
        cout << " " << i << endl;
        cout << "     ---- ---- ---- ---- ---- ---- ---- ----" << endl;
    }

    cout << "      0    1    2    3    4    5    6    7 " << endl << endl; 

}

void Board::updatescore() { //for calculating the difference of score between white and black
    score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game[i][j]) {
                if (game[i][j]->getColor() == 0) {
                    score = *game[i][j] - score;        //we substract if 
                }
                else {
                    score = *game[i][j] + score;
                }
            }
        }
    }
}

//overload of + for check as the classic notation in check use

bool Board::operator+(int color) {
    int k, l;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game[i][j]) {
                if (color == 0) {
                    if (game[i][j]->getpiece() == "bK") {       //we get the position of the king of the asked color
                        k = i;
                        l = j;
                    }
                }
                else {
                    if (game[i][j]->getpiece() == "wK") {
                        k = i;
                        l = j;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {       //we check if any piece have a legal move which can eat the king
            if (game[i][j]) {
                if (game[i][j]->getColor() != color) {
                    if (color == 0) {
                        if (game[i][j]->legalmove(i, j, k, l, 1, game)) {
                            return true;
                        }
                    }
                    else {
                        if (game[i][j]->legalmove(i, j, k, l, 0, game)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Board::inCheck(int color) {
    int k, l;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game[i][j]) {
                if (color == 0) {
                    if (game[i][j]->getpiece() == "bK") {  //we get the position of the king of the asked color
                        k = i;
                        l = j;
                    }
                }
                else {
                    if (game[i][j]->getpiece() == "wK") {
                        k = i;
                        l = j;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game[i][j]) {
                if (game[i][j]->getColor()!=color){ //we check if any piece have a legal move which can eat the king
                    if (color == 0) {
                        if (game[i][j]->legalmove(i, j, k, l, 1, game)) {
                            return true;
                        }
                    }
                    else {
                        if (game[i][j]->legalmove(i, j, k, l, 0, game)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

//this method check if the player has still a legal move to do
bool Board::canplay(int color)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {       //we check every square
            if (game[i][j]) {
                if (game[i][j]->getColor() == color) {      //if the square is empty or an other color
                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            if (game[i][j]->legalmove(i, j, k, l, color, game)) {       //if a move is possible
                                Piece* piece = game[k][l];      
                                game[k][l] = game[i][j];
                                game[i][j] = nullptr;       //we do it
                                bool check = inCheck(color);        //we check if the new position let us in check
                                //bool check = this+color;
                                game[i][j] = game[k][l];        //we undo it
                                game[k][l] = piece;

                                if (!check) {
                                    return true;        //if the position is possible we directly return true
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false; //if no legal move found
}

//for making a move on the board
bool Board::move(int xs, int ys, int xd, int yd, int color)
{
    if ((xs >= 0) && (xs <= 7) && (ys >= 0) && (ys <= 7) && (xd >= 0) && (xd <= 7) && (yd >= 0) && (yd <= 7)) { //we check that the input are in range 
        if (game[xs][ys]) {
            if (game[xs][ys]->legalmove(xs, ys, xd, yd, color, game)) { //we check if the move is legal
                Piece* piece = game[xd][yd];
                game[xd][yd] = game[xs][ys];        //we do it
                game[xs][ys] = nullptr;
                bool check = inCheck(color);
                //bool check = this+color;

                if (!check) {       //if the position don't let us in check, we delete the eaten piece for memory 
                    delete piece;
                    return true;
                }
                else {
                    game[xs][ys] = game[xd][yd];        //if not we undo it and we return that we did'nt do it
                    game[xd][yd] = piece;
                }
            }
        }
    }
    return false;
}



