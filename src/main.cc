#include <iostream>
#include <math.h>

#include "white.h"
#include "black.h"
#include "bishop.h"
#include "config.h"

using namespace std;

void rect(int* color, int row, int col) {
	sf::RectangleShape rectangle(sf::Vector2f(UNIT, UNIT));
	rectangle.setPosition(col*UNIT, row*UNIT);
	rectangle.setFillColor(sf::Color(color[0],color[1],color[2]));
	window.draw(rectangle);
}

void draw_board() {
	int light[3] = {255, 255, 255};
	int dark[3] = {96, 144, 148};
	for (int k=0; k<8; k++) {
		for (int i=0; i<8; i++) {
			if ((k + i) % 2 != 0) {
				rect(dark, k, i);
			} else {
				rect(light, k, i);
			}
		}
	}
}

void draw_select(int row, int col) {
	int color[3] = {166, 214, 218};
	if (row != -1 and col != -1 and (white::blocks[row][col] or black::blocks[row][col])) {
		rect(color, row, col);
	}
}

int main() {
	white::init();
	black::init();
	auto desktop = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i((desktop.width/2-window.getSize().x/2) + 250, desktop.height/2-window.getSize().y/2));
	int select_row = -1;
	int select_col = -1;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					case sf::Keyboard::B:
						black::print_blocks(); 
						break;
					case sf::Keyboard::W:
						white::print_blocks(); 
						break;
				}
      		}
      		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i position = sf::Mouse::getPosition(window);
				select_row = position.y / int(UNIT);
				select_col = position.x / int(UNIT);
				if (white::blocks[select_row][select_col]) {
					white::show_moves(select_row, select_col);
				}
			}
			window.clear();
			draw_board();
			draw_select(select_row, select_col);
			white::draw();
			black::draw();
			window.display();
		}
	}
}