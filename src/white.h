#ifndef CHESS_WHITE_H
#define CHESS_WHITE_H

#include <vector>

#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"

using namespace std;

namespace white {
    extern vector<Bishop> bishops;
    extern vector<Knight> knights;
    extern vector<Rook> rooks;
    extern vector<Pawn> pawns;
    extern vector<Queen> queens;
    extern vector<King> kings;
    extern int blocks[8][8];
    void move(string piece, int row, int col);
    void init();
    void show_moves(string piece);
    void draw();
    void print_blocks();
    void update_movelist();
    string get_piece(int row, int col);
}

#endif // CHESS_WHITE_H