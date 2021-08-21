#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include <SFML/Graphics.hpp>
#include "piece.h"

using namespace std;

class Queen : public Piece {
    public:
        int row, col;
        char side;
        Queen(char side, int row, int col) : side(side), row(row), col(col) {
            movelist = {};
            x = col * UNIT;
            y = row * UNIT;
        }
        void move(int row, int col);
        void update_movelist();
};

#endif // CHESS_QUEEN_H