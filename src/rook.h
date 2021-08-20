#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include <SFML/Graphics.hpp>

class Rook {
    public:
        int row, col;
        sf::Sprite sprite;
        sf::Texture texture;
        Rook(int row, int col) : row(row), col(col) {}
};

#endif // CHESS_ROOK_H