#include <stdio.h>
#include <string>
//#include "Tilemap.h"
#include "Camera.h"
#include "Text.h"
#include "Entity.h"
#include "ECSManager.h"
#include "World.h"
//#include "Player.h" included in Camera.h

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif
#define ORIGINAL_SIZE 200.0
#define SIZE 100.0
const int SCREEN_WIDTH = 8*(SIZE);
const int SCREEN_HEIGHT = 8*(SIZE);
const int WORLD_WIDTH = 10*(SIZE);
const int WORLD_HEIGHT = 10*(SIZE);
bool init();
bool loadMedia();
void close();

SDL_Texture* loadTexture(std::string path);

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

SDL_Texture* texture = NULL;

TTF_Font* font = NULL;

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
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				if (TTF_Init() == -1)
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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
	font = TTF_OpenFont( "../Resources/gothic_pixel.ttf", SIZE );
    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
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

			bool quit = false;
			SDL_Event e;
			Uint32 sumDeltaT = 0;
			Uint32 prevTime = SDL_GetTicks();
			int arr[100] = {0,1,3,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
			Camera* camera = new Camera(WORLD_WIDTH, WORLD_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
			
			Tilemap* tilemap = new Tilemap(arr, 10, 10, SIZE, ORIGINAL_SIZE, texture); //(use multiple tilemaps for more depth)
			
			World* world = new World(tilemap);
			ECSManager* ecsManager = new ECSManager(world);
			
			Uint32 player = ecsManager->generateEntity();
			ecsManager->addPhysicsComponent(player, new PhysicsComponent(SCREEN_WIDTH / 2 - SIZE / 2, SCREEN_HEIGHT / 2 - SIZE / 2, 0.2 * (SIZE / 50), SIZE));
			ecsManager->addGraphicsComponent(player, new GraphicsComponent(texture));
			Uint32 enemy = ecsManager->generateEntity();
			ecsManager->addPhysicsComponent(enemy,new PhysicsComponent(120, 120, 0.2 * (SIZE / 50), SIZE));
			ecsManager->addGraphicsComponent(enemy, new GraphicsComponent(texture));
			/*Entity* enemy2 = new Entity("enemy");
			enemy2->physics = new PhysicsComponent(120, 120, 0.2 * (SIZE / 50), SIZE, WORLD_WIDTH, WORLD_HEIGHT);
			enemy2->graphics = new GraphicsComponent(texture);
			Entity* enemy3 = new Entity("enemy");
			enemy3->physics = new PhysicsComponent(120, 120, 0.2 * (SIZE / 50), SIZE, WORLD_WIDTH, WORLD_HEIGHT);
			enemy3->graphics = new GraphicsComponent(texture);
			Entity* enemy4 = new Entity("enemy");
			enemy4->physics = new PhysicsComponent(120, 120, 0.2 * (SIZE / 50), SIZE, WORLD_WIDTH, WORLD_HEIGHT);
			enemy4->graphics = new GraphicsComponent(texture);
			Entity* enemy5 = new Entity("enemy");
			enemy5->physics = new PhysicsComponent(120, 120, 0.2 * (SIZE / 50), SIZE, WORLD_WIDTH, WORLD_HEIGHT);
			enemy5->graphics = new GraphicsComponent(texture);
			Entity* enemy6 = new Entity("enemy");
			enemy6->physics = new PhysicsComponent(120, 120, 0.2 * (SIZE / 50), SIZE, WORLD_WIDTH, WORLD_HEIGHT);
			enemy6->graphics = new GraphicsComponent(texture);
			Entity* enemy7 = new Entity("enemy");
			enemy7->physics = new PhysicsComponent(120, 120, 0.2 * (SIZE / 50), SIZE, WORLD_WIDTH, WORLD_HEIGHT);
			enemy7->graphics = new GraphicsComponent(texture);*/


			 
			SDL_Color textColor = {0,0,0};
			Text* text = new Text(font, textColor);
			text->setText("Hello there", renderer);
			text->setPosition(0, SCREEN_HEIGHT - text->getRect()->h);

			while (!quit)
			{

				Uint32 deltaT = SDL_GetTicks() - prevTime;
				//Event manager
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					ecsManager->input(e);

				}
				//world logic update with delta T
				ecsManager->update(deltaT);
				text->setText(std::to_string((ecsManager->getPhysicsComponent(player))->getPosition()->x) + ", " + std::to_string((ecsManager->getPhysicsComponent(player))->getPosition()->y), renderer);

				//prevTime = SDL_GetTicks();
				
				


				//camera adjustments
				camera->update(deltaT, (ecsManager->getPhysicsComponent(player)));

				
				
				prevTime = SDL_GetTicks();

				//rendering

				//clear renderer
				SDL_RenderClear(renderer);
				//render tilemap (use multiple tilemaps for more depth)
				tilemap->render(renderer, camera->returnRect());
				//render player
				ecsManager->render(renderer, camera->returnRect());
				//render text
				text->render(renderer);
				//present frame
				SDL_RenderPresent(renderer);

			}
		}
	}
	close();
	return 0;
}
