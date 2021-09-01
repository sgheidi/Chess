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
#include "common.h"

using namespace std;

namespace black {
    vector<string> checker = {};
    vector<Bishop> bishops = {};
    vector<Knight> knights = {};
    vector<Rook> rooks = {};
    vector<Pawn> pawns = {};
    vector<Queen> queens = {};
    vector<King> kings = {};
    int blocks[8][8] = {};

    bool no_moves() {
        // for     
    }

    // return true if square (row, col) is in any of opponent pieces' movelists
    bool in_opp_movelist(int row, int col) {
        vector<int> sq = {row, col};
        for (int i=0;i<white::bishops.size();i++) {
            if (find(white::bishops[i].movelist.begin(), white::bishops[i].movelist.end(), sq) 
            != white::bishops[i].movelist.end()) {
                return true;
            }
        }
        for (int i=0;i<white::knights.size();i++) {
            if (find(white::knights[i].movelist.begin(), white::knights[i].movelist.end(), sq) 
            != white::knights[i].movelist.end()) {
                return true;
            }
        }
        for (int i=0;i<white::rooks.size();i++) {
            if (find(white::rooks[i].movelist.begin(), white::rooks[i].movelist.end(), sq) 
            != white::rooks[i].movelist.end()) {
                return true;
            }
        }
        for (int i=0;i<white::queens.size();i++) {
            if (find(white::queens[i].movelist.begin(), white::queens[i].movelist.end(), sq) 
            != white::queens[i].movelist.end()) {
                return true;
            }
        }
        for (int i=0;i<white::pawns.size();i++) {
            if (find(white::pawns[i].attacks.begin(), white::pawns[i].attacks.end(), sq) 
            != white::pawns[i].attacks.end()) {
                return true;
            }
        }
        for (int i=0;i<white::kings.size();i++) {
            if (find(white::kings[i].movelist.begin(), white::kings[i].movelist.end(), sq) 
            != white::kings[i].movelist.end()) {
                return true;
            }
        }
        return false;
    }

    bool can_castle_Q() {
        bool queenside_rook_present = false;
        if (!blocks[0][0] or !blocks[0][4] or blocks[0][1] or blocks[0][2] or blocks[0][3] 
        or white::blocks[0][1] or white::blocks[0][2] or white::blocks[0][3] or in_check()) {
            // print("1");
            return false;
        }
        for (Rook r : rooks) {
            if (r.row == 0 and r.col == 0 and !r.moved)
                queenside_rook_present = true;
        }
        if (kings[0].moved or kings[0].row != 0 or kings[0].col != 4) {
            // print("2");
            return false;
        }
        if (in_opp_movelist(0, 2) or in_opp_movelist(0, 3)) {
            // print("3");
            return false;
        }
        // if (!queenside_rook_present)
        //     print("4");
        return queenside_rook_present;
    }

    bool can_castle_K() {
        bool kingside_rook_present = false;
        if (!blocks[0][7] or !blocks[0][4] or blocks[0][6] or blocks[0][5] or white::blocks[0][6] or white::blocks[0][5]
        or in_check()) {
            // print("1");
            return false;
        }
        for (Rook r : rooks) {
            if (r.row == 0 and r.col == 7 and !r.moved)
                kingside_rook_present = true;
        }
        if (kings[0].moved or kings[0].row != 0 or kings[0].col != 4) {
            // print("2");
            return false;
        }
        if (in_opp_movelist(0, 5) or in_opp_movelist(0, 6)) {
            // print("3");
            return false;
        }
        // if (!kingside_rook_present)
        //     print("4");
        return kingside_rook_present;
    }

    bool in_check() {
        bool ret = false;
        checker.clear();
        vector<int> king_sq = {kings[0].row, kings[0].col};
        for (int i=0;i<white::bishops.size();i++) {
            if (find(white::bishops[i].movelist.begin(), white::bishops[i].movelist.end(), king_sq) 
            != white::bishops[i].movelist.end()) {
                checker.push_back("B" + str(i));
                ret = true;
            }
        }
        for (int i=0;i<white::knights.size();i++) {
            if (find(white::knights[i].movelist.begin(), white::knights[i].movelist.end(), king_sq) 
            != white::knights[i].movelist.end()) {
                checker.push_back("N" + str(i));
                ret = true;
            }
        }
        for (int i=0;i<white::rooks.size();i++) {
            if (find(white::rooks[i].movelist.begin(), white::rooks[i].movelist.end(), king_sq) 
            != white::rooks[i].movelist.end()) {
                checker.push_back("R" + str(i));
                ret = true;
            }
        }
        for (int i=0;i<white::queens.size();i++) {
            if (find(white::queens[i].movelist.begin(), white::queens[i].movelist.end(), king_sq) 
            != white::queens[i].movelist.end()) {
                checker.push_back("Q" + str(i));
                ret = true;
            }
        }
        for (int i=0;i<white::pawns.size();i++) {
            if (find(white::pawns[i].attacks.begin(), white::pawns[i].attacks.end(), king_sq) 
            != white::pawns[i].attacks.end()) {
                checker.push_back("P" + str(i));
                ret = true;
            }
        }
        for (int i=0;i<white::kings.size();i++) {
            if (find(white::kings[i].movelist.begin(), white::kings[i].movelist.end(), king_sq) 
            != white::kings[i].movelist.end()) {
                checker.push_back("K" + str(i));
                ret = true;
            }
        }
        return ret;
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
        for (Pawn& p : pawns) p.update_movelist(true);
        for (Knight& n : knights) n.update_movelist(true);
        for (Bishop& b : bishops) b.update_movelist(true);
        for (Rook& r : rooks) r.update_movelist(true);
        for (Queen& q : queens) q.update_movelist(true);
        for (King& k : kings) k.update_movelist();
    }

    void move(string piece, int row, int col) {
        // reset pawn's enpassant flags
        for (Pawn& p : pawns) p.is_enpassant = false;

        for (int i=0;i<8;i++) {
            if (piece == "P" + str(i)) {
                // promote
                if (row == 7) {
                    string promote_piece;
                    cout << "Enter piece: (Q, N, R, B) ";
                    cin >> promote_piece;
                    if (promote_piece == "Q") {
                        queens.push_back(Queen('B', row, col));
                    } else if (promote_piece == "R") {
                        rooks.push_back(Rook('B', row, col));
                    } else if (promote_piece == "B") {
                        bishops.push_back(Bishop('B', row, col));
                    } else if (promote_piece == "N") {
                        knights.push_back(Knight('B', row, col));
                    }
                    blocks[row][col] = 1;
                    blocks[pawns[i].row][pawns[i].col] = 0;
                    pawns.erase(pawns.begin() + i);
                    break;
                }
                // enpassant capture
                if (row == 5 and abs(pawns[i].col-col) == 1 and !white::blocks[row][col]) {
                    for (int i=0;i<white::pawns.size();i++) {
                        if (white::pawns[i].is_enpassant) {
                            white::pawns.erase(white::pawns.begin() + i); 
                            white::blocks[row-1][col] = 0;
                        }
                    }
                }
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
            if (row == 10 and col == 10) {  // K-castle
                kings[i].move(0, 6);
                for (Rook& r : rooks) {
                    if (r.col == 7 and r.row == 0)
                        r.move(0, 5);
                }
                break;
            } else if (row == 100 and col == 100) {  // Q-castle
                kings[i].move(0, 2);
                for (Rook& r : rooks) {
                    if (r.col == 0 and r.row == 0)
                        r.move(0, 3);
                }
                break;
            }
            if (piece == "K" + str(i)) {
                kings[i].move(row, col);
            }
        }
        // captures
        if (row != 10 and row != 100 and col != 10 and col != 100) {
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
                    if (arr[0] == 10 and arr[1] == 10) { // K-castle
                        circle(0, 6);
                        continue;
                    } else if (arr[0] == 100 and arr[1] == 100) { // Q-castle
                        circle(0, 2);
                        continue;
                    }
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