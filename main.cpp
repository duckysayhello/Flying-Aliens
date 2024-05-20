#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "graphics.h"
#include "game.h"
#include "alien.h"
const int FPS = 60;
const int frameDelay = 1000 / FPS;

using namespace std;

int main(int argc, char *argv[])
{
    Uint32 frameStart;
    short int frameTime;
    game g;
    bool ready = 0;
    bool showmenu = 0;
    bool ispause = 0;
    bool issound = 1;
    bool redon = 1;
    short int frame = 0;
    int idx = 0;
    bool menu = 1;
    bool quit = 0;
    bool rep = 1;
    bool sound = 1;
    bool music = 1;
    bool showtut = 0;

    while(!g.isQuit() && !quit)
    {
        frameStart = SDL_GetTicks();
        if (g.isDie())
        {
            if (ready)
            {
                g.sound.playcollide();
                g.alien.render(0);
            }
            g.userInput.Type = game::input::NONE;
            while(g.isDie() && !g.isQuit() && !quit)
            {
                g.takeInput();

                g.renderbackground();
                g.rocket.render();
                g.moon.render();
                if (ready)
                {

                    g.alien.render(0);
                    g.alien.fall();
                    g.rendergameover();
                    if(g.checkReplay())
                    {
                        g.sound.playclick();
                        ready=0;
                        g.clicked =0;

                    }
                    if(g.rendertomenu())
                    {
                        menu=1;
                        ready=0;
                        g.sound.playclick();
                    }
                    g.rendertrophy();
                    g.renderScoreSmall();
                    g.renderBestScore();
                    g.replay();
                }
                else
                {

                    if (menu)
                    {

                        g.rendermenubackground();
                        g.moon.render();

                        if (rep)
                        {
                            g.sound.playmusic();
                            rep=0;
                        }
                        if (g.play())
                        {
                            if(!showmenu)
                            {
                                menu=0;
                                g.sound.playclick();
                            }
                        }
                        if (g.quit()) quit=1;
                        if (g.rendertutorbutton())
                        {
                            g.sound.playclick();
                            showtut=1;
                        }
                        if (g.options())
                        {
                            if (!showmenu) g.sound.playclick();
                            showmenu=1;
                        }
                        if(showtut)
                        {
                            g.rendertutortab();
                            if (g.out())
                            {
                                g.sound.playclick();
                                showtut=0;
                            }
                        }
                        if (showmenu)
                        {
                            g.rendermenu();
                            if (g.out())
                            {
                                g.sound.playclick();
                                showmenu=0;
                            }
                            g.sound.musicstatus(music);
                            g.sound.rendersound1();
                            g.sound.rendersound2();
                            if (!redon)
                            {
                                g.redxskin();
                                g.blueskin();
                            }
                            else
                            {
                                g.bluexskin();
                                g.redskin();
                            }
                            if (g.userInput.Type == game::input::PLAY)
                            {
                                if (g.sound.checkSound())
                                {
                                    issound=!issound;
                                }
                                if (g.sound.checkSound2())
                                {
                                    music=!music;
                                }
                                if (g.changeskin(redon))
                                {
                                    redon=!redon;
                                }
                                g.userInput.Type = game::input::NONE;
                            }
                        }
                        g.userInput.Type = game::input::NONE;
                    }
                    else
                    {
                        if (g.userInput.Type == game::input::SETTING)
                        {
                            showmenu=!showmenu;
                            g.userInput.Type = game::input::NONE;
                        }
                        g.rocket.init();
                        g.sound.musicstatus(music);
                        g.alien.init(!redon, 0.8);
                        g.alien.render(0);
                        g.renderready();
                        if(showmenu)
                        {
                            g.rendermenu();
                            g.sound.rendersound1();
                            g.sound.rendersound2();
                            if (!redon)
                            {
                                g.redxskin();
                                g.blueskin();
                            }
                            else
                            {
                                g.bluexskin();
                                g.redskin();
                            }
                            if (g.userInput.Type == game::input::PLAY)
                            {
                                if (g.sound.checkSound())
                                {
                                    issound=!issound;
                                }
                                else if (g.sound.checkSound2())
                                {
                                    music=!music;
                                }
                                else if (g.changeskin(redon))
                                {
                                    redon=!redon;
                                }
                                g.userInput.Type = game::input::NONE;
                            }

                        }
                        if (g.userInput.Type == game::input::PLAY)
                        {
                            g.Restart();
                            ready = 1;
                            g.userInput.Type = game::input::NONE;
                        }
                        g.moon.update();
                    }
                }
                g.display();
            }
            g.rocket.init();
        }
        else
        {
            g.takeInput();
            if (g.userInput.Type == game::input::PAUSE)
            {
                ispause=!ispause;
                g.userInput.Type = game::input::NONE;
            }
            if (ispause==0 && g.userInput.Type == game::input::PLAY)
            {
                if (issound) g.sound.playfly();
                g.alien.resetTime();
                g.userInput.Type=game::input::NONE;
            }
            g.renderbackground();
            g.rocket.render();
            g.moon.render();
            if (ispause==0)
            {
                frame++;
                if (frame==20)
                {
                    idx++;
                    if (idx==3) idx=0;
                    frame=0;
                }
            }
            g.alien.render(idx);
            g.renderScoreLarge();

            if (!ispause)
            {
                g.alien.update(g.getRocketWidth(),g.getRocketHeight(),0.8);
                g.rocket.update();
                g.moon.update();
                g.pause();
            }
            else
            {
                g.resume();
                g.renderpausetab();
                g.sound.rendersound1();
                g.sound.rendersound2();
                g.sound.musicstatus(music);
                g.renderScoreSmall();
                g.renderBestScore();
                g.replay();
                g.sound.rendersound1();
                if (g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        ispause=0;
                    }
                    if (g.sound.checkSound())
                    {
                        issound=!issound;
                    }
                    if (g.sound.checkSound2())
                    {
                        music=!music;
                    }
                    g.userInput.Type = game::input::NONE;
                }
            }
            g.display();
        }
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay>frameTime)
        {
            SDL_Delay(frameDelay-frameTime);
        }
    }
    return 0;
}


