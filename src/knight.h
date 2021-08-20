#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include <SFML/Graphics.hpp>

class Knight {
    public:
        int row, col;
        sf::Sprite sprite;
        sf::Texture texture;
        Knight(int row, int col) : row(row), col(col) {}
};

#endif // CHESS_KNIGHT_H