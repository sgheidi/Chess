#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <SFML/Graphics.hpp>
#include "common.h"

using namespace std;

class Piece {
    public:
        int x, y;
        vector<vector<int>> movelist;
        sf::Sprite sprite;
        sf::Texture texture;
        inline void print_movelist() const {
            print_vec2(movelist);
        }

        // virtual void move(int row, int col) = 0;
        // virtual void update_movelist(bool check_pin) = 0;
};

#endif // CHESS_PIECE_H