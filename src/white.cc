#include <iostream>
#include <vector>

#include "white.h"
#include "black.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"
#include "common.h"

using namespace std;

namespace white {
    vector<string> checker = {};
    vector<Bishop> bishops = {};
    vector<Knight> knights = {};
    vector<Rook> rooks = {};
    vector<Pawn> pawns = {};
    vector<Queen> queens = {};
    vector<King> kings = {};
    int blocks[8][8] = {};

    bool no_moves() {

    }

    // return true if square (row, col) is in any of opponent pieces' movelists
    bool in_opp_movelist(int row, int col) {
        vector<int> sq = {row, col};
        for (int i=0;i<black::bishops.size();i++) {
            if (find(black::bishops[i].movelist.begin(), black::bishops[i].movelist.end(), sq) 
            != black::bishops[i].movelist.end()) {
                return true;
            }
        }
        for (int i=0;i<black::knights.size();i++) {
            if (find(black::knights[i].movelist.begin(), black::knights[i].movelist.end(), sq) 
            != black::knights[i].movelist.end()) {
                return true;
            }
        }
        for (int i=0;i<black::rooks.size();i++) {
            if (find(black::rooks[i].movelist.begin(), black::rooks[i].movelist.end(), sq) 
            != black::rooks[i].movelist.end()) {
                return true;
            }
        }
        for (int i=0;i<black::queens.size();i++) {
            if (find(black::queens[i].movelist.begin(), black::queens[i].movelist.end(), sq) 
            != black::queens[i].movelist.end()) {
                return true;
            }
        }
        for (int i=0;i<black::pawns.size();i++) {
            if (find(black::pawns[i].attacks.begin(), black::pawns[i].attacks.end(), sq) 
            != black::pawns[i].attacks.end()) {
                return true;
            }
        }
        for (int i=0;i<black::kings.size();i++) {
            if (find(black::kings[i].movelist.begin(), black::kings[i].movelist.end(), sq) 
            != black::kings[i].movelist.end()) {
                return true;
            }
        }
        return false;
    }

    bool can_castle_Q() {
        bool queenside_rook_present = false;
        if (!blocks[7][0] or !blocks[7][4] or blocks[7][1] or blocks[7][2] or blocks[7][3] 
        or black::blocks[7][1] or black::blocks[7][2] or black::blocks[7][3] or in_check()) {
            // print("1");
            return false;
        }
        for (Rook r : rooks) {
            if (r.row == 7 and r.col == 0 and !r.moved)
                queenside_rook_present = true;
        }
        if (kings[0].moved or kings[0].row != 7 or kings[0].col != 4) {
            // print("2");
            return false;
        }
        if (in_opp_movelist(7, 2) or in_opp_movelist(7, 3)) {
            // print("3");
            return false;
        }
        // if (!queenside_rook_present)
        //     print("4");
        return queenside_rook_present;
    }

    bool can_castle_K() {
        bool kingside_rook_present = false;
        if (!blocks[7][7] or !blocks[7][4] or blocks[7][6] or blocks[7][5] or black::blocks[7][6] or black::blocks[7][5]
        or in_check()) {
            // print("1");
            return false;
        }
        for (Rook r : rooks) {
            if (r.row == 7 and r.col == 7 and !r.moved)
                kingside_rook_present = true;
        }
        if (kings[0].moved or kings[0].row != 7 or kings[0].col != 4) {
            // print("2");
            return false;
        }
        if (in_opp_movelist(7, 5) or in_opp_movelist(7, 6)) {
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
        for (int i=0;i<black::bishops.size();i++) {
            if (find(black::bishops[i].movelist.begin(), black::bishops[i].movelist.end(), king_sq) 
            != black::bishops[i].movelist.end()) {
                checker.push_back("B" + str(i));
                ret = true;
            }
        }
        for (int i=0;i<black::knights.size();i++) {
            if (find(black::knights[i].movelist.begin(), black::knights[i].movelist.end(), king_sq) 
            != black::knights[i].movelist.end()) {
                checker.push_back("N" + str(i));
                ret = true;
            }
        }
        for (int i=0;i<black::rooks.size();i++) {
            if (find(black::rooks[i].movelist.begin(), black::rooks[i].movelist.end(), king_sq) 
            != black::rooks[i].movelist.end()) {
                checker.push_back("R" + str(i));
                ret = true;
            }
        }
        for (int i=0;i<black::queens.size();i++) {
            if (find(black::queens[i].movelist.begin(), black::queens[i].movelist.end(), king_sq) 
            != black::queens[i].movelist.end()) {
                checker.push_back("Q" + str(i));
                ret = true;
            }
        }
        for (int i=0;i<black::pawns.size();i++) {
            if (find(black::pawns[i].attacks.begin(), black::pawns[i].attacks.end(), king_sq) 
            != black::pawns[i].attacks.end()) {
                checker.push_back("P" + str(i));
                ret = true;
            }
        }
        for (int i=0;i<black::kings.size();i++) {
            if (find(black::kings[i].movelist.begin(), black::kings[i].movelist.end(), king_sq) 
            != black::kings[i].movelist.end()) {
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
        ERROR("Error from function `white::get_piece`: row = " + str(row) + ", col = " + str(col) + ".");
    }

    void update_moves() {
        for (Pawn& p : pawns) p.update_movelist(true);
        for (Knight& n : knights) n.update_movelist(true);
        for (Bishop& b : bishops) b.update_movelist(true);
        for (Rook& r : rooks) r.update_movelist(true);
        for (Queen& q : queens) q.update_movelist(true);
        for (King& k : kings) k.update_movelist();
    }

    void move(string piece, int row, int col, bool is_undo) {
        // reset pawn's enpassant flags
        for (Pawn& p : pawns) p.is_enpassant = false;
        
        for (int i=0;i<8;i++) {
            if (piece == "P" + str(i)) {
                // promote
                if (row == 0) {
                    string promote_piece;
                    cout << "Enter piece: (Q, N, R, B) ";
                    cin >> promote_piece;
                    if (promote_piece == "Q") {
                        queens.push_back(Queen('W', row, col));
                    } else if (promote_piece == "R") {
                        rooks.push_back(Rook('W', row, col));
                    } else if (promote_piece == "B") {
                        bishops.push_back(Bishop('W', row, col));
                    } else if (promote_piece == "N") {
                        knights.push_back(Knight('W', row, col));
                    }
                    blocks[row][col] = 1;
                    blocks[pawns[i].row][pawns[i].col] = 0;
                    pawns.erase(pawns.begin() + i);
                    break;
                }
                // enpassant capture
                if (row == 2 and abs(pawns[i].col-col) == 1 and !black::blocks[row][col]) {
                    for (int i=0;i<black::pawns.size();i++) {
                        if (black::pawns[i].is_enpassant) {
                            black::pawns.erase(black::pawns.begin() + i); 
                            black::blocks[row+1][col] = 0;
                        }
                    }
                }
                if (!is_undo) history.pos.push_back({pawns[i].row, pawns[i].col});
                pawns[i].move(row, col);
            }
        }
        for (int i=0;i<knights.size();i++) {
            if (piece == "N" + str(i)) {
                if (!is_undo) history.pos.push_back({knights[i].row, knights[i].col});
                knights[i].move(row, col);
            }
        }
        for (int i=0;i<bishops.size();i++) {
            if (piece == "B" + str(i)) {
                if (!is_undo) history.pos.push_back({bishops[i].row, bishops[i].col});
                bishops[i].move(row, col);
            }
        }
        for (int i=0;i<rooks.size();i++) {
            if (piece == "R" + str(i)) {
                if (!is_undo) history.pos.push_back({rooks[i].row, rooks[i].col});
                rooks[i].move(row, col);
            }
        }
        for (int i=0;i<queens.size();i++) {
            if (piece == "Q" + str(i)) {
                if (!is_undo) history.pos.push_back({queens[i].row, queens[i].col});
                queens[i].move(row, col);
            }
        }
        for (int i=0;i<kings.size();i++) {
            if (row == 10 and col == 10) {  // K-castle
                kings[i].move(7, 6);
                for (Rook& r : rooks) {
                    if (r.col == 7 and r.row == 7)
                        r.move(7, 5);
                }
                break;
            } else if (row == 100 and col == 100) {  // Q-castle
                kings[i].move(7, 2);
                for (Rook& r : rooks) {
                    if (r.col == 0 and r.row == 7)
                        r.move(7, 3);
                }
                break;
            }
            if (piece == "K" + str(i)) {
                if (!is_undo) history.pos.push_back({kings[i].row, kings[i].col});
                kings[i].move(row, col);
            }
        }
        // captures
        if (row != 10 and row != 100 and col != 10 and col != 100) {
            if (black::blocks[row][col]) {
                black::blocks[row][col] = 0;
                string capture_piece = black::get_piece(row, col);
                if (!is_undo) {
                    history.is_capture.push_back(true);
                    history.capture_piece.push_back(capture_piece);
                    history.capture_sq.push_back({row, col});
                }
                for (int i=0;i<8;i++) {
                    if (capture_piece == "P" + str(i)) {
                        black::pawns.erase(black::pawns.begin() + i); 
                    }
                }
                for (int i=0;i<black::knights.size();i++) {
                    if (capture_piece == "N" + str(i)) {
                        black::knights.erase(black::knights.begin() + i); 
                    }
                }
                for (int i=0;i<black::bishops.size();i++) {
                    if (capture_piece == "B" + str(i)) {
                        black::bishops.erase(black::bishops.begin() + i); 
                    }
                }
                for (int i=0;i<black::rooks.size();i++) {
                    if (capture_piece == "R" + str(i)) {
                        black::rooks.erase(black::rooks.begin() + i); 
                    }
                }
                for (int i=0;i<black::queens.size();i++) {
                    if (capture_piece == "Q" + str(i)) {
                        black::queens.erase(black::queens.begin() + i); 
                    }
                }
                for (int i=0;i<black::kings.size();i++) {
                    if (capture_piece == "K" + str(i)) {
                        black::kings.erase(black::kings.begin() + i); 
                    }
                }
            }
            else {
                if (!is_undo) {
                    history.is_capture.push_back(false);
                    history.capture_piece.push_back("");
                    history.capture_sq.push_back({-1,-1});
                }
            }
        }
        update_moves();
        black::update_moves();
        if (!is_undo) {
            history.n_moves ++;
            history.piece.push_back(piece);
        }
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
                        circle(7, 6);
                        continue;
                    } else if (arr[0] == 100 and arr[1] == 100) { // Q-castle
                        circle(7, 2);
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
                if (i == 6 or i == 7) {
                    blocks[i][j] = 1;
                } else {
                    blocks[i][j] = 0;
                }
            }
        }
        Bishop b1 = Bishop('W', 7, 2);
        Bishop b2 = Bishop('W', 7, 5);
        bishops.push_back(b1);
        bishops.push_back(b2);

        Knight n1 = Knight('W', 7, 1);
        Knight n2 = Knight('W', 7, 6);
        knights.push_back(n1);
        knights.push_back(n2);

        Rook r1 = Rook('W', 7, 0);
        Rook r2 = Rook('W', 7, 7);
        rooks.push_back(r1);
        rooks.push_back(r2);

        Queen q = Queen('W', 7, 3);
        queens.push_back(q);

        King k = King('W', 7, 4);
        kings.push_back(k);

        for (int i=0;i<8;i++) pawns.push_back(Pawn('W', 6, i));
        update_moves();
    }

    void draw() {
        for (Bishop b : bishops) b.draw();
        for (Knight n : knights) {
            if (!n.texture.loadFromFile("../assets/sprites/white/knight.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            n.sprite.setTexture(n.texture);
            n.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            n.sprite.setPosition(n.x + PIECES_PADDING_X, n.y + PIECES_PADDING_Y);
            window.draw(n.sprite);
        }
        for (Rook r : rooks) {
            if (!r.texture.loadFromFile("../assets/sprites/white/rook.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            r.sprite.setTexture(r.texture);
            r.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            r.sprite.setPosition(r.x + PIECES_PADDING_X, r.y + PIECES_PADDING_Y);
            window.draw(r.sprite);
        }
        for (Pawn p : pawns) {
            if (!p.texture.loadFromFile("../assets/sprites/white/pawn.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            p.sprite.setTexture(p.texture);
            p.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            p.sprite.setPosition(p.x + PIECES_PADDING_X, p.y + PIECES_PADDING_Y);
            window.draw(p.sprite);
        }
        for (Queen q : queens) {
            if (!q.texture.loadFromFile("../assets/sprites/white/queen.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            q.sprite.setTexture(q.texture);
            q.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            q.sprite.setPosition(q.x + PIECES_PADDING_X, q.y + PIECES_PADDING_Y);
            window.draw(q.sprite);
        }
        for (King k : kings) {
            if (!k.texture.loadFromFile("../assets/sprites/white/king.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            k.sprite.setTexture(k.texture);
            k.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            k.sprite.setPosition(k.x + PIECES_PADDING_X, k.y + PIECES_PADDING_Y);
            window.draw(k.sprite);
        }
    }
}