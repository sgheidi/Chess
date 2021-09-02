#ifndef CHESS_KING_H
#define CHESS_KING_H

#include <SFML/Graphics.hpp>
#include "piece.h"

using namespace std;

class King : public Piece {
    public:
        int row, col;
        char side;
        bool moved;
        King(char side, int row, int col) : side(side), row(row), col(col) {
            moved = false;
            movelist = {};
            x = col * UNIT;
            y = row * UNIT;
        }
        void move(int row, int col);
        void update_movelist();
        void draw();
};

#endif // CHESS_KING_H