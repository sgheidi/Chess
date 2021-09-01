#ifndef CHESS_CONFIG_H
#define CHESS_CONFIG_H

#include <vector>
#include <iostream>
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

// takes set difference (v1 - v2), places result into v1
inline void diff(std::vector<std::vector<int>>& v1, std::vector<std::vector<int>> v2) {
    for (int i=v1.size()-1;i>=0;i--) {
        if (find(v2.begin(), v2.end(), v1[i]) != v2.end()) {
            v1.erase(v1.begin() + i);
        }
    }
}

inline void print_vec2(vector<vector<int>> v) {
    for (auto arr: v) {
        cout << "{" << arr[0] << " " << arr[1] << "}" << endl;
    }
    cout << endl;
}

inline void print_hist() {
    print(history.n_moves);
}

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

inline void ERROR(string msg) {
    cout << RED << msg << RESET << endl;
    exit(1);
}

inline void STATUS(string msg) {
    cout << RED << msg << RESET << endl;
}

#endif // CHESS_CONFIG_H