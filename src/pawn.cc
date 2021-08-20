#include "pawn.h"
#include "white.h"
#include "black.h"

void Pawn::update_movelist() {
    if (side == 'W') {
        if (row == 6 and !black::blocks[row+2][col] and !white::blocks[row+2][col]) {
            movelist.push_back({row, col});
        }
    }
}