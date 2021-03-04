#pragma once
#include <vector>
#include <string>
#include "Tilemap.h"
#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#endif
class World
{
public:
	World(Tilemap* t)
	{
		tilemap = t;
		WORLD_HEIGHT = tilemap->h * tilemap->size;
		WORLD_WIDTH = tilemap->w * tilemap->size;
	}
	int WORLD_HEIGHT, WORLD_WIDTH;
	Tilemap* tilemap;
};