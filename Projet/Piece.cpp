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

bool Piece::canmove(int xs, int ys, int xd, int yd, Piece* b[8][8])
{
    cout << "Error";
    return false;
}

bool Piece::legalmove(int xs, int ys, int xd, int yd, int color, Piece* b[8][8])
{
    if (b[xs][ys]) {
        if (b[xs][ys]->getColor()==color) {
            if ((xs != xd) || (ys != yd)) {
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

int Piece::operator+(int nb)
{
    return getValue()+nb;
}

int Piece::operator-(int nb)
{
    return nb-getValue();
}

Pawn::Pawn(int newcolor)
{
    value = 1;
    color = newcolor;
}

Pawn::~Pawn()
{
}

bool Pawn::canmove(int xs, int ys, int xd, int yd, Piece* b[8][8])
{
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

    else {
        if (ys == yd) {
            if (getColor() == 0) {
                if (xd == xs - 1) {
                    return true;
                }
                else {
                    if ((xs == 6) && (b[5][yd] == nullptr)) {
                        return true;
                    }
                }
            }
            else {
                if (xd == xs + 1) {
                    return true;
                }
                else {
                    if ((xs == 1) && (b[2][yd] == nullptr)) {
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
    if (((b[xd][yd]) && (b[xd][yd]->getColor() != getColor())) || (b[xd][yd] == nullptr)) {
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
    if (((b[xd][yd]) && (b[xd][yd]->getColor() != getColor())) || (b[xd][yd] == nullptr)) {
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
    if (((b[xd][yd]) && (b[xd][yd]->getColor() != getColor())) || (b[xd][yd] == nullptr)) {
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
    if (((b[xd][yd]) && (b[xd][yd]->getColor() != getColor())) || (b[xd][yd] == nullptr)) {
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
