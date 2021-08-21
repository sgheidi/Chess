#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // vector<vector<int>> vec = {{1}, {2}, {3}};
    // vector<int> el = {1};
    // if (find(vec.begin(), vec.end(), el) != vec.end()) {
    //     cout << "True" << endl;
    // }
    vector<vector<int>> blocks = {{1, 2}};
    if (blocks[-1][0]) {
        cout << "True" << endl;
    }
}