#include <iostream>
 
#include "white.h"
#include "black.h"

using namespace std;

void Pawn::update_movelist(bool check_pin) {
    movelist.clear();
    attacks.clear();
    if (side == 'W') {
        // enpassant
        if (row == 3) {
            for (Pawn p : black::pawns) {
                if (p.is_enpassant and abs(p.col - col) == 1) {
                    movelist.push_back({row-1, p.col});
                }
            }
        }
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
            bool is_enpassant_ = is_enpassant;
            for (auto sq : movelist) {
                // enpassant
                if (sq[0] == 2 and abs(sq[1] - col_) == 1 and !black::blocks[sq[0]][sq[1]]) {
                    string piece = black::get_piece(sq[0]+1, sq[1]);
                    for (int i=0;i<black::pawns.size();i++) {
                        if (piece == "P" + str(i))
                            black::pawns.erase(black::pawns.begin() + i);
                    }
                    black::blocks[sq[0]+1][sq[1]] = 0;
                    move(sq[0], sq[1]);
                    for (Bishop& b : black::bishops) b.update_movelist(false);
                    for (Queen& q : black::queens) q.update_movelist(false);
                    for (Rook& r : black::rooks) r.update_movelist(false);
                    if (white::in_check()) {
                        check_sq.push_back(sq);
                    }
                    Pawn p = Pawn('B', sq[0]+1, sq[1]);
                    p.is_enpassant = true;
                    black::pawns.push_back(p);
                    black::blocks[sq[0]+1][sq[1]] = 1;
                    continue;
                }
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
            is_enpassant = is_enpassant_;
        }
    } else {
        // enpassant
        if (row == 4) {
            for (Pawn p : white::pawns) {
                if (p.is_enpassant and abs(p.col - col) == 1) {
                    movelist.push_back({row+1, p.col});
                }
            }
        }
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
            bool is_enpassant_ = is_enpassant;
            for (auto sq : movelist) {
                // enpassant
                if (sq[0] == 5 and abs(sq[1] - col_) == 1 and !white::blocks[sq[0]][sq[1]]) {
                    string piece = white::get_piece(sq[0]-1, sq[1]);
                    for (int i=0;i<white::pawns.size();i++) {
                        if (piece == "P" + str(i))
                            white::pawns.erase(white::pawns.begin() + i);
                    }
                    white::blocks[sq[0]-1][sq[1]] = 0;
                    move(sq[0], sq[1]);
                    for (Bishop& b : white::bishops) b.update_movelist(false);
                    for (Queen& q : white::queens) q.update_movelist(false);
                    for (Rook& r : white::rooks) r.update_movelist(false);
                    if (black::in_check()) {
                        check_sq.push_back(sq);
                    }
                    Pawn p = Pawn('W', sq[0]-1, sq[1]);
                    p.is_enpassant = true;
                    white::pawns.push_back(p);
                    white::blocks[sq[0]-1][sq[1]] = 1;
                    continue;
                }
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
            is_enpassant = is_enpassant_;
        }
    }
}

void Pawn::move(int row_, int col_) {
    if (side == 'W') {
        if (row == 6 and row_ == 4) {
            is_enpassant = true;
        }
        white::blocks[row][col] = 0;
        white::blocks[row_][col_] = 1;
    } else {
        if (row == 1 and row_ == 3) {
            is_enpassant = true;
        }
        black::blocks[row][col] = 0;
        black::blocks[row_][col_] = 1;
    }
    row = row_;
    col = col_;
    x = col * UNIT;
    y = row * UNIT;
}

void Pawn::draw() {
    string color = (side == 'W') ? "white" : "black";
    if (!texture.loadFromFile("../assets/sprites/" + color + "/pawn.png")) {
        throw runtime_error("Could not load sprite file.");
    }
    sprite.setTexture(texture);
    sprite.setScale(PIECES_SCALE, PIECES_SCALE);
    sprite.setPosition(x + PIECES_PADDING_X, y + PIECES_PADDING_Y);
    window.draw(sprite);
}