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
#define str(x) to_string(x)

#define PRINT_DEBUG_ENABLED
#define NO_TURNS_ENABLED

extern sf::RenderWindow window;

extern struct History {
    int n_moves;
    vector<vector<int>> pos;
    vector<string> piece;
    vector<bool> is_capture;
    vector<string> capture_piece;
    vector<vector<int>> capture_sq;
} history;

// takes set difference (v1 - v2), places back into v1
inline void diff(std::vector<std::vector<int>>& v1, std::vector<std::vector<int>> v2) {
    for (int i=v1.size()-1;i>=0;i--) {
        if (find(v2.begin(), v2.end(), v1[i]) != v2.end()) {
            v1.erase(v1.begin() + i);
        }
    }
}

#endif // CHESS_CONFIG_H