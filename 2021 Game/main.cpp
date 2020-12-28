/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
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
	texture = loadTexture("C:\\Users\\satgu\\Pictures\\bmp_24.bmp");
	if (texture == NULL)
	{
		printf("image load error %s\n", SDL_GetError());
		success = false;
	}
	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture(texture);
	texture = NULL;

	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
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
			position->x = 500;
			position->y = 400;
			position->w = 50;
			position->h = 50;
			double xVelocity = 0;
			double yVelocity = 0;
			double speed = 1;
			bool quit = false;
			SDL_Event e;
			Uint32 sumDeltaT = 0;
			Uint32 prevTime = SDL_GetTicks();
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
				position->x += xVelocity * deltaT;
				position->y += yVelocity * deltaT;
				
				


				prevTime = SDL_GetTicks();
				//rendering
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, texture, NULL, position);
				SDL_RenderPresent(renderer);

			}
		}
	}
	close();
	return 0;
}