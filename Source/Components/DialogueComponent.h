#pragma once

#ifdef _WIN32
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL_image.h>
#endif

typedef struct DialogueComponent
{
    SDL_Texture* face;
	DialogueComponent(SDL_Texture* f)
	{
		face = f;
	}
};