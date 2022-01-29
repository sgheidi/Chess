#include <iostream>
#include <vector>

#include "common.h"

using namespace std;

// global window object
sf::RenderWindow window(sf::VideoMode(RES, RES), "Chess");
bool in_checkmate = false;
bool in_draw = false;

struct History history = {
    0,
    {},
    {},
    {},
    {},
    {},
    {},
};