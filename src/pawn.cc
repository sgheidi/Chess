#include <iostream>

#include "pawn.h"
#include "white.h"
#include "black.h"

using namespace std;

void Pawn::update_movelist() {
    movelist.clear();
    if (side == 'W') {
        // double step
        if (row == 6 and !black::blocks[row-2][col] and !white::blocks[row-2][col]) 
            movelist.push_back({row-2, col});
        // single step
        if (!black::blocks[row-1][col] and !white::blocks[row-1][col])
            movelist.push_back({row-1, col});
        // side captures
        if (black::blocks[row-1][col+1])
            movelist.push_back({row-1, col+1});
        if (black::blocks[row-1][col-1])
            movelist.push_back({row-1, col-1});
    }
}

void Pawn::move(int row_, int col_) {
    white::blocks[row][col] = 0;
    white::blocks[row_][col_] = 1;
    row = row_;
    col = col_;
    x = col * UNIT;
    y = row * UNIT;
}