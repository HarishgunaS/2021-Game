#pragma once
#include "Component.h"
#include "PhysicsComponent.h"
#ifdef _WIN32
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL_image.h>
#endif
class GraphicsComponent : public Component
{
public:
	GraphicsComponent(SDL_Texture* t)
	{
		texture = t;
	}
	SDL_Texture* texture = NULL;
};