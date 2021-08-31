#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include <SFML/Graphics.hpp>
#include "piece.h"

using namespace std;

class Rook : public Piece {
    public:
        int row, col;
        char side;
        bool moved;
        Rook(char side, int row, int col) : side(side), row(row), col(col) {
            moved = false;
            movelist = {};
            x = col * UNIT;
            y = row * UNIT;
        }
        void move(int row, int col);
        void update_movelist(bool check_pin);
};

#endif // CHESS_ROOK_H