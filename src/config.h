#ifndef CHESS_CONFIG_H
#define CHESS_CONFIG_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define RES 800
#define UNIT RES/8
#define PIECES_PADDING_X 19
#define PIECES_PADDING_Y 17
#define PIECES_SCALE 1.2

#define print(x) cout << x << endl;

extern sf::RenderWindow window;

#endif // CHESS_CONFIG_H