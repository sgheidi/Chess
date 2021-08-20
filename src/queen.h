#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include <SFML/Graphics.hpp>

class Queen {
    public:
        int row, col;
        sf::Sprite sprite;
        sf::Texture texture;
        Queen(int row, int col) : row(row), col(col) {}
};

#endif // CHESS_QUEEN_H