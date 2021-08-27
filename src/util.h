#ifndef CHESS_UTIL_H
#define CHESS_UTIL_H

#include "config.h"

inline void print_vec2(vector<vector<int>> v) {
    for (auto arr: v) {
        cout << "{" << arr[0] << " " << arr[1] << "}" << endl;
    }
    cout << endl;
}

inline void print_hist() {
    print(history.n_moves);
}

#endif // CHESS_UTIL_H