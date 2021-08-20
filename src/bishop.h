#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include <SFML/Graphics.hpp>

class Bishop {
    public:
        int row, col;
        sf::Sprite sprite;
        sf::Texture texture;
        Bishop(int row, int col) : row(row), col(col) {}
};

#endif // CHESS_BISHOP_H