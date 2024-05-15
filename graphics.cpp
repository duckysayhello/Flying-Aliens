#include "game.h"
#include <iostream>

bool graphics::quit = false;
bool graphics::die = true;
short int graphics::score = 0;
SDL_Window* graphics::gWindow = NULL;
SDL_Renderer* graphics::gRenderer = NULL;
SDL_Event graphics::event;

graphics::graphics()
{
	Texture = NULL;
}

short int graphics::getWidth()
{
	return tWidth;
}

short int graphics::getHeight()
{
	return tHeight;
}

void graphics::free()
{
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture );
		Texture = NULL;
		tWidth = 0;
		tHeight = 0;
	}
}

void graphics::Render(short int x, short int y, short int angle, SDL_Rect* clip, SDL_RendererFlip flip)
{
	SDL_Rect Rec_Render = { x, y, tWidth, tHeight };

    if( clip != NULL )
	{
		Rec_Render.w = clip->w ;
		Rec_Render.h = clip->h ;
	}

    SDL_RenderCopyEx( gRenderer, Texture, clip, &Rec_Render, angle, NULL, flip );
}

bool graphics::Load(string path, double scale)
{
	free();

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x00, 0xFF, 0xFF ) );

        Texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( Texture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			tWidth = (loadedSurface->w) * scale;
			tHeight = (loadedSurface->h) * scale;
		}

		SDL_FreeSurface( loadedSurface );
	}
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return Texture != NULL;

}

bool graphics
::isNULL()
{
    if (Texture == NULL) return true;
    return false;
}

void position::getPos(const short int x, const short int y)
{
    this->x = x;
    this->y = y;
}

