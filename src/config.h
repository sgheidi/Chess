#ifndef CHESS_CONFIG_H
#define CHESS_CONFIG_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

#define RES 800
#define UNIT RES/8
#define PIECES_PADDING_X 19
#define PIECES_PADDING_Y 17
#define PIECES_SCALE 1.2

#define print(x) cout << x << endl
#define str(x) std::to_string(x)

#define PRINT_DEBUG_ENABLED
#define NO_TURNS_DEBUG_ENABLED

extern sf::RenderWindow window;

inline void print_vec2(vector<vector<int>> v) {
    for (auto arr: v) {
        cout << "{" << arr[0] << " " << arr[1] << "}" << endl;
    }
    cout << endl;
}

#endif // CHESS_CONFIG_H