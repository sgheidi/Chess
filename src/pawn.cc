#include <iostream>
 
#include "white.h"
#include "black.h"

using namespace std;

void Pawn::update_movelist(bool check_pin) {
    movelist.clear();
    attacks.clear();
    is_enpassant = false;
    if (side == 'W') {
        // double step
        if (row == 6 and !black::blocks[row-2][col] and !white::blocks[row-2][col] and !black::blocks[row-1][col] and
        !white::blocks[row-1][col]) {
            movelist.push_back({row-2, col});
            is_enpassant = true;        
        }
        // single step
        if (!black::blocks[row-1][col] and !white::blocks[row-1][col] and row-1 >= 0)
            movelist.push_back({row-1, col});
        // side captures
        if (black::blocks[row-1][col+1] and row-1 >= 0 and col+1 < 8)
            movelist.push_back({row-1, col+1});
        if (black::blocks[row-1][col-1] and row-1 >= 0 and col-1 >= 0)
            movelist.push_back({row-1, col-1});
        // attacks
        if (row-1 >= 0 and col-1 >= 0)
            attacks.push_back({row-1, col-1});
        if (row-1 >= 0 and col+1 < 8)
            attacks.push_back({row-1, col+1});

        if (check_pin) {
            vector<vector<int>> check_sq = {};
            int row_ = row;
            int col_ = col;
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
        }
    } else {
        // double step
        if (row == 1 and !black::blocks[row+2][col] and !white::blocks[row+2][col] and !black::blocks[row+1][col] and
        !white::blocks[row+1][col])  {
            movelist.push_back({row+2, col});
            is_enpassant = true;
        }
        // single step
        if (!black::blocks[row+1][col] and !white::blocks[row+1][col] and row+1 < 8)
            movelist.push_back({row+1, col});
        // side captures
        if (white::blocks[row+1][col+1] and row+1 < 8 and col+1 < 8)
            movelist.push_back({row+1, col+1});
        if (white::blocks[row+1][col-1] and row+1 < 8 and col-1 >= 0)
            movelist.push_back({row+1, col-1});    
        // attacks
        if (row+1 < 8 and col-1 >= 0)
            attacks.push_back({row+1, col-1});
        if (row+1 < 8 and col+1 < 8)
            attacks.push_back({row+1, col+1});
        if (check_pin) {
            vector<vector<int>> check_sq = {};
            int row_ = row;
            int col_ = col;
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
        }
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