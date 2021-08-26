#include <iostream>

#include "knight.h"
#include "white.h"
#include "black.h"

using namespace std;

void Knight::update_movelist() {
    movelist.clear();
    vector<vector<int>> squares = {
        {row+1, col-2}, {row+1, col+2}, {row+2, col-1}, {row+2, col+1},
        {row-1, col-2}, {row-1, col+2}, {row-2, col-1}, {row-2, col+1}
    };
    if (side == 'W') {
        for (vector<int> s : squares) {
            if (!white::blocks[s[0]][s[1]] and s[0] >= 0 and s[0] < 8 and s[1] >= 0 and s[1] < 8) {
                movelist.push_back({s[0], s[1]});
            }
        }
    } else {
        for (vector<int> s : squares) {
            if (!black::blocks[s[0]][s[1]] and s[0] >= 0 and s[0] < 8 and s[1] >= 0 and s[1] < 8) {
                movelist.push_back({s[0], s[1]});
            }
        }
    }
}

void Knight::move(int row_, int col_) {
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