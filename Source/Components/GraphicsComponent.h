#pragma once

#ifdef _WIN32
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL_image.h>
#endif
typedef struct GraphicsComponent
{
	SDL_Texture* texture = NULL;
	GraphicsComponent(SDL_Texture* t)
	{
		texture = t;
	}
} GraphicsComponent;