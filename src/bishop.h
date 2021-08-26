#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include <SFML/Graphics.hpp>
#include "piece.h"

using namespace std;

class Bishop : public Piece {
    public:
        int row, col;
        char side;
        Bishop(char side, int row, int col) : side(side), row(row), col(col) {
            movelist = {};
            x = col * UNIT;
            y = row * UNIT;
        }
        void move(int row, int col);
        void update_movelist();
        void draw();
};

#endif // CHESS_BISHOP_H