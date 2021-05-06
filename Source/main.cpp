#include <stdio.h>
#include <string>
//#include "Tilemap.h"
#include "Camera.h"
#include "Text.h"
#include "ECSManager.h"
#include "World.h"

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

#include "LuaHelper.h"

#define ORIGINAL_SIZE 200.0
#define SIZE 32.0
const int SCREEN_WIDTH = 14*(SIZE);
const int SCREEN_HEIGHT = 15*(SIZE);

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(std::string path);
SDL_Texture* loadTexture(std::string path);
Uint32 entityFromLua(LuaRef entity, ECSManager* manager);

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


bool loadMedia(lua_State* L)
{
	bool success = true;
	font = TTF_OpenFont( "../Resources/gothic_pixel.ttf", SIZE );
    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
	texture = loadTexture("../Resources/MysticChroma_Basics.png");
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

Uint32 entityFromLua(LuaRef entity, ECSManager* manager)
{
	Uint32 id;
	if (!entity["name"].isNil())
	{
		id = manager->generateEntity(entity["name"].cast<std::string>());
	}
	else
	{
		id = manager->generateEntity();
	}
	if (!entity["physics"].isNil())
	{
		LuaRef physics = entity["physics"];
		manager->addPhysicsComponent(id, new PhysicsComponent(physics["x"].cast<int>(), physics["y"].cast<int>(), physics["speed"].cast<double>(), physics["size"].cast<int>()));
	}
	if (!entity["graphics"].isNil())
	{
		LuaRef graphics = entity["graphics"];
		manager->addGraphicsComponent(id, new GraphicsComponent(loadTexture(graphics["path"].cast<std::string>())));
	}
	if (!entity["combat"].isNil())
	{
		LuaRef combat = entity["combat"];
		manager->addCombatComponent(id, new CombatComponent(combat["health"].cast<int>(), combat["attack"].cast<int>(), combat["defense"].cast<int>(), combat["cooldown"].cast<int>()));
	}
	return id;
}

int main( int argc, char* args[] )
{
	if (init())
	{
		lua_State* L = luaL_newstate();
		if (luaL_loadfile(L, "../Scripts/script.lua") || lua_pcall(L, 0, 0, 0)) {
			printf("script not loading\n");
		}
		luaL_dofile(L, "../Scripts/script.lua");
		luaL_openlibs(L);
		lua_pcall(L, 0, 0, 0);
		if (loadMedia(L))
		{
			//logic initialization
			bool quit = false;
			SDL_Event e;
			Uint32 sumDeltaT = 0;
			Uint32 prevTime = SDL_GetTicks();

			LuaRef map = getGlobal(L, "map");
			if (map.isNil())
			{
				printf("error\n");
			}
			LuaRef entities = getGlobal(L, "entities");
			LuaRef layerOne = map["layers"][1];
			Tilemap* tilemap = new Tilemap(layerOne, SIZE, map["tilewidth"].cast<int>(), texture, 6); //(use multiple tilemaps for more depth)
			World* world = new World(tilemap);

			Camera* camera = new Camera(world->WORLD_WIDTH, world->WORLD_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
			


			SDL_Color textColor = {0,0,0};
			ECSManager* ecsManager = new ECSManager(renderer, world, font, textColor);

			int numEntities = entities["count"].cast<int>();
			LuaRef entityArray = entities["array"];
			for (int i = 0; i < numEntities; i++)
			{
				LuaRef entity = entityArray[i + 1];
				entityFromLua(entity, ecsManager);
			}
			Uint32 player = ecsManager->getIDfromName("player");
			 
			
			Text* text = new Text(font, textColor);
			text->setText("Hello there", renderer);
			text->setPosition(10, 10);
			ecsManager->render(camera->returnRect());
			ecsManager->speak("hi there", -1);
			int maxFPS = 144;
			int minTime = 1000/maxFPS;

			while (!quit)
			{

				Uint32 deltaT = SDL_GetTicks() - prevTime;
				
				if (deltaT < minTime)
				{
					SDL_Delay(minTime - deltaT);
					deltaT = minTime;
				}
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
				
				//text->setText(std::to_string((ecsManager->getPhysicsComponent(player))->getPosition()->x) + ", " + std::to_string((ecsManager->getPhysicsComponent(player))->getPosition()->y), renderer);

				//prevTime = SDL_GetTicks();
				
				


				//camera adjustments
				camera->update(deltaT, (ecsManager->getPhysicsComponent(player)));

				
				
				prevTime = SDL_GetTicks();


				int fps = 1000.0/(deltaT);
				if (prevTime % 100 == 0)
				{
					text->setText(std::to_string(fps), renderer);
				}
				//rendering
				
				//clear renderer
				SDL_RenderClear(renderer);
				//render tilemap (use multiple tilemaps for more depth)
				tilemap->render(renderer, camera->returnRect());
				//render player
				ecsManager->render(camera->returnRect());
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
