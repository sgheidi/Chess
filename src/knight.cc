#include <iostream>

#include "knight.h"
#include "white.h"
#include "black.h"

using namespace std;

void Knight::update_movelist(bool check_pin) {
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
        for (vector<int> s : squares) {
            if (!black::blocks[s[0]][s[1]] and s[0] >= 0 and s[0] < 8 and s[1] >= 0 and s[1] < 8) {
                movelist.push_back({s[0], s[1]});
            }
        }
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

void Knight::draw() {
    string color = (side == 'W') ? "white" : "black";
    if (!texture.loadFromFile("../assets/sprites/" + color + "/knight.png")) {
        throw runtime_error("Could not load sprite file.");
    }
    sprite.setTexture(texture);
    sprite.setScale(PIECES_SCALE, PIECES_SCALE);
    sprite.setPosition(x + PIECES_PADDING_X, y + PIECES_PADDING_Y);
    window.draw(sprite);
}