#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include <SFML/Graphics.hpp>
#include "piece.h"

using namespace std;

class Pawn : public Piece {
    public:
        int row, col;
        char side;
        Pawn(char side, int row, int col) : side(side), row(row), col(col) {
            movelist = {};
            x = col * UNIT;
            y = row * UNIT;
        }
        void move(int row, int col);
        void update_movelist();
};

#endif // CHESS_PAWN_H