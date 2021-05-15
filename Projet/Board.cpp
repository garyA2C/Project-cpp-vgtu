#include "Board.h"
#include "Piece.h"
#include <iostream>
using namespace std;

Board::Board()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            game[i][j] = nullptr;
        }
    }

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

void Board::display()
{
    cout << endl << endl;
    updatescore();
    cout << " Actual score for white : " << score << endl << endl;
    cout << "      0    1    2    3    4    5    6    7 " << endl;
    cout << "     ---- ---- ---- ---- ---- ---- ---- ----" << endl ;

    for (int i = 7; i >= 0; i--) {
        cout << " " << i << "  | ";
        for (int j = 0; j < 8; j++) {
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

void Board::updatescore() {
    score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game[i][j]) {
                if (game[i][j]->getColor() == 0) {
                    score = *game[i][j] - score;
                }
                else {
                    score = *game[i][j] + score;
                }
            }
        }
    }
}

bool Board::operator+(int color) {
    int k, l;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game[i][j]) {
                if (color == 0) {
                    if (game[i][j]->getpiece() == "bK") {
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
                    if (game[i][j]->getpiece() == "bK") {
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
                if (game[i][j]->getColor()!=color){
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

vector<int> Board::whiteKingCoord()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game[i][j]) {
                if (game[i][j]->getpiece() == "wK") {
                    return { i, j };
                }
            }
        }
    }
}

vector<int> Board::blackKingCoord()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game[i][j]) {
                if (game[i][j]->getpiece() == "bK") {
                    return { i, j };
                }
            }
        }
    }
}

bool Board::canplay(int color)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game[i][j]) {
                if (game[i][j]->getColor() == color) {
                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            if (game[i][j]->legalmove(i, j, k, l, color, game)) {
                                Piece* piece = game[k][l];
                                game[k][l] = game[i][j];
                                game[i][j] = nullptr;
                                bool check = inCheck(color);
                                //bool check = this+color;
                                game[i][j] = game[k][l];
                                game[k][l] = piece;

                                if (!check) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}


bool Board::move(int xs, int ys, int xd, int yd, int color)
{
    if ((xs >= 0) && (xs <= 7) && (ys >= 0) && (ys <= 7) && (xd >= 0) && (xd <= 7) && (yd >= 0) && (yd <= 7)) {
        if (game[xs][ys]) {
            if (game[xs][ys]->legalmove(xs, ys, xd, yd, color, game)) {
                Piece* piece = game[xd][yd];
                game[xd][yd] = game[xs][ys];
                game[xs][ys] = nullptr;
                bool check = inCheck(color);
                //bool check = this+color;

                if (!check) {
                    delete piece;
                    return true;
                }
                else {
                    game[xs][ys] = game[xd][yd];
                    game[xd][yd] = piece;
                }
            }
        }
    }

    return false;
}



