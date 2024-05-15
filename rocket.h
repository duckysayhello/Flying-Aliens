#pragma once

#include "graphics.h"
#include <iostream>
#include <vector>

using namespace std;

extern vector<position> posRocket;

class rocket:graphics
{
public:
    bool init();

    void Free();

    void render();

    void update();

    short int width() {return getWidth();}

    short int height() {return getHeight();}

    const short int randMin = -373 + 30;
    const short int randMax = SCREEN_HEIGHT - MOON_HEIGHT - 373 - ROCKET_DISTANCE - 30;
};

