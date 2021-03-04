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
		w = tilemap->w;
		h = tilemap->h;
		size = tilemap->size;
		collisionBuckets = new Uint32**[w];
		for (int i = 0; i < w; i++)
		{
			collisionBuckets[i] = new Uint32*[h];
			for (int j = 0; j < h; j++)
			{
				collisionBuckets[i][j] = new Uint32[2];
				for (int k = 0; k < 2; k++)
				{
					collisionBuckets[i][j][k] = -1;
				}
			}
		}
	}
	int WORLD_HEIGHT, WORLD_WIDTH, w, h, size;
	Tilemap* tilemap;
	Uint32*** collisionBuckets;
};