#include <iostream>
#include <math.h>
#include <algorithm>

#include "white.h"
#include "black.h"
#include "common.h"

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

void take_back() {
//     int last = history.n_moves;
//     if (last == 0) {
//         print("No moves to undo!");
//         return;
//     }
//     white::move(history.piece[last-1], history.pos[last-1][0], history.pos[last-1][1], true);
// 	if (history.is_capture[last-1]) {
// 		for (int i=0;i<8;i++) {
// 			if (history.capture_piece[last-1] == "P" + str(i)) {
// 				black::pawns.push_back(Pawn('B', history.capture_sq[last-1][0], history.capture_sq[last-1][1]));
// 			}
// 		}
// 		for (int i=0;i<=black::knights.size();i++) {
// 			if (history.capture_piece[last-1] == "N" + str(i)) {
// 				black::knights.push_back(Knight('B', history.capture_sq[last-1][0], history.capture_sq[last-1][1]));
// 			}
// 		}
// 		for (int i=0;i<=black::bishops.size();i++) {
// 			if (history.capture_piece[last-1] == "B" + str(i)) {
// 				black::bishops.push_back(Bishop('B', history.capture_sq[last-1][0], history.capture_sq[last-1][1]));
// 			}
// 		}
// 		for (int i=0;i<=black::rooks.size();i++) {
// 			if (history.capture_piece[last-1] == "R" + str(i)) {
// 				black::rooks.push_back(Rook('B', history.capture_sq[last-1][0], history.capture_sq[last-1][1]));
// 			}
// 		}
// 		for (int i=0;i<=black::queens.size();i++) {
// 			if (history.capture_piece[last-1] == "Q" + str(i)) {
// 				black::queens.push_back(Queen('B', history.capture_sq[last-1][0], history.capture_sq[last-1][1]));
// 			}
// 		}
// 		for (int i=0;i<=black::kings.size();i++) {
// 			if (history.capture_piece[last-1] == "K" + str(i)) {
// 				black::kings.push_back(King('B', history.capture_sq[last-1][0], history.capture_sq[last-1][1]));
// 			}
// 		}
// 		black::blocks[history.capture_sq[last-1][0]][history.capture_sq[last-1][1]] = 1;
// 	}
// 	history.n_moves --;
// 	history.piece.resize(history.n_moves);
// 	history.pos.resize(history.n_moves);
// 	history.is_capture.resize(history.n_moves);
// 	history.capture_piece.resize(history.n_moves);
// 	history.capture_sq.resize(history.n_moves);
// 	white::update_moves();
// 	black::update_moves();
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
					case sf::Keyboard::L:
						black::print_blocks(); 
						break;
					case sf::Keyboard::W:
						white::print_blocks(); 
						break;
					case sf::Keyboard::P:
						black::pawns[0].print_movelist(); 
						break;
					case sf::Keyboard::N:
						black::knights[0].print_movelist(); 
						break;
					case sf::Keyboard::B:
						white::bishops[0].print_movelist(); 
						break;
					case sf::Keyboard::R:
						white::rooks[0].print_movelist(); 
						break;
					case sf::Keyboard::Q:
						white::queens[0].print_movelist(); 
						break;
					case sf::Keyboard::K:
						white::kings[0].print_movelist(); 
						break;
					case sf::Keyboard::H:
						print_hist(); 
						break;
					// case sf::Keyboard::H:
					// 	print_vec2(); 
					// 	break;
					#endif
					case sf::Keyboard::Z:
						take_back();
				}
      		}
			else if (event.type == sf::Event::MouseButtonReleased) {
				sf::Vector2i position = sf::Mouse::getPosition(window);
				int to_row = position.y / int(UNIT);
				int to_col = position.x / int(UNIT);
				vector<int> to_sq = {to_row, to_col};
				if (select_piece != "") {
					if (white::blocks[select_row][select_col]) {
						for (int i=0;i<8;i++) {
							if (select_piece == "P" + str(i) and 
							find(white::pawns[i].movelist.begin(), white::pawns[i].movelist.end(), to_sq) 
							!= white::pawns[i].movelist.end()) {
								white::move(select_piece, to_row, to_col, false);
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
								white::move(select_piece, to_row, to_col, false);
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
								white::move(select_piece, to_row, to_col, false);
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
								white::move(select_piece, to_row, to_col, false);
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
								white::move(select_piece, to_row, to_col, false);
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
								white::move(select_piece, to_row, to_col, false);
								last_selected_piece = "";
							}
							else if (select_piece == "K" + str(i) and 
							find(white::kings[i].movelist.begin(), white::kings[i].movelist.end(), to_sq) 
							== white::kings[i].movelist.end()) {
								if (to_sq[0] == 7) {
									// K castle
									if ((to_sq[1] == 6 or to_sq[1] == 7) and white::can_castle_K()) {
										white::move(select_piece, 10, 10, false);
									}
									// Q castle
									else if ((to_sq[1] == 0 or to_sq[1] == 2) and white::can_castle_Q())
										white::move(select_piece, 100, 100, false);
								}
								white::kings[i].x = white::kings[i].col * UNIT;
								white::kings[i].y = white::kings[i].row * UNIT;
							}
						}
					}
					else if (black::blocks[select_row][select_col]) {
						for (int i=0;i<8;i++) {
							if (select_piece == "P" + str(i) and 
							find(black::pawns[i].movelist.begin(), black::pawns[i].movelist.end(), to_sq) 
							!= black::pawns[i].movelist.end()) {
								black::move(select_piece, to_row, to_col);
							}
							else if (select_piece == "P" + str(i) and 
							find(black::pawns[i].movelist.begin(), black::pawns[i].movelist.end(), to_sq) 
							== black::pawns[i].movelist.end()) {
								black::pawns[i].x = black::pawns[i].col * UNIT;
								black::pawns[i].y = black::pawns[i].row * UNIT;
							}
						}
						for (int i=0;i<black::knights.size();i++) {
							if (select_piece == "N" + str(i) and 
							find(black::knights[i].movelist.begin(), black::knights[i].movelist.end(), to_sq) 
							!= black::knights[i].movelist.end()) {
								black::move(select_piece, to_row, to_col);
							}
							else if (select_piece == "N" + str(i) and 
							find(black::knights[i].movelist.begin(), black::knights[i].movelist.end(), to_sq) 
							== black::knights[i].movelist.end()) {
								black::knights[i].x = black::knights[i].col * UNIT;
								black::knights[i].y = black::knights[i].row * UNIT;
							}
						}
						for (int i=0;i<black::bishops.size();i++) {
							if (select_piece == "B" + str(i) and 
							find(black::bishops[i].movelist.begin(), black::bishops[i].movelist.end(), to_sq) 
							!= black::bishops[i].movelist.end()) {
								black::move(select_piece, to_row, to_col);
							}
							else if (select_piece == "B" + str(i) and 
							find(black::bishops[i].movelist.begin(), black::bishops[i].movelist.end(), to_sq) 
							== black::bishops[i].movelist.end()) {
								black::bishops[i].x = black::bishops[i].col * UNIT;
								black::bishops[i].y = black::bishops[i].row * UNIT;
							}
						}
						for (int i=0;i<black::rooks.size();i++) {
							if (select_piece == "R" + str(i) and 
							find(black::rooks[i].movelist.begin(), black::rooks[i].movelist.end(), to_sq) 
							!= black::rooks[i].movelist.end()) {
								black::move(select_piece, to_row, to_col);
							}
							else if (select_piece == "R" + str(i) and 
							find(black::rooks[i].movelist.begin(), black::rooks[i].movelist.end(), to_sq) 
							== black::rooks[i].movelist.end()) {
								black::rooks[i].x = black::rooks[i].col * UNIT;
								black::rooks[i].y = black::rooks[i].row * UNIT;
							}
						}
						for (int i=0;i<black::queens.size();i++) {
							if (select_piece == "Q" + str(i) and 
							find(black::queens[i].movelist.begin(), black::queens[i].movelist.end(), to_sq) 
							!= black::queens[i].movelist.end()) {
								black::move(select_piece, to_row, to_col);
							}
							else if (select_piece == "Q" + str(i) and 
							find(black::queens[i].movelist.begin(), black::queens[i].movelist.end(), to_sq) 
							== black::queens[i].movelist.end()) {
								black::queens[i].x = black::queens[i].col * UNIT;
								black::queens[i].y = black::queens[i].row * UNIT;
							}
						}
						for (int i=0;i<black::kings.size();i++) {
							if (select_piece == "K" + str(i) and 
							find(black::kings[i].movelist.begin(), black::kings[i].movelist.end(), to_sq) 
							!= black::kings[i].movelist.end()) {
								black::move(select_piece, to_row, to_col);
								last_selected_piece = "";
							}
							else if (select_piece == "K" + str(i) and 
							find(black::kings[i].movelist.begin(), black::kings[i].movelist.end(), to_sq) 
							== black::kings[i].movelist.end()) {
								if (to_sq[0] == 0) {
									// K castle
									if ((to_sq[1] == 6 or to_sq[1] == 7) and black::can_castle_K()) {
										black::move(select_piece, 10, 10);
									}
									// Q castle
									else if ((to_sq[1] == 0 or to_sq[1] == 2) and black::can_castle_Q())
										black::move(select_piece, 100, 100);
								}
								black::kings[i].x = black::kings[i].col * UNIT;
								black::kings[i].y = black::kings[i].row * UNIT;
							}
						}
					}
					select_piece = "";
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position = sf::Mouse::getPosition(window);
				select_row = position.y / int(UNIT);
				select_col = position.x / int(UNIT);
				if (white::blocks[select_row][select_col]) {
					select_piece = white::get_piece(select_row, select_col);
					last_selected_piece = select_piece;
				} else if (black::blocks[select_row][select_col]) {
					select_piece = black::get_piece(select_row, select_col);
					last_selected_piece = select_piece;
				} else {
					select_piece = "";
					last_selected_piece = "";
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i position = sf::Mouse::getPosition(window);
			if (select_piece != "") {
				if (white::blocks[select_row][select_col]) {
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
				else if (black::blocks[select_row][select_col]) {
					for (int i=0;i<8;i++) {
						if (select_piece == "P" + str(i)) {
							black::pawns[i].x = position.x - 2.6*PIECES_PADDING_X;
							black::pawns[i].y = position.y - 2.8*PIECES_PADDING_Y;
						}
					}
					for (int i=0;i<black::knights.size();i++) {
						if (select_piece == "N" + str(i)) {
							black::knights[i].x = position.x - 2.6*PIECES_PADDING_X;
							black::knights[i].y = position.y - 2.8*PIECES_PADDING_Y;
						}
					}
					for (int i=0;i<black::bishops.size();i++) {
						if (select_piece == "B" + str(i)) {
							black::bishops[i].x = position.x - 2.6*PIECES_PADDING_X;
							black::bishops[i].y = position.y - 2.8*PIECES_PADDING_Y;
						}
					}
					for (int i=0;i<black::rooks.size();i++) {
						if (select_piece == "R" + str(i)) {
							black::rooks[i].x = position.x - 2.6*PIECES_PADDING_X;
							black::rooks[i].y = position.y - 2.8*PIECES_PADDING_Y;
						}
					}
					for (int i=0;i<black::queens.size();i++) {
						if (select_piece == "Q" + str(i)) {
							black::queens[i].x = position.x - 2.6*PIECES_PADDING_X;
							black::queens[i].y = position.y - 2.8*PIECES_PADDING_Y;
						}
					}
					for (int i=0;i<black::kings.size();i++) {
						if (select_piece == "K" + str(i)) {
							black::kings[i].x = position.x - 2.6*PIECES_PADDING_X;
							black::kings[i].y = position.y - 2.8*PIECES_PADDING_Y;
						}
					}
				}
			}
		}
		window.clear();
		draw_board();
		draw_select(select_row, select_col);
		black::draw();
		white::draw();
		if (last_selected_piece != "") {
			if (white::blocks[select_row][select_col])
				white::show_moves(last_selected_piece);
			else if (black::blocks[select_row][select_col])
				black::show_moves(last_selected_piece);		
		}
		window.display();
	}
}