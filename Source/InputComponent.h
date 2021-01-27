#pragma once
#include "Component.h"
#include "PhysicsComponent.h"
#ifdef _WIN32
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL_image.h>
#endif
class InputComponent : public Component
{
public:
	InputComponent(PhysicsComponent* p)
	{
		physics = p;
	}
	void update(Uint32 deltaT)
	{

	}
	void input(SDL_Event e)
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				 physics->setYVelocity(-1.0 * physics->getSpeed());
				 physics->setXVelocity(0);
				break;
			case SDLK_DOWN:
				physics->setYVelocity(physics->getSpeed());
				physics->setXVelocity(0);
				break;
			case SDLK_LEFT:
				physics->setXVelocity(-1.0 * physics->getSpeed());
				physics->setYVelocity(0);
				break;
			case SDLK_RIGHT:
				physics->setXVelocity(physics->getSpeed());
				physics->setYVelocity(0);
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
				physics->setYVelocity(0);
				break;
			case SDLK_DOWN:
				physics->setYVelocity(0);
				break;
			case SDLK_LEFT:
				physics->setXVelocity(0);
				break;
			case SDLK_RIGHT:
				physics->setXVelocity(0);
				break;
			default:
				break;
			}
		}
	}

private:
	PhysicsComponent* physics;
};