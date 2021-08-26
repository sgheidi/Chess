#include <iostream>
 
#include "white.h"
#include "black.h"

using namespace std;

void Pawn::update_movelist() {
    movelist.clear();
    attacks.clear();
    if (side == 'W') {
        // double step
        if (row == 6 and !black::blocks[row-2][col] and !white::blocks[row-2][col] and !black::blocks[row-1][col] and
        !white::blocks[row-1][col]) 
            movelist.push_back({row-2, col});
        // single step
        if (!black::blocks[row-1][col] and !white::blocks[row-1][col] and row-1 >= 0)
            movelist.push_back({row-1, col});
        // side captures
        if (black::blocks[row-1][col+1] and row-1 >= 0 and col+1 < 8)
            movelist.push_back({row-1, col+1});
        if (black::blocks[row-1][col-1] and row-1 >= 0 and col-1 < 8)
            movelist.push_back({row-1, col-1});
    } else {
        // double step
        if (row == 1 and !black::blocks[row+2][col] and !white::blocks[row+2][col] and !black::blocks[row+1][col] and
        !white::blocks[row+1][col]) 
            movelist.push_back({row+2, col});
        // single step
        if (!black::blocks[row+1][col] and !white::blocks[row+1][col] and row+1 < 8)
            movelist.push_back({row+1, col});
        // side captures
        if (white::blocks[row+1][col+1] and row+1 < 8 and col+1 < 8)
            movelist.push_back({row+1, col+1});
        if (white::blocks[row+1][col-1] and row+1 < 8 and col-1 < 8)
            movelist.push_back({row+1, col-1});        
    }
}

void Pawn::move(int row_, int col_) {
    if (side == 'W') {
        white::blocks[row][col] = 0;
        white::blocks[row_][col_] = 1;
    } else {
        black::blocks[row][col] = 0;
        black::blocks[row_][col_] = 1;
    }
    row = row_;
    col = col_;
    x = col * UNIT;
    y = row * UNIT;
}