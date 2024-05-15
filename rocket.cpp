#include "rocket.h"
#include "stdio.h"

vector<position> posRocket;

bool rocket::init()
{
    posRocket.clear();
    for (signed char i = 0; i < TOTAL_ROCKET; i++)
    {
        position temp;
        temp.getPos(SCREEN_WIDTH + i * ROCKET_DISTANCE + 350, (rand() % (randMax - randMin + 1)) + randMin);
        posRocket.push_back(temp);
    }
    if (isNULL())
    {
        if (Load( "image/rocket.png", 1 ))
        {
            return true;
        }
    }
    return false;
}

void rocket::Free()
{
    free();
}

void rocket::render()
{
    for (signed char i = 0; i < TOTAL_ROCKET; i++)
    {
        if (posRocket[i].x <= SCREEN_WIDTH && posRocket[i].x > -getWidth())
        {
            Render(posRocket[i].x, posRocket[i].y);
        }
        Render(posRocket[i].x, posRocket[i].y + getHeight() + ROCKET_SPACE, 180);
    }
}

void rocket::update()
{
    if (!die)
    {
        for (signed char i = 0; i < TOTAL_ROCKET; i++)
        {
            if (posRocket[i].x < - getWidth())
            {
                posRocket[i].y = (rand() % (randMax - randMin + 1)) + randMin;
                posRocket[i].x = posRocket[(i + TOTAL_ROCKET - 1) % TOTAL_ROCKET].x + ROCKET_DISTANCE;
            }
            else
            {
                posRocket[i].x -= 3;
            }
        }
    }
}

