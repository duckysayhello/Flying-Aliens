#include "moon.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

bool moon::init()
{
    posMoon.getPos(0, SCREEN_HEIGHT - MOON_HEIGHT);
    string back_path = "image/moon.png";
    if (isNULL())
    {
        if ( Load( back_path.c_str(), 1 ) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void moon::Free()
{
    free();
}

void moon::render()
{
    if (posMoon.x > -SCREEN_WIDTH && posMoon.x <= 0)
    {
        Render(posMoon.x, posMoon.y);
        Render(posMoon.x + SCREEN_WIDTH, posMoon.y, 0, NULL);
    }
    else
    {
        posMoon.getPos(0, SCREEN_HEIGHT - MOON_HEIGHT);
        Render(posMoon.x, posMoon.y);
    }

}

void moon::update()
{
    posMoon.x -= 3;
}

