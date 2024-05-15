#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class position
{
public:
    short int x, y, angle, state;
    void getPos(const short int x, const short int y);
};

class graphics
{
public:
    graphics();

    ~graphics() {}

    bool isNULL();

    bool Load(string path, double scale = 1);

    short int getWidth();
    short int getHeight();

    void free();
    void Render(short int x, short int y, short int angle = 0, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    SDL_Texture* Texture;

    short int tWidth;
    short int tHeight;

    static SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;
    static SDL_Event event;
    static bool quit;
    static bool die;
    static short int score;

    static const short int SCREEN_WIDTH = 350;
    static const short int SCREEN_HEIGHT = 610;
    static const short int ROCKET_SPACE = 160;
    static const short int TOTAL_ROCKET = 4;
    static const short int ROCKET_DISTANCE = 220;
    static const short int MOON_HEIGHT = 140;
    static const short int ALIEN_WIDTH = 40;
    static const short int ALIEN_HEIGHT = 40;
};
