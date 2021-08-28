#include <iostream>

#include "bishop.h"
#include "white.h"
#include "black.h"

using namespace std;

void Bishop::update_movelist() {
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
    }
    else {
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
        // vector<vector<int>> check_sq = {};
        // row_ = row;
        // col_ = col;
        // for (auto sq : movelist) {
        //     move(sq[0], sq[1]);
        //     // for (Bishop& b : white::bishops) b.update_movelist();
        //     // for (Queen& q : white::queens) q.update_movelist();
        //     // for (Rook& r : white::rooks) r.update_movelist();
        //     if (black::in_check()) {
        //         if (white::blocks[sq[0]][sq[1]]) {
        //             if (white::get_piece(sq[0], sq[1]) == black::checker) {
        //                 continue;
        //             }
        //         }
        //         check_sq.push_back(sq);
        //     }
        // }
        // move(row_, col_);
        // diff(movelist, check_sq);
    }
}

void Bishop::move(int row_, int col_) {
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

void Bishop::draw() {
    if (!texture.loadFromFile("../assets/sprites/white/bishop.png")) {
        throw runtime_error("Could not load sprite file.");
    }
    sprite.setTexture(texture);
    sprite.setScale(PIECES_SCALE, PIECES_SCALE);
    sprite.setPosition(x + PIECES_PADDING_X, y + PIECES_PADDING_Y);
    window.draw(sprite);
}