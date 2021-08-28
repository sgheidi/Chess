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
        while (row_ >= 0 and col_ >= 0) {
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
        while (row_ >= 0 and col_ <= 7) {
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
        while (row_ <= 7 and col_ <= 7) {
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
        while (row_ <= 7 and col_ >= 0) {
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
        while (col_ >= 0) {
            if (white::blocks[row][col_]) {
                break;
            }
            movelist.push_back({row, col_});
            if (black::blocks[row][col_]) {
                break;
            }
            col_ --;
        }
        vector<vector<int>> check_sq = {};
        row_ = row;
        col_ = col;
        for (auto sq : movelist) {
            move(sq[0], sq[1]);
            for (Bishop& b : black::bishops) b.update_movelist();
            for (Queen& q : black::queens) q.update_movelist();
            for (Rook& r : black::rooks) r.update_movelist();
            if (white::in_check()) {
                if (black::blocks[sq[0]][sq[1]] and white::checker.size() == 1) {
                    if (black::get_piece(sq[0], sq[1]) == white::checker[0]) {
                        continue;
                    }
                }
                check_sq.push_back(sq);
            }
        }
        move(row_, col_);
        diff(movelist, check_sq);
    } else {
        // UL
        int row_ = row-1;
        int col_ = col-1;
        while (row_ >= 0 and col_ >= 0) {
            if (black::blocks[row_][col_]) {
                break;
            }
            movelist.push_back({row_, col_});
            if (white::blocks[row_][col_]) {
                break;
            }
            row_ --;
            col_ --;
        }
        // UR
        row_ = row-1;
        col_ = col+1;
        while (row_ >= 0 and col_ <= 7) {
            if (black::blocks[row_][col_]) {
                break;
            }
            movelist.push_back({row_, col_});
            if (white::blocks[row_][col_]) {
                break;
            }
            row_ --;
            col_ ++;
        }
         // LR
        row_ = row+1;
        col_ = col+1;
        while (row_ <= 7 and col_ <= 7) {
            if (black::blocks[row_][col_]) {
                break;
            }
            movelist.push_back({row_, col_});
            if (white::blocks[row_][col_]) {
                break;
            }
            row_ ++;
            col_ ++;
        }
        // LL
        row_ = row+1;
        col_ = col-1;
        while (row_ <= 7 and col_ >= 0) {
            if (black::blocks[row_][col_]) {
                break;
            }
            movelist.push_back({row_, col_});
            if (white::blocks[row_][col_]) {
                break;
            }
            row_ ++;
            col_ --;
        }
        // U
        row_ = row-1;
        while (row_ >= 0) {
            if (black::blocks[row_][col]) {
                break;
            }
            movelist.push_back({row_, col});
            if (white::blocks[row_][col]) {
                break;
            }
            row_ --;
        }
        // D
        row_ = row+1;
        while (row_ <= 7) {
            if (black::blocks[row_][col]) {
                break;
            }
            movelist.push_back({row_, col});
            if (white::blocks[row_][col]) {
                break;
            }
            row_ ++;
        }
        // R
        col_ = col+1;
        while (col_ <= 7) {
            if (black::blocks[row][col_]) {
                break;
            }
            movelist.push_back({row, col_});
            if (white::blocks[row][col_]) {
                break;
            }
            col_ ++;
        }
        // L
        col_ = col-1;
        while (col_ >= 0) {
            if (black::blocks[row][col_]) {
                break;
            }
            movelist.push_back({row, col_});
            if (white::blocks[row][col_]) {
                break;
            }
            col_ --;
        }
    }
}

void Queen::move(int row_, int col_) {
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