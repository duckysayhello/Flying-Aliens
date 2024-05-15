#include "sound.h"
#include <stdio.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

bool sound::init()
{
    string fly_path = "sound/fly.mp3";
    string collide_path = "sound/collide.mp3";
    string click_path = "sound/click.mp3";
    string sound_path = "image/sound.png";
    string music_path = "sound/blueheart.mp3";


    bool success = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        fly = Mix_LoadWAV( fly_path.c_str() );
        if ( fly == NULL )
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
        click = Mix_LoadWAV( click_path.c_str() );
        if ( click == NULL )
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        collide = Mix_LoadWAV( collide_path.c_str() );
        if (collide == NULL)
        {
            printf( "Failed to load chord! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        music = Mix_LoadMUS( music_path.c_str() );
        if (music == NULL)
        {
            printf( "Failed to load chord! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        if (!Load(sound_path))
        {
            return false;
        }

        Active.x = 0; Active.y = 0; Active.w = getWidth(); Active.h = getHeight() / 2;
        Mute.x = 0; Mute.y = getHeight() / 2; Mute.w = getWidth(); Mute.h = getHeight() / 2;
        isPlay = true;
        isPlaymusic = true;
    }
    return success;
}

void sound::Free()
{
    free();

    Mix_FreeChunk(fly);
    fly = NULL;
    Mix_FreeChunk(click);
    click = NULL;
    Mix_FreeChunk(collide);
    collide = NULL;
    Mix_FreeMusic(music);
    music = NULL;
    Mix_Quit();
}

void sound::playfly()
{
    if (isPlay)
    {
        Mix_PlayChannel( -1, fly, 0 );
    }
}
void sound::playclick()
{
    if (isPlay)
    {
        Mix_PlayChannel( -1, click, 0 );
    }
}

void sound::playcollide()
{
    if (isPlay)
    {
        Mix_PlayChannel(-1, collide, 0);
    }
}
void sound::playmusic()
{
    if (isPlaymusic)
    {
        Mix_PlayMusic(music,-1);
        Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    }
}
void sound::musicstatus(bool x)
{
    if(x) Mix_ResumeMusic();
    else Mix_PauseMusic();
}

void sound::rendersound1()
{
    if (isPlay)
    {
        Render(POS_X, POS_Y, 0, &Active);
    }
    else
    {
        Render(POS_X, POS_Y, 0, &Mute);
    }
}

void sound::rendersound2()
{
    if (isPlaymusic)
    {
        Render(POS_X, POS_Y2, 0, &Active);
    }
    else
    {
        Render(POS_X, POS_Y2, 0, &Mute);
    }
}

bool sound::checkSound2() {
    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    if ((buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
        x > POS_X && x < POS_X + getWidth() &&
        y > POS_Y2 && y < POS_Y2 + getHeight()) {
        isPlaymusic = !isPlaymusic;
        return true;
    }
    return false;
}

bool sound::checkSound() {
    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    if ((buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
        x > POS_X && x < POS_X + getWidth() &&
        y > POS_Y && y < POS_Y + getHeight()) {
        isPlay = !isPlay;
        return true;
    }
    return false;
}


