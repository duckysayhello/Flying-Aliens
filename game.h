#pragma once

#include "alien.h"
#include "rocket.h"
#include "moon.h"
#include "sound.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class game:graphics
{
public:
    struct input
    {
        enum type { QUIT, PLAY, NONE, PAUSE, SETTING, TUTOR};
        type Type;
    };
    input userInput;

    bool clicked = false;
    int x_mouse = 0;
    int y_mouse = 0;

    alien alien;
    rocket rocket;
    sound sound;
    moon moon;
public:
    game();

    ~game();

    bool initGraphic();

    bool isQuit()
    {
        return quit();
    }

    bool isDie()
    {
        return die;
    }

    int getRocketWidth()
    {
        return rocket.width();
    }

    int getRocketHeight()
    {
        return rocket.height();
    }

    void takeInput();

    void display();

    void releaseGraphic();

    void renderScoreSmall();

    void renderScoreLarge();

    void rendermenubackground();

    void renderBestScore();

    void renderready();

    void rendermoon();

    void renderbackground();

    bool rendertutorbutton();

    void rendertutortab();

    void renderpausetab();

    bool changeskin(bool k);

    void pause();

    void resume();

    void rendermenu();

    void blueskin();

    void redskin();

    void redxskin();

    void bluexskin();

    bool out();

    bool play();

    bool rendertomenu();

    bool options();

    bool quit();

    void rendergameover();

    void rendertrophy();

    void replay();

    bool checkReplay();

    void Restart();

    short int bestScore;
};

