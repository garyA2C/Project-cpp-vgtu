#include "Piece.h"
#include <climits>
#include <iostream>
#include "Board.h"
#include <cmath>
using namespace std;


int Piece::getColor() const
{
    return color;
}

int Piece::getValue() const
{
    return value;
}

bool Piece::isKilled() const
{
    return killed;
}

bool Piece::canmove(int xs, int ys, int xd, int yd, Piece* b[8][8]) //for polimorphism checking
{
    cout << "Error";
    return false;   
}

bool Piece::legalmove(int xs, int ys, int xd, int yd, int color, Piece* b[8][8]) //check if a piece can move here
{
    if (b[xs][ys]) { //if there is a piece on the square
        if (b[xs][ys]->getColor()==color) {
            if ((xs != xd) || (ys != yd)) { //if the source and the destination are different
                return b[xs][ys]->canmove(xs, ys, xd, yd, b);
            }
        }        
    }
    return false;
}

string Piece::getpiece()
{
    return "  ";
}

int Piece::operator+(int nb) //overload of + use for adding the score
{
    return getValue()+nb;
}

int Piece::operator-(int nb) //overload of - used for substracting the score
{
    return nb-getValue();
}

Pawn::Pawn(int newcolor)    //pawn derivate from piece
{
    value = 1;
    color = newcolor;
}

Pawn::~Pawn()
{
}

bool Pawn::canmove(int xs, int ys, int xd, int yd, Piece* b[8][8])
{
    //if the destination is an opponent piece, we can eat in diagonal
    if (b[xd][yd]) {
        if (b[xd][yd]->getColor() != getColor()){
            if ((ys == yd + 1) || (ys == yd - 1)) {
                if (getColor() == 0) {
                    return (xd == xs - 1);
                }
                else {
                    return (xd == xs + 1);
                }
            }
        }
    }

    //if not, we have to go 1 forward or 2 if we are in starting position
    else {
        if (ys == yd) {
            if (getColor() == 0) {
                if (xd == xs - 1) {
                    return true;
                }
                else {
                    if ((xs == 6) && (b[5][yd] == nullptr)) { //we check if there is no piece on the column 5 for going two step forward
                        return true;
                    }
                }
            }
            else {
                if (xd == xs + 1) {
                    return true;
                }
                else {
                    if ((xs == 1) && (b[2][yd] == nullptr)) { //we check if there is no piece on the column 2 for going two step forward
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

string Pawn::getpiece()
{
    if (color == 0) {
        return "bP";
    }
    else {
        return "wP";
    }
}

//knight derive from piece
Knight::Knight(int newcolor)
{
    value = 3;
    color = newcolor;
}

Knight::~Knight()
{
}

bool Knight::canmove(int xs, int ys, int xd, int yd, Piece* b[8][8])
{
    //a knight can move in a L shape

    if (((b[xd][yd]) && (b[xd][yd]->getColor() != getColor())) || (b[xd][yd] == nullptr)) {

        if ((xs == xd + 1) || (xs == xd - 1)) {
            return ((ys == yd + 2) || (ys == yd - 2));
        }
        else if ((xs == xd + 2) || (xs == xd - 2)) {
            return ((ys == yd + 1) || (ys == yd - 1));
        }
    }
    return false;

}

string Knight::getpiece()
{
    if (color == 0) {
        return "bN";
    }
    else {
        return "wN";
    }
}

//rook derive from a piece
Rook::Rook(int newcolor)
{
    value = 5;
    color = newcolor;
}

Rook::~Rook()
{
}

bool Rook::canmove(int xs, int ys, int xd, int yd, Piece* b[8][8])
{
    //a rook can only move on one line
    if (((b[xd][yd]) && (b[xd][yd]->getColor() != getColor())) || (b[xd][yd] == nullptr)) { //we check if the destination is empty or a piece of opposit color
        //if horizontal line
        if (xs == xd) {
            if (ys > yd) {
                //we check if all the square are empty between the two position
                for (int i = yd + 1; i < ys; i++) {
                    if (b[xs][i]) {
                        return false;
                    }
                }
            }
            else {
                for (int i = ys + 1; i < yd; i++) {
                    if (b[xs][i]) {                         //we check if all the square are empty between the two position
                        return false;
                    }
                }
            }
            return true;

        }
        //if vertical line
        else if (ys == yd) {
            if (xs > xd) {
                for (int i = xd + 1; i < xs; i++) {
                    if (b[i][ys]) {
                        return false;
                    }
                }
            }
            else {
                for (int i = xs + 1; i < xd; i++) {
                    if (b[i][ys]) {
                        return false;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

string Rook::getpiece()
{
    if (color == 0) {
        return "bR";
    }
    else {
        return "wR";
    }
}

//queen derive from Piece
Queen::Queen(int newcolor)
{
    value = 9;
    color = newcolor;
}

Queen::~Queen()
{
}

bool Queen::canmove(int xs, int ys, int xd, int yd, Piece* b[8][8])
{
    //a queen have the power of the rook and the bishop combined, we just copy the code of the two 

    if (((b[xd][yd]) && (b[xd][yd]->getColor() != getColor())) || (b[xd][yd] == nullptr)) { //we check if the destination is empty or a piece of opposit color
        if (abs(xs - xd) == abs(ys - yd)) {
            if (xs > xd) {
                if (ys > yd) {
                    for (int i = 1; i < abs(xs - xd); i++) {
                        if (b[xs - i][ys - i]) {
                            return false;
                        }
                    }
                    return true;
                }
                else {
                    for (int i = 1; i < abs(xs - xd); i++) {
                        if (b[xs - i][ys + i]) {
                            return false;
                        }
                    }
                    return true;
                }
            }
            else {
                if (ys > yd) {
                    for (int i = 1; i < abs(xs - xd); i++) {
                        if (b[xs + i][ys - i]) {
                            return false;
                        }
                    }
                    return true;
                }
                else {
                    for (int i = 1; i < abs(xs - xd); i++) {
                        if (b[xs - i][ys - i]) {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        else {
            if (xs == xd) {
                if (ys > yd) {
                    for (int i = yd + 1; i < ys; i++) {
                        if (b[xs][i]) {
                            return false;
                        }
                    }
                }
                else {
                    for (int i = ys + 1; i < yd; i++) {
                        if (b[xs][i]) {
                            return false;
                        }
                    }
                }
                return true;

            }
            else if (ys == yd) {
                if (xs > xd) {
                    for (int i = xd + 1; i < xs; i++) {
                        if (b[i][ys]) {
                            return false;
                        }
                    }
                }
                else {
                    for (int i = xs + 1; i < xd; i++) {
                        if (b[i][ys]) {
                            return false;
                        }
                    }
                }
                return true;
            }
        }
    }

    return false;
}

string Queen::getpiece()
{
    if (color == 0) {
        return "bQ";
    }
    else {
        return "wQ";
    }
}

//King derive from Piece
King::King(int newcolor)
{
    value = INT_MAX;
    color = newcolor;
}

King::~King()
{
}

bool King::canmove(int xs, int ys, int xd, int yd, Piece* b[8][8])
{
    //a king can move in all direction but only one step
    if (((b[xd][yd]) && (b[xd][yd]->getColor() != getColor())) || (b[xd][yd] == nullptr)) { //we check if the destination is empty or a piece of opposit color
        if ((abs(xs - xd) <= 1) && (abs(ys - xd) <= 1)) {
            return true;
        }
    }
    return false;
}

string King::getpiece()
{
    if (color == 0) {
        return "bK";
    }
    else {
        return "wK";
    }
}

//Bishop derive from Piece
Bishop::Bishop(int newcolor)
{
    value = 3;
    color = newcolor;
}

Bishop::~Bishop()
{
}

bool Bishop::canmove(int xs, int ys, int xd, int yd, Piece* b[8][8])
{
    //a bishop move in diagonal 

    if (((b[xd][yd]) && (b[xd][yd]->getColor() != getColor())) || (b[xd][yd] == nullptr)) { //we check if the destination is empty or a piece of opposit color
        if (abs(xs - xd) == abs(ys - yd)) {             //if it make a diagonal
            if (xs > xd) {
                if (ys > yd) {
                    for (int i = 1; i < abs(xs - xd); i++) {        
                        if (b[xs - i][ys - i]) {                //we check if there is piece on the way 
                            return false;
                        }
                    }
                    return true;
                }
                else {
                    for (int i = 1; i < abs(xs - xd); i++) {
                        if (b[xs - i][ys + i]) {        //we check if there is piece on the way
                            return false;
                        }
                    }
                    return true;
                }
            }
            else {
                if (ys > yd) {
                    for (int i = 1; i < abs(xs - xd); i++) {
                        if (b[xs + i][ys - i]) {        //we check if there is piece on the way
                            return false;
                        }
                    }
                    return true;
                }
                else {
                    for (int i = 1; i < abs(xs - xd); i++) {
                        if (b[xs - i][ys - i]) {        //we check if there is piece on the way
                            return false;   
                        }
                    }
                    return true;
                }
            }
        }
    }

    return false;
}

string Bishop::getpiece()
{
    if (color == 0) {
        return "bB";
    }
    else {
        return "wB";
    }
}
