#include <stdio.h>
#include <string>
#include "Tilemap.h"

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(std::string path);

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

SDL_Texture* texture = NULL;

SDL_Rect* position = new SDL_Rect();

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("couldnt initialize %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("2021 Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}



bool loadMedia()
{
	bool success = true;
	texture = loadTexture("../Resources/bmp_24.bmp");
	if (texture == NULL)
	{
		printf("image load error %s\n", SDL_GetError());
		success = false;
	}
	return success;
}

void close()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
 
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
int main( int argc, char* args[] )
{
	if (init())
	{
		if (loadMedia())
		{
			//logic initialization
			
			double x = 500;
			double y = 400;
			double xVelocity = 0;
			double yVelocity = 0;
			double speed = 0.2;
			bool quit = false;
			SDL_Event e;
			Uint32 sumDeltaT = 0;
			Uint32 prevTime = SDL_GetTicks();
			position->x = x;
			position->y = y;
			position->w = 50;
			position->h = 50;
			int arr[100] = {0,1,3,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


			Tilemap* tilemap = new Tilemap(arr, 10, 10, 50, texture);
			
			while (!quit)
			{


				//Event manager
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							yVelocity = -1.0*speed;
							break;
						case SDLK_DOWN:
							yVelocity = speed;
							break;
						case SDLK_LEFT:
							xVelocity = -1.0*speed;
							break;
						case SDLK_RIGHT:
							xVelocity = speed;
							break;
						default:
							break;
						}
					}
					else if (e.type == SDL_KEYUP)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							yVelocity = 0;
							break;
						case SDLK_DOWN:
							yVelocity = 0;
							break;
						case SDLK_LEFT:
							xVelocity = 0;
							break;
						case SDLK_RIGHT:
							xVelocity = 0;
							break;
						default:
							break;
						}
					}

				}
				//world logic update with delta T
				double deltaT = SDL_GetTicks() - prevTime;
				x += xVelocity * deltaT;
				y += yVelocity * deltaT;
				position->x = x;
				position->y = y;
				


				prevTime = SDL_GetTicks();
				//rendering
				SDL_RenderClear(renderer);
				tilemap->render(renderer);
				SDL_RenderCopy(renderer, texture, NULL, position);
				SDL_RenderPresent(renderer);

			}
		}
	}
	close();
	return 0;
}
