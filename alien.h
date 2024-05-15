#pragma once

#include "graphics.h"
#include "rocket.h"

using namespace std;

class alien:graphics
{
public:
    bool init(bool isDark, double scale);

    void animation();

    void render(int i);

    void Free();

    void resetTime()
    {
        time = 0;
    }

    void fall();

    void update(short int pileWidth, short int pileHeight, double scale);
    short int angle, time, x0;
    short int ahead = 0;


    graphics textures[4];
    position posalien;
};

