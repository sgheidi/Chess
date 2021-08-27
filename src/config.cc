#include <iostream>
#include <vector>

#include "config.h"

using namespace std;

// global window object
sf::RenderWindow window(sf::VideoMode(RES, RES), "Chess");

struct History history = {
    0,
    {},
    {},
    {},
    {},
    {},
};