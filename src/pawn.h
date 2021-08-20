#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include <SFML/Graphics.hpp>

using namespace std;

class Pawn {
    public:
        int row, col;
        char side;
        vector<vector<int>> movelist;
        sf::Sprite sprite;
        sf::Texture texture;
        Pawn(char side, int row, int col) : side(side), row(row), col(col) {
            movelist = {};
        }
        void update_movelist();
};

#endif // CHESS_PAWN_H