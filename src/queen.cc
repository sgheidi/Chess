#include <iostream>

#include "queen.h"
#include "white.h"
#include "black.h"

using namespace std;

void Queen::update_movelist() {
    movelist.clear();
    if (side == 'W') {
        // UL
        int row_ = row-1;
        int col_ = col-1;
        while (row_ >= 0 and col >= 0) {
            if (white::blocks[row_][col_]) {
                break;
            }
            movelist.push_back({row_, col_});
            if (black::blocks[row_][col_]) {
                break;
            }
            row_ --;
            col_ --;
        }
        // UR
        row_ = row-1;
        col_ = col+1;
        while (row_ >= 0 and col <= 7) {
            if (white::blocks[row_][col_]) {
                break;
            }
            movelist.push_back({row_, col_});
            if (black::blocks[row_][col_]) {
                break;
            }
            row_ --;
            col_ ++;
        }
         // LR
        row_ = row+1;
        col_ = col+1;
        while (row_ <= 7 and col <= 7) {
            if (white::blocks[row_][col_]) {
                break;
            }
            movelist.push_back({row_, col_});
            if (black::blocks[row_][col_]) {
                break;
            }
            row_ ++;
            col_ ++;
        }
        // LL
        row_ = row+1;
        col_ = col-1;
        while (row_ <= 7 and col >= 0) {
            if (white::blocks[row_][col_]) {
                break;
            }
            movelist.push_back({row_, col_});
            if (black::blocks[row_][col_]) {
                break;
            }
            row_ ++;
            col_ --;
        }
        // U
        row_ = row-1;
        while (row_ >= 0) {
            if (white::blocks[row_][col]) {
                break;
            }
            movelist.push_back({row_, col});
            if (black::blocks[row_][col]) {
                break;
            }
            row_ --;
        }
        // D
        row_ = row+1;
        while (row_ <= 7) {
            if (white::blocks[row_][col]) {
                break;
            }
            movelist.push_back({row_, col});
            if (black::blocks[row_][col]) {
                break;
            }
            row_ ++;
        }
        // R
        col_ = col+1;
        while (col_ <= 7) {
            if (white::blocks[row][col_]) {
                break;
            }
            movelist.push_back({row, col_});
            if (black::blocks[row][col_]) {
                break;
            }
            col_ ++;
        }
        // L
        col_ = col-1;
        while (row_ >= 0) {
            if (white::blocks[row][col_]) {
                break;
            }
            movelist.push_back({row, col_});
            if (black::blocks[row][col_]) {
                break;
            }
            col_ --;
        }
    }
}

void Queen::move(int row_, int col_) {
    white::blocks[row][col] = 0;
    white::blocks[row_][col_] = 1;
    row = row_;
    col = col_;
    x = col * UNIT;
    y = row * UNIT;
}