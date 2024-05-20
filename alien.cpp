#include "alien.h"
#include "graphics.h"
#include <stdio.h>
#include <iostream>

bool alien::init(bool skin, double scale)
{
    string path = "red";
    if(skin) path = "blue";
        posalien.getPos(100, SCREEN_HEIGHT / 2 - 10);
        ahead = 0;
        angle = 0;

    if (isNULL())
    {
        for (int i = 0; i < 3; i++)
        {
            string catpath = "image/cat/" + path + to_string(i + 1) + ".png";
            if (!textures[i].Load(catpath.c_str(), scale))
                return false;
        }
        return true;
    }
    return false;
}

void alien::Free()
{
    free();
}

void alien::render(int i)
{
    textures[i].Render(posalien.x, posalien.y, angle);
}

void alien::fall()
{
    if (die && posalien.y < SCREEN_HEIGHT - MOON_HEIGHT - ALIEN_HEIGHT)
    {
        if (time == 0)
        {
            x0 = posalien.y;
        }
        if (time >= 0)
        {
            posalien.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }
        angle = 180;
    }
    else return;
}

void alien::update(short int rocketWidth, short int rocketHeight, double scale)
{
    if (!die)
    {
        if (time == 0)
        {
            x0 = posalien.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posalien.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }
        if ( (posalien.x + textures[1].getWidth()*scale -10 > posRocket[ahead].x +5) && (posalien.x + 5 < posRocket[ahead].x + rocketWidth) &&
                (posalien.y + 5 < posRocket[ahead].y + rocketHeight || posalien.y  + textures[1].getHeight()*scale > posRocket[ahead].y + rocketHeight + ROCKET_SPACE + 5) )
        {
            die = true;
        }
        else if (posalien.x > posRocket[ahead].x + rocketWidth )
        {
            ahead = ( ahead + 1 ) % TOTAL_ROCKET;
            score++;
        }

        if (posalien.y > SCREEN_HEIGHT - MOON_HEIGHT -  ALIEN_HEIGHT - 5 || posalien.y < - 10 )
        {
            die = true;
        }
    }
}

