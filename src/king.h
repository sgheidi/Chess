#ifndef CHESS_KING_H
#define CHESS_KING_H

#include <SFML/Graphics.hpp>

class King {
    public:
        int row, col;
        sf::Sprite sprite;
        sf::Texture texture;
        King(int row, int col) : row(row), col(col) {}
};

#endif // CHESS_KING_H