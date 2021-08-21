#include <iostream>
#include <math.h>
#include <algorithm>

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
	int light[3] = {230, 230, 230};
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
	if (row != -1 and col != -1) {
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
	string select_piece = "";
	string last_selected_piece = "";
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					#ifdef PRINT_DEBUG_ENABLED
					case sf::Keyboard::B:
						black::print_blocks(); 
						break;
					case sf::Keyboard::W:
						white::print_blocks(); 
						break;
					case sf::Keyboard::P:
						white::pawns[0].print_movelist(); 
						break;
					case sf::Keyboard::N:
						white::knights[0].print_movelist(); 
						break;
					#endif
				}
      		}
			else if (event.type == sf::Event::MouseButtonReleased) {
				vector<int> to_sq = {select_row, select_col};
				for (int i=0;i<8;i++) {
					if (select_piece == "P" + str(i) and 
					find(white::pawns[i].movelist.begin(), white::pawns[i].movelist.end(), to_sq) 
					!= white::pawns[i].movelist.end()) {
						white::move(select_piece, select_row, select_col);
					}
					else if (select_piece == "P" + str(i) and 
					find(white::pawns[i].movelist.begin(), white::pawns[i].movelist.end(), to_sq) 
					== white::pawns[i].movelist.end()) {
						white::pawns[i].x = white::pawns[i].col * UNIT;
						white::pawns[i].y = white::pawns[i].row * UNIT;
					}
				}
				for (int i=0;i<white::knights.size();i++) {
					if (select_piece == "N" + str(i) and 
					find(white::knights[i].movelist.begin(), white::knights[i].movelist.end(), to_sq) 
					!= white::knights[i].movelist.end()) {
						white::move(select_piece, select_row, select_col);
					}
					else if (select_piece == "N" + str(i) and 
					find(white::knights[i].movelist.begin(), white::knights[i].movelist.end(), to_sq) 
					== white::knights[i].movelist.end()) {
						white::knights[i].x = white::knights[i].col * UNIT;
						white::knights[i].y = white::knights[i].row * UNIT;
					}
				}
				for (int i=0;i<white::bishops.size();i++) {
					if (select_piece == "B" + str(i) and 
					find(white::bishops[i].movelist.begin(), white::bishops[i].movelist.end(), to_sq) 
					!= white::bishops[i].movelist.end()) {
						white::move(select_piece, select_row, select_col);
					}
					else if (select_piece == "B" + str(i) and 
					find(white::bishops[i].movelist.begin(), white::bishops[i].movelist.end(), to_sq) 
					== white::bishops[i].movelist.end()) {
						white::bishops[i].x = white::bishops[i].col * UNIT;
						white::bishops[i].y = white::bishops[i].row * UNIT;
					}
				}
				for (int i=0;i<white::rooks.size();i++) {
					if (select_piece == "R" + str(i) and 
					find(white::rooks[i].movelist.begin(), white::rooks[i].movelist.end(), to_sq) 
					!= white::rooks[i].movelist.end()) {
						white::move(select_piece, select_row, select_col);
					}
					else if (select_piece == "R" + str(i) and 
					find(white::rooks[i].movelist.begin(), white::rooks[i].movelist.end(), to_sq) 
					== white::rooks[i].movelist.end()) {
						white::rooks[i].x = white::rooks[i].col * UNIT;
						white::rooks[i].y = white::rooks[i].row * UNIT;
					}
				}
				for (int i=0;i<white::queens.size();i++) {
					if (select_piece == "Q" + str(i) and 
					find(white::queens[i].movelist.begin(), white::queens[i].movelist.end(), to_sq) 
					!= white::queens[i].movelist.end()) {
						white::move(select_piece, select_row, select_col);
					}
					else if (select_piece == "Q" + str(i) and 
					find(white::queens[i].movelist.begin(), white::queens[i].movelist.end(), to_sq) 
					== white::queens[i].movelist.end()) {
						white::queens[i].x = white::queens[i].col * UNIT;
						white::queens[i].y = white::queens[i].row * UNIT;
					}
				}
				for (int i=0;i<white::kings.size();i++) {
					if (select_piece == "K" + str(i) and 
					find(white::kings[i].movelist.begin(), white::kings[i].movelist.end(), to_sq) 
					!= white::kings[i].movelist.end()) {
						white::move(select_piece, select_row, select_col);
					}
					else if (select_piece == "K" + str(i) and 
					find(white::kings[i].movelist.begin(), white::kings[i].movelist.end(), to_sq) 
					== white::kings[i].movelist.end()) {
						white::kings[i].x = white::kings[i].col * UNIT;
						white::kings[i].y = white::kings[i].row * UNIT;
					}
				}
				select_piece = "";
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i position = sf::Mouse::getPosition(window);
			select_row = position.y / int(UNIT);
			select_col = position.x / int(UNIT);
			if (white::blocks[select_row][select_col] and select_piece == "") {
				select_piece = white::get_piece(select_row, select_col);
				last_selected_piece = select_piece;	
			}
			for (int i=0;i<8;i++) {
				if (select_piece == "P" + str(i)) {
					white::pawns[i].x = position.x - 2.6*PIECES_PADDING_X;
					white::pawns[i].y = position.y - 2.8*PIECES_PADDING_Y;
				}
			}
			for (int i=0;i<white::knights.size();i++) {
				if (select_piece == "N" + str(i)) {
					white::knights[i].x = position.x - 2.6*PIECES_PADDING_X;
					white::knights[i].y = position.y - 2.8*PIECES_PADDING_Y;
				}
			}
			for (int i=0;i<white::bishops.size();i++) {
				if (select_piece == "B" + str(i)) {
					white::bishops[i].x = position.x - 2.6*PIECES_PADDING_X;
					white::bishops[i].y = position.y - 2.8*PIECES_PADDING_Y;
				}
			}
			for (int i=0;i<white::rooks.size();i++) {
				if (select_piece == "R" + str(i)) {
					white::rooks[i].x = position.x - 2.6*PIECES_PADDING_X;
					white::rooks[i].y = position.y - 2.8*PIECES_PADDING_Y;
				}
			}
			for (int i=0;i<white::queens.size();i++) {
				if (select_piece == "Q" + str(i)) {
					white::queens[i].x = position.x - 2.6*PIECES_PADDING_X;
					white::queens[i].y = position.y - 2.8*PIECES_PADDING_Y;
				}
			}
			for (int i=0;i<white::kings.size();i++) {
				if (select_piece == "K" + str(i)) {
					white::kings[i].x = position.x - 2.6*PIECES_PADDING_X;
					white::kings[i].y = position.y - 2.8*PIECES_PADDING_Y;
				}
			}
		}
		window.clear();
		draw_board();
		draw_select(select_row, select_col);
		black::draw();
		if (last_selected_piece != "")
			white::show_moves(last_selected_piece);
		white::draw();
		window.display();
	}
}