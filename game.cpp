#include "game.h"
#include "graphics.h"
#include <iostream>

void game::takeInput()
{
    while(SDL_PollEvent(&event) != 0)
    {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			clicked = true;
			x_mouse = event.motion.x; y_mouse = event.motion.y;
		} else {
			clicked = false;
		}
        if (event.type == SDL_QUIT)
        {
            userInput.Type = input::QUIT;
        }
        else if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q && event.key.repeat == 0)
        {
            userInput.Type = input::SETTING;
        }
        else if ( event.type == SDL_MOUSEBUTTONDOWN || (event.type == SDL_KEYDOWN &&
		(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && event.key.repeat == 0) )
        {
            userInput.Type = input::PLAY;
        }
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p && event.key.repeat == 0)
		{
			userInput.Type = input::PAUSE;
		}
    }
}

game::game()
{
    initGraphic();
    rocket.init();
    moon.init();
    sound.init();
}

game::~game()
{
    alien.Free();
    rocket.Free();
    moon.Free();
    sound.Free();
    free();
    releaseGraphic();
}

void game::releaseGraphic()
{
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool game::initGraphic()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Flying Aliens", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void game::display()
{
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer);
}

void game::renderScoreSmall()
{
	string s = to_string(score);
	signed char len = s.length();
	graphics image;

	for (signed char i = len - 1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("image/num/1.png", 0.45);
		}
		else if (number == 2)
		{
			image.Load("image/num/2.png", 0.45);
		}
		else if (number == 3)
		{
			image.Load("image/num/3.png", 0.45);
		}
		else if (number == 4)
		{
			image.Load("image/num/4.png", 0.45);
		}
		else if (number == 5)
		{
			image.Load("image/num/5.png", 0.45);
		}
		else if (number == 6)
		{
			image.Load("image/num/6.png", 0.45);
		}
		else if (number == 7)
		{
			image.Load("image/num/7.png", 0.45);
		}
		else if (number == 8)
		{
			image.Load("image/num/8.png", 0.45);
		}
		else if (number == 9)
		{
			image.Load("image/num/9.png", 0.45);
		}
		else
		{
			image.Load("image/num/0.png", 0.45);
		}
		image.Render(245 - image.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1), 262);
	}
	image.free();
}

void game::renderScoreLarge()
{
    string s = to_string(score);
	signed char len = s.length();
	graphics image;

	for (signed char i = 0; i < len; i++)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("image/num/1.png", 1);
		}
		else if (number == 2)
		{
			image.Load("image/num/2.png", 1);
		}
		else if (number == 3)
		{
			image.Load("image/num/3.png", 1);
		}
		else if (number == 4)
		{
			image.Load("image/num/4.png", 1);
		}
		else if (number == 5)
		{
			image.Load("image/num/5.png", 1);
		}
		else if (number == 6)
		{
			image.Load("image/num/6.png", 1);
		}
		else if (number == 7)
		{
			image.Load("image/num/7.png", 1);
		}
		else if (number == 8)
		{
			image.Load("image/num/8.png", 1);
		}
		else if (number == 9)
		{
			image.Load("image/num/9.png", 1);
		}
		else
		{
			image.Load("image/num/0.png", 1);
		}
		image.Render((SCREEN_WIDTH - (image.getWidth() * len + (len - 1) * 10)) / 2 + (i + 30) * i, 100);
	}
	image.free();
}

void game::renderBestScore()
{
	ifstream fileIn("data/best.txt");
	fileIn >> bestScore;
	ofstream fileOut("data/best.txt", ios::trunc);

	if (score > bestScore)
	{
		bestScore = score;
	}
	string s = to_string(bestScore);
	signed char len = s.length();
	graphics image;

	for (signed char i = len-1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("image/num/1.png", 0.45);
		}
		else if (number == 2)
		{
			image.Load("image/num/2.png", 0.45);
		}
		else if (number == 3)
		{
			image.Load("image/num/3.png", 0.45);
		}
		else if (number == 4)
		{
			image.Load("image/num/4.png", 0.45);
		}
		else if (number == 5)
		{
			image.Load("image/num/5.png", 0.45);
		}
		else if (number == 6)
		{
			image.Load("image/num/6.png", 0.45);
		}
		else if (number == 7)
		{
			image.Load("image/num/7.png", 0.45);
		}
		else if (number == 8)
		{
			image.Load("image/num/8.png", 0.45);
		}
		else if (number == 9)
		{
			image.Load("image/num/9.png", 0.45);
		}
		else
		{
			image.Load("image/num/0.png", 0.45);
		}
		image.Render(245 - image.getWidth()*(len-i-1)*0.75 - 5*(len - i - 1), 315);
	}
	image.free();

	fileOut << bestScore;
	fileIn.close();
	fileOut.close();
}

void game::renderready()
{
	graphics image;
	image.Load("image/ready.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
	image.free();
}

void game::rendermenubackground()
{
    graphics image;
    image.Load("image/background.png");
    image.Render(0,0);
    image.free();
}

bool IsWithinBounds(bool clicked, int x, int y, int x_button, int y_button, int w_button, int h_button)
{
  if (clicked == false) return false;

  if (x < x_button) return false;

  if (x > x_button + w_button) return false;

  if (y < y_button) return false;

  if (y > y_button + h_button) return false;

  return true;
}

bool game::play()
{
    graphics image;
    image.Load("image/play.png");
	int x = 125;
	int y = 240;
	int w = image.getWidth();
	int h = image.getHeight();
    image.Render(x,y);
    image.free();
	return IsWithinBounds(clicked, x_mouse, y_mouse, x, y, w, h);
}

bool game::out()
{
    graphics image;
    image.Load("image/out.png",0.9);
	int x = 283;
	int y = 195;
	int w = image.getWidth();
	int h = image.getHeight();
    image.Render(x,y);
    image.free();
	return IsWithinBounds(clicked, x_mouse, y_mouse, x, y, w, h);
}

bool game::rendertutorbutton()
{
    graphics image;
    image.Load("image/question.png");
	int x = 10;
	int y = 440;
	int w = image.getWidth();
	int h = image.getHeight();
    image.Render(x,y);
    image.free();
	return IsWithinBounds(clicked, x_mouse, y_mouse, x, y, w, h);
}

void game::rendertutortab()
{
	graphics image;
	image.Load("image/tut.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 210);
	image.free();
}

void game::resume()
{
	graphics image;
	image.Load("image/resume.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void game::pause()
{
	graphics image;
	image.Load("image/pause.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void game::renderpausetab()
{
	graphics image;
	image.Load("image/pausetab.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 225);
	image.free();
}

bool game::options()
{
    graphics image;
    image.Load("image/options.png");
    int x = 125;
	int y = 305;
	int w = image.getWidth();
	int h = image.getHeight();
    image.Render(x,y);
    image.free();
	return IsWithinBounds(clicked, x_mouse, y_mouse, x, y, w, h);
}

bool game::quit()
{
    graphics image;
    image.Load("image/quit.png");
    int x = 125;
	int y = 370;
	int w = image.getWidth();
	int h = image.getHeight();
    image.Render(x,y);
    image.free();
	return IsWithinBounds(clicked, x_mouse, y_mouse, x, y, w, h);
}

void game::renderbackground()
{
	graphics image;
	image.Load("image/back.png", 1);
	image.Render(0, 0);
	image.free();
}

void game::rendermoon()
{
	graphics image;
	image.Load("image/moon.png", 1);
	image.Render(0, 470);
	image.free();
}

bool game::rendertomenu()
{
    graphics image;
	image.Load("image/tomenu.png", 1);
	int x = (SCREEN_WIDTH - image.getWidth()) / 2;
	int y = 450;
	int w = image.getWidth();
	int h = image.getHeight();
	image.Render(x,y);
	image.free();
	return IsWithinBounds(clicked, x_mouse, y_mouse, x, y, w, h);
}

void game::rendermenu()
{
	graphics image;
	image.Load("image/menu.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 210);
	image.free();
}

void game::redskin()
{
	graphics image;
	image.Load("image/cat/red1.png", 0.8);
	image.Render(205, 266);
	image.free();
}

void game::redxskin()
{
	graphics image;
	image.Load("image/cat/redx.png", 0.8);
	image.Render(205, 266);
	image.free();
}

void game::blueskin()
{
	graphics image;
	image.Load("image/cat/blue1.png", 0.8);
	image.Render(255, 270);
	image.free();
}

void game::bluexskin()
{
	graphics image;
	image.Load("image/cat/bluex.png", 0.8);
	image.Render(255, 270);
	image.free();
}

bool game::changeskin(bool k)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if ((!k) && (x > 205 && x < 245) && (y > 266 && y < 306))
    {
        //cout<<"Redon"<<endl;
        return true;
    }
	else if ((k) && (x > 255 && x < 295) && (y > 266 && y < 306))
    {
        //cout<<"Redon"<<endl;
        return true;
    }
    else return false;
}

void game::rendergameover()
{
	graphics image;
	image.Load("image/gameover.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 150);
	image.free();
}

void game::rendertrophy()
{
	graphics image;

	if (score >= 20 && score <= 50)
	{
		image.Load("image/trophy/silver.png", 0.5);
	}
	else if (score > 50)
	{
		image.Load("image/trophy/gold.png", 0.5);
	}
	else
	{
		image.Load("image/trophy/bronze.png", 0.5);
	}
	image.Render(100, 275);

	image.free();
}

void game::replay()
{
	graphics image;
	image.Load("image/replay.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 380);
	image.free();
}

bool game::checkReplay()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - 100)/2 && x < (SCREEN_WIDTH + 100) / 2 && y > 380 && y < 380 + 60) //cai nut
	{
		return true;
	}
	return false;
}

void game::Restart()
{
    die = false;
    score = 0;
    alien.resetTime();
}
