#include <iostream>
#include <vector>

#include "black.h"
#include "white.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"
#include "config.h"
#include "error.h"

using namespace std;

namespace black {
    string checker = "";
    vector<Bishop> bishops = {};
    vector<Knight> knights = {};
    vector<Rook> rooks = {};
    vector<Pawn> pawns = {};
    vector<Queen> queens = {};
    vector<King> kings = {};
    int blocks[8][8] = {};

    bool in_check() {
        vector<int> king_sq = {kings[0].row, kings[0].col};
        for (int i=0;i<white::bishops.size();i++) {
            if (find(white::bishops[i].movelist.begin(), white::bishops[i].movelist.end(), king_sq) 
            != white::bishops[i].movelist.end()) {
                checker = "B" + str(i);
                return true;
            }
        }
        for (int i=0;i<white::knights.size();i++) {
            if (find(white::knights[i].movelist.begin(), white::knights[i].movelist.end(), king_sq) 
            != white::knights[i].movelist.end()) {
                checker = "N" + str(i);
                return true;
            }
        }
        for (int i=0;i<white::rooks.size();i++) {
            if (find(white::rooks[i].movelist.begin(), white::rooks[i].movelist.end(), king_sq) 
            != white::rooks[i].movelist.end()) {
                checker = "R" + str(i);
                return true;
            }
        }
        for (int i=0;i<white::queens.size();i++) {
            if (find(white::queens[i].movelist.begin(), white::queens[i].movelist.end(), king_sq) 
            != white::queens[i].movelist.end()) {
                checker = "Q" + str(i);
                return true;
            }
        }
        for (int i=0;i<white::pawns.size();i++) {
            if (find(white::pawns[i].attacks.begin(), white::pawns[i].attacks.end(), king_sq) 
            != white::pawns[i].attacks.end()) {
                checker = "P" + str(i);
                return true;
            }
        }
        checker = "";
        return false;
    }

    void print_blocks() {
        for (int i=0;i<8;i++) {
            for (int j=0;j<8;j++) {
                cout << blocks[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void circle(int row, int col) {
        sf::CircleShape circle(8);
        circle.setPosition(col*UNIT + PIECES_PADDING_X + 22, row*UNIT + PIECES_PADDING_Y + 22);
        circle.setFillColor(sf::Color(66, 114, 118));
        window.draw(circle);
    }

    string get_piece(int row, int col) {
        for (int i=0;i<pawns.size();i++) {
            if (pawns[i].row == row and pawns[i].col == col) {
                return "P" + str(i);
            }
        }
        for (int i=0;i<knights.size();i++) {
            if (knights[i].row == row and knights[i].col == col) {
                return "N" + str(i);
            }
        }
        for (int i=0;i<bishops.size();i++) {
            if (bishops[i].row == row and bishops[i].col == col) {
                return "B" + str(i);
            }
        }
        for (int i=0;i<rooks.size();i++) {
            if (rooks[i].row == row and rooks[i].col == col) {
                return "R" + str(i);
            }
        }
        for (int i=0;i<queens.size();i++) {
            if (queens[i].row == row and queens[i].col == col) {
                return "Q" + str(i);
            }
        }
        for (int i=0;i<kings.size();i++) {
            if (kings[i].row == row and kings[i].col == col) {
                return "K" + str(i);
            }
        }
        return "nothin";
        // ERROR("Error from function `black::get_piece`: row = " + str(row) + ", col = " + str(col) + ".");
        // return NULL;
    }

    void update_moves() {
        for (Pawn& p : pawns) p.update_movelist();
        for (Knight& n : knights) n.update_movelist();
        for (Bishop& b : bishops) b.update_movelist();
        for (Rook& r : rooks) r.update_movelist();
        for (Queen& q : queens) q.update_movelist();
        for (King& k : kings) k.update_movelist();
    }

    void move(string piece, int row, int col) {
        for (int i=0;i<8;i++) {
            if (piece == "P" + str(i)) {
                pawns[i].move(row, col);
            }
        }
        for (int i=0;i<knights.size();i++) {
            if (piece == "N" + str(i)) {
                knights[i].move(row, col);
            }
        }
        for (int i=0;i<bishops.size();i++) {
            if (piece == "B" + str(i)) {
                bishops[i].move(row, col);
            }
        }
        for (int i=0;i<rooks.size();i++) {
            if (piece == "R" + str(i)) {
                rooks[i].move(row, col);
            }
        }
        for (int i=0;i<queens.size();i++) {
            if (piece == "Q" + str(i)) {
                queens[i].move(row, col);
            }
        }
        for (int i=0;i<kings.size();i++) {
            if (piece == "K" + str(i)) {
                kings[i].move(row, col);
            }
        }
        // captures
        if (white::blocks[row][col]) {
            white::blocks[row][col] = 0;
            string piece = white::get_piece(row, col);
            for (int i=0;i<8;i++) {
                if (piece == "P" + str(i)) {
                    white::pawns.erase(white::pawns.begin() + i); 
                }
            }
            for (int i=0;i<white::knights.size();i++) {
                if (piece == "N" + str(i)) {
                    white::knights.erase(white::knights.begin() + i); 
                }
            }
            for (int i=0;i<white::bishops.size();i++) {
                if (piece == "B" + str(i)) {
                    white::bishops.erase(white::bishops.begin() + i); 
                }
            }
            for (int i=0;i<white::rooks.size();i++) {
                if (piece == "R" + str(i)) {
                    white::rooks.erase(white::rooks.begin() + i); 
                }
            }
            for (int i=0;i<white::queens.size();i++) {
                if (piece == "Q" + str(i)) {
                    white::queens.erase(white::queens.begin() + i); 
                }
            }
            for (int i=0;i<white::kings.size();i++) {
                if (piece == "K" + str(i)) {
                    white::kings.erase(white::kings.begin() + i); 
                }
            }
        }
        update_moves();
        white::update_moves();
        history.n_moves ++;
        history.piece.push_back(piece);
        history.pos.push_back({row, col});
    }

    // show the moves of the piece on (row, col)
    void show_moves(string piece) {
        for (int i=0;i<pawns.size();i++) {
            if (piece == "P" + str(i)) {
                for (auto arr : pawns[i].movelist) {
                    circle(arr[0], arr[1]);
                }
            }
        }
        for (int i=0;i<knights.size();i++) {
            if (piece == "N" + str(i)) {
                for (auto arr : knights[i].movelist) {
                    circle(arr[0], arr[1]);
                }
            }
        }
        for (int i=0;i<bishops.size();i++) {
            if (piece == "B" + str(i)) {
                for (auto arr : bishops[i].movelist) {
                    circle(arr[0], arr[1]);
                }
            }
        }
        for (int i=0;i<rooks.size();i++) {
            if (piece == "R" + str(i)) {
                for (auto arr : rooks[i].movelist) {
                    circle(arr[0], arr[1]);
                }
            }
        }
        for (int i=0;i<queens.size();i++) {
            if (piece == "Q" + str(i)) {
                for (auto arr : queens[i].movelist) {
                    circle(arr[0], arr[1]);
                }
            }
        }
        for (int i=0;i<kings.size();i++) {
            if (piece == "K" + str(i)) {
                for (auto arr : kings[i].movelist) {
                    circle(arr[0], arr[1]);
                }
            }
        }
    }

    void init() {
        for (int i=0;i<8;i++) {
            for (int j=0;j<8;j++) {
                if (i == 0 or i == 1) {
                    blocks[i][j] = 1;
                } else {
                    blocks[i][j] = 0;
                }
            }
        }
        Bishop b1 = Bishop('B', 0, 2);
        Bishop b2 = Bishop('B', 0, 5);
        bishops.push_back(b1);
        bishops.push_back(b2);

        Knight n1 = Knight('B', 0, 1);
        Knight n2 = Knight('B', 0, 6);
        knights.push_back(n1);
        knights.push_back(n2);

        Rook r1 = Rook('B', 0, 0);
        Rook r2 = Rook('B', 0, 7);
        rooks.push_back(r1);
        rooks.push_back(r2);

        Queen q = Queen('B', 0, 3);
        queens.push_back(q);

        King k = King('B',0, 4);
        kings.push_back(k);

        for (int i=0;i<8;i++) pawns.push_back(Pawn('B', 1, i));
        update_moves();
    }

    void draw() {
        for (Bishop b : bishops) {
            if (!b.texture.loadFromFile("../assets/sprites/black/bishop.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            b.sprite.setTexture(b.texture);
            b.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            b.sprite.setPosition(b.x + PIECES_PADDING_X, b.y + PIECES_PADDING_Y);
            window.draw(b.sprite);
        }
        for (Knight n : knights) {
            if (!n.texture.loadFromFile("../assets/sprites/black/knight.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            n.sprite.setTexture(n.texture);
            n.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            n.sprite.setPosition(n.x + PIECES_PADDING_X, n.y + PIECES_PADDING_Y);
            window.draw(n.sprite);
        }
        for (Rook r : rooks) {
            if (!r.texture.loadFromFile("../assets/sprites/black/rook.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            r.sprite.setTexture(r.texture);
            r.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            r.sprite.setPosition(r.x + PIECES_PADDING_X, r.y + PIECES_PADDING_Y);
            window.draw(r.sprite);
        }
        for (Pawn p : pawns) {
            if (!p.texture.loadFromFile("../assets/sprites/black/pawn.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            p.sprite.setTexture(p.texture);
            p.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            p.sprite.setPosition(p.x + PIECES_PADDING_X, p.y + PIECES_PADDING_Y);
            window.draw(p.sprite);
        }
        for (Queen q : queens) {
            if (!q.texture.loadFromFile("../assets/sprites/black/queen.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            q.sprite.setTexture(q.texture);
            q.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            q.sprite.setPosition(q.x + PIECES_PADDING_X, q.y + PIECES_PADDING_Y);
            window.draw(q.sprite);
        }
        for (King k : kings) {
            if (!k.texture.loadFromFile("../assets/sprites/black/king.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            k.sprite.setTexture(k.texture);
            k.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            k.sprite.setPosition(k.x + PIECES_PADDING_X, k.y + PIECES_PADDING_Y);
            window.draw(k.sprite);
        }
    }
}