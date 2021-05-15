#pragma once
#include <string>

class Piece
{
    public:
        int getColor() const;
        int getValue() const;
        bool isKilled() const;

        virtual bool canmove(int xs, int ys, int xd, int yd, Piece* b[8][8]);
        bool legalmove(int xs, int ys, int xd, int yd, int color, Piece* b[8][8]);
        virtual std::string getpiece();
        int operator+(int nb);
        int operator-(int nb);

    protected:
        int color;
        int value;
        bool killed;
 };

class Bishop : public Piece
{
    public:
        Bishop(int newcolor);
        ~Bishop();
        virtual bool canmove(int xs, int ys, int xd, int yd, Piece* b[8][8]);
        virtual std::string getpiece();

    private:
};

class King : public Piece
{
    public:
        King(int newcolor);
        ~King();
        virtual bool canmove(int xs, int ys, int xd, int yd, Piece* b[8][8]);
        virtual std::string getpiece();

    private:
};

class Queen : public Piece
{
    public:
        Queen(int newcolor);
        ~Queen();
        virtual bool canmove(int xs, int ys, int xd, int yd, Piece* b[8][8]);
        virtual std::string getpiece();

    private:
};

class Rook : public Piece
{
    public:
        Rook(int newcolor);
        ~Rook();
        virtual bool canmove(int xs, int ys, int xd, int yd, Piece* b[8][8]);
        virtual std::string getpiece();

    private:    
};


class Pawn : public Piece
{
    public:
        Pawn(int newcolor);
        ~Pawn();
        virtual bool canmove(int xs, int ys, int xd, int yd, Piece* b[8][8]);
        virtual std::string getpiece();

    private:
};

class Knight : public Piece
{
    public:
        Knight(int newcolor);
        ~Knight();
        virtual bool canmove(int xs, int ys, int xd, int yd, Piece* b[8][8]);
        virtual std::string getpiece();

    private:
};

