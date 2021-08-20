#include <iostream>
#include <vector>

#include "white.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"
#include "config.h"

using namespace std;

namespace white {
    vector<Bishop> bishops = {};
    vector<Knight> knights = {};
    vector<Rook> rooks = {};
    vector<Pawn> pawns = {};
    vector<Queen> queens = {};
    vector<King> kings = {};
    int blocks[8][8] = {};

    void print_blocks() {
        for (int i=0;i<8;i++) {
            for (int j=0;j<8;j++) {
                cout << blocks[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    

    // show the moves of the piece on (row, col)
    void show_moves(int row, int col) {

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
        Bishop b1 = Bishop(7, 2);
        Bishop b2 = Bishop(7, 5);
        bishops.push_back(b1);
        bishops.push_back(b2);

        Knight n1 = Knight(7, 1);
        Knight n2 = Knight(7, 6);
        knights.push_back(n1);
        knights.push_back(n2);

        Rook r1 = Rook(7, 0);
        Rook r2 = Rook(7, 7);
        rooks.push_back(r1);
        rooks.push_back(r2);

        Queen q = Queen(7, 3);
        queens.push_back(q);

        King k = King(7, 4);
        kings.push_back(k);

        for (int i=0;i<8;i++) pawns.push_back(Pawn('W', 6, i));
    }

    void draw() {
        for (Bishop b : bishops) {
            if (!b.texture.loadFromFile("../assets/sprites/white/bishop.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            b.sprite.setTexture(b.texture);
            b.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            b.sprite.setPosition((b.col*UNIT) + PIECES_PADDING_X, (b.row*UNIT) + PIECES_PADDING_Y);
            window.draw(b.sprite);
        }
        for (Knight n : knights) {
            if (!n.texture.loadFromFile("../assets/sprites/white/knight.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            n.sprite.setTexture(n.texture);
            n.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            n.sprite.setPosition((n.col*UNIT) + PIECES_PADDING_X, (n.row*UNIT) + PIECES_PADDING_Y);
            window.draw(n.sprite);
        }
        for (Rook r : rooks) {
            if (!r.texture.loadFromFile("../assets/sprites/white/rook.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            r.sprite.setTexture(r.texture);
            r.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            r.sprite.setPosition((r.col*UNIT) + PIECES_PADDING_X, (r.row*UNIT) + PIECES_PADDING_Y);
            window.draw(r.sprite);
        }
        for (Pawn p : pawns) {
            if (!p.texture.loadFromFile("../assets/sprites/white/pawn.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            p.sprite.setTexture(p.texture);
            p.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            p.sprite.setPosition((p.col*UNIT) + PIECES_PADDING_X, (p.row*UNIT) + PIECES_PADDING_Y);
            window.draw(p.sprite);
        }
        for (Queen q : queens) {
            if (!q.texture.loadFromFile("../assets/sprites/white/queen.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            q.sprite.setTexture(q.texture);
            q.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            q.sprite.setPosition((q.col*UNIT) + PIECES_PADDING_X, (q.row*UNIT) + PIECES_PADDING_Y);
            window.draw(q.sprite);
        }
        for (King k : kings) {
            if (!k.texture.loadFromFile("../assets/sprites/white/king.png")) {
                throw runtime_error("Could not load sprite file.");
            }
            k.sprite.setTexture(k.texture);
            k.sprite.setScale(PIECES_SCALE, PIECES_SCALE);
            k.sprite.setPosition((k.col*UNIT) + PIECES_PADDING_X, (k.row*UNIT) + PIECES_PADDING_Y);
            window.draw(k.sprite);
        }
    }
}