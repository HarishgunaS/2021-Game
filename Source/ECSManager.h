#pragma once
#include <vector>
#include <string>
#include "Entity.h"
#include "World.h"
#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#endif
class ECSManager
{
public:
	ECSManager(World* w)
	{
		loadWorld(w);
	}
	void loadWorld(World* w)
	{
		world = w;
	}
	void setInputControlled(Entity* e)
	{
		inputControlled = e;
	}
	Entity* generateEntity()
	{
		Entity* e = new Entity(currentID++);
		if (currentID == 1)
		{
			setInputControlled(e);
		}
		entities.push_back(e);
		return e;
	}
	void update(Uint32 deltaT)
	{
		for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			Entity* e = *it;
			//make more robust obviously
			if (e->physics != NULL)
			{
				PhysicsComponent* physics = e->physics;
				if (physics->x + physics->xVelocity * deltaT >= 0 && physics->x + physics->position->w + physics->xVelocity * deltaT <= world->WORLD_WIDTH)
				{
					physics->x += physics->xVelocity * deltaT;
				}
				if (physics->y + physics->yVelocity * deltaT >= 0 && physics->y + physics->position->h + physics->yVelocity * deltaT <= world->WORLD_HEIGHT)
				{
					physics->y += physics->yVelocity * deltaT;
				}
				physics->position->x = physics->x;
				physics->position->y = physics->y;

			}

		}
	}
	void render(SDL_Renderer* renderer, SDL_Rect* camera)
	{
		for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			Entity* e = *it;
			//make more robust obviously
			if (e->graphics != NULL && e->physics != NULL)
			{
				PhysicsComponent* physics = e->physics;
				GraphicsComponent* graphics = e->graphics;
				if (SDL_HasIntersection(physics->getPosition(), camera) == SDL_TRUE)
				{

					physics->getPosition()->x = physics->getPosition()->x - camera->x;
					physics->getPosition()->y = physics->getPosition()->y - camera->y;
					SDL_RenderCopy(renderer, graphics->texture, NULL, physics->getPosition());
				}
			}
		}
	}
	void input(SDL_Event e)
	{
		PhysicsComponent* physics = inputControlled->physics;
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
	World* world;
	int currentID = 0;
	std::vector<Entity*> entities;
	Entity* inputControlled = NULL;

};