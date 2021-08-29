#include <iostream>

#include "white.h"
#include "black.h"

using namespace std;

void King::update_movelist() {
    movelist.clear();
    vector<vector<int>> squares = {
        {row+1, col}, {row+1, col+1}, {row+1, col-1}, 
        {row, col+1}, {row, col-1},
        {row-1, col}, {row-1, col+1}, {row-1, col-1}, 
    };
    if (side == 'W') {
        for (vector<int> s : squares) {
            if (!white::blocks[s[0]][s[1]] and s[0] >= 0 and s[0] < 8 and s[1] >= 0 and s[1] < 8) {
                movelist.push_back({s[0], s[1]});
            }
        }
        vector<vector<int>> check_sq = {};
        int row_ = row;
        int col_ = col;
        for (auto sq : movelist) {
            bool capture = false;
            if (black::blocks[sq[0]][sq[1]]) { // capture
                black::blocks[sq[0]][sq[1]] = 0;
                capture = true;
            }
            move(sq[0], sq[1]);
            for (Bishop& b : black::bishops) b.update_movelist(false);
            for (Queen& q : black::queens) q.update_movelist(false);
            for (Rook& r : black::rooks) r.update_movelist(false);
            for (Knight& n : black::knights) n.update_movelist(false);
            if (white::in_check()) {
                check_sq.push_back(sq);
            }
            if (capture)
                black::blocks[sq[0]][sq[1]] = 1;
        }
        move(row_, col_);
        diff(movelist, check_sq);
        for (Bishop& b : black::bishops) b.update_movelist(false);
        for (Queen& q : black::queens) q.update_movelist(false);
        for (Rook& r : black::rooks) r.update_movelist(false);
        for (Knight& n : black::knights) n.update_movelist(false);
    } else {
        for (vector<int> s : squares) {
            if (!black::blocks[s[0]][s[1]] and s[0] >= 0 and s[0] < 8 and s[1] >= 0 and s[1] < 8) {
                movelist.push_back({s[0], s[1]});
            }
        }
        vector<vector<int>> check_sq = {};
        int row_ = row;
        int col_ = col;
        for (auto sq : movelist) {
            bool capture = false;
            if (white::blocks[sq[0]][sq[1]]) { // capture
                white::blocks[sq[0]][sq[1]] = 0;
                capture = true;
            }
            move(sq[0], sq[1]);
            for (Bishop& b : white::bishops) b.update_movelist(false);
            for (Queen& q : white::queens) q.update_movelist(false);
            for (Rook& r : white::rooks) r.update_movelist(false);
            for (Knight& n : white::knights) n.update_movelist(false);
            if (black::in_check()) {
                check_sq.push_back(sq);
            }
            if (capture)
                white::blocks[sq[0]][sq[1]] = 1;
        }
        move(row_, col_);
        diff(movelist, check_sq);
        for (Bishop& b : white::bishops) b.update_movelist(false);
        for (Queen& q : white::queens) q.update_movelist(false);
        for (Rook& r : white::rooks) r.update_movelist(false);
        for (Knight& n : white::knights) n.update_movelist(false);
    }
}

void King::move(int row_, int col_) {
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