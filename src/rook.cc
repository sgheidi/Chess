#include <iostream>

#include "rook.h"
#include "white.h"
#include "black.h"

using namespace std;

void Rook::update_movelist(bool check_pin) {
    movelist.clear();
    if (side == 'W') {
        // U
        int row_ = row-1;
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
        int col_ = col+1;
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
        if (check_pin) {
            vector<vector<int>> check_sq = {};
            row_ = row;
            col_ = col;
            bool moved_ = moved;
            for (auto sq : movelist) {
                move(sq[0], sq[1]);
                for (Bishop& b : black::bishops) b.update_movelist(false);
                for (Queen& q : black::queens) q.update_movelist(false);
                for (Rook& r : black::rooks) r.update_movelist(false);
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
            moved = moved_;
        }
    } else {
        // U
        int row_ = row-1;
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
        int col_ = col+1;
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
        if (check_pin) {
            vector<vector<int>> check_sq = {};
            row_ = row;
            col_ = col;
            bool moved_ = moved;
            for (auto sq : movelist) {
                move(sq[0], sq[1]);
                for (Bishop& b : white::bishops) b.update_movelist(false);
                for (Queen& q : white::queens) q.update_movelist(false);
                for (Rook& r : white::rooks) r.update_movelist(false);
                if (black::in_check()) {
                    if (white::blocks[sq[0]][sq[1]] and black::checker.size() == 1) {
                        if (white::get_piece(sq[0], sq[1]) == black::checker[0]) {
                            continue;
                        }
                    }
                    check_sq.push_back(sq);
                }
            }
            move(row_, col_);
            diff(movelist, check_sq);
            moved = moved_;
        }
    }
}

void Rook::move(int row_, int col_) {
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
    moved = true;
}