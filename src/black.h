#ifndef CHESS_BLACK_H
#define CHESS_BLACK_H

#include <vector>

#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"

using namespace std;

namespace black {
    extern vector<string> checker;
    extern vector<Bishop> bishops;
    extern vector<Knight> knights;
    extern vector<Rook> rooks;
    extern vector<Pawn> pawns;
    extern vector<Queen> queens;
    extern vector<King> kings;
    extern int blocks[8][8];
    bool in_check();
    void move(string piece, int row, int col);
    void init();
    void show_moves(string piece);
    void draw();
    void print_blocks();
    void update_moves();
    string get_piece(int row, int col);
}

#endif // CHESS_BLACK_H