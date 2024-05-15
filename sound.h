#pragma once

#include <SDL_mixer.h>
#include <string>
#include "graphics.h"

using namespace std;

class sound:graphics
{
public:
    bool init();

    void Free();

    void playfly();

    void playcollide();

    void playclick();

    void playmusic();

    void rendersound1();

    void rendersound2();

    void musicstatus(bool x);

    bool checkSound();
    bool checkSound2();

private:
    const short int POS_X = 100;
    const short int POS_Y = 300;
    const short int POS_Y2 = 260;
    bool clicked = 1;
    bool isPlay = 0; bool isPlaymusic = 0;
    Mix_Chunk* fly = NULL;
    Mix_Chunk* collide = NULL;
    Mix_Chunk* drop = NULL;
    Mix_Chunk* click = NULL;

    Mix_Music* music = NULL;
    SDL_Rect Mute ;
    SDL_Rect Active ;
};

