#pragma once

#include "graphics.h"
#include <vector>

using namespace std;

class moon:graphics
{
public:
    bool init();

    void Free();

    void render();

    void update();

    position posMoon;
};

