#include <iostream>

#include "knight.h"
#include "white.h"
#include "black.h"

using namespace std;

void Knight::update_movelist() {
    movelist.clear();
    if (side == 'W') {
        vector<vector<int>> squares = {
            {row+1, col-2}, {row+1, col+2}, {row+2, col-1}, {row+2, col+1},
            {row-1, col-2}, {row-1, col+2}, {row-2, col-1}, {row-2, col+1}
        };
        for (vector<int> s : squares) {
            if (!white::blocks[s[0]][s[1]] and s[0] >= 0 and s[0] < 8 and s[1] >= 0 and s[1] < 8) {
                movelist.push_back({s[0], s[1]});
            }
        }
    }
}

void Knight::move(int row_, int col_) {
    white::blocks[row][col] = 0;
    white::blocks[row_][col_] = 1;
    row = row_;
    col = col_;
    x = col * UNIT;
    y = row * UNIT;   
}