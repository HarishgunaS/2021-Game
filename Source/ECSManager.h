#pragma once
#include <unordered_map>
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include <string>
#include "World.h"
#include <iostream>
#include <stdio.h>
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
	void setInputControlled(Uint32 id)
	{
		inputControlled = id;
	}
	Uint32 generateEntity()
	{
		return currentID++;
	}
	void addGraphicsComponent(Uint32 id, GraphicsComponent* graphics)
	{
		graphicsComponents[id] = graphics;
	}
	void addPhysicsComponent(Uint32 id, PhysicsComponent* physics)
	{
		physicsComponents[id] = physics;
	}
	void printCollisionBuckets()
	{
		for (int i = 0; i < world->w; i++)
		{
			for (int j = 0; j < world->h; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					Uint32 id = world->collisionBuckets[i][j][k];
					if (id != -1)
					{
						std::cout << id << " " << i << " " << j << " " << k << std::endl;
					}
				}
			}
		}
	}
	void update(Uint32 deltaT)
	{
		for (const auto& pair : physicsComponents)
		{
			
			PhysicsComponent* physics = pair.second;
			//make more robust obviously


			//grid bucket to check around
			int previousBucketX = (physics->collider->x + physics->collider->w / 2) / world->size;
			int previousBucketY = (physics->collider->y + physics->collider->h / 2) / world->size;

			//move temp x y if within borders
			if (physics->x + physics->xVelocity * deltaT >= 0 && physics->x + physics->position->w + physics->xVelocity * deltaT <= world->WORLD_WIDTH)
			{
				physics->x += physics->xVelocity * deltaT;
			}
			if (physics->y + physics->yVelocity * deltaT >= 0 && physics->y + physics->position->h + physics->yVelocity * deltaT <= world->WORLD_HEIGHT)
			{
				physics->y += physics->yVelocity * deltaT;
			}

			//new collider of future position
			SDL_Rect* newCollider = new SDL_Rect();
			newCollider->w = physics->collider->w;
			newCollider->h = physics->collider->h;
			newCollider->x = physics->x;
			newCollider->y = physics->y;

			bool collisionOccurred = false;
			for (int i = previousBucketX - 2; i < previousBucketX + 2; i++)
			{
				if (i < 0 || i >= world->w)
				{
					continue;
				}
				for (int j = previousBucketY - 2; j < previousBucketY + 2; j++)
				{
					if (j < 0 || j >= world->h)
					{
						continue;
					}
					for (int k = 0; k < 2; k++)
					{
						//std::cout << i << " " << j << " " << k << std::endl;
						Uint32 id = world->collisionBuckets[i][j][k];
						if (id != pair.first && id != -1)
						{
							//check collisions
							collisionOccurred = collisionOccurred || (SDL_HasIntersection(newCollider, physicsComponents[id]->collider));
						}
					}
				}
			}
			delete newCollider;
			newCollider = NULL;
			if (!collisionOccurred)
			{
				physics->position->x = physics->x;
				physics->position->y = physics->y;
				physics->collider->x = physics->x;
				physics->collider->y = physics->y;

				int x = (physics->collider->x + physics->collider->w / 2) / world->size;
				int y = (physics->collider->y + physics->collider->h / 2) / world->size;

				if (world->collisionBuckets[previousBucketX][previousBucketY][0] == pair.first)
				{
					world->collisionBuckets[previousBucketX][previousBucketY][0] = -1;
				}
				else if (world->collisionBuckets[previousBucketX][previousBucketY][1] == pair.first)
				{
					world->collisionBuckets[previousBucketX][previousBucketY][1] = -1;
				}
				else
				{
					//PRINT ERROR!
				}

				if (world->collisionBuckets[x][y][0] == -1)
				{
					world->collisionBuckets[x][y][0] = pair.first;
				}
				else if (world->collisionBuckets[x][y][1] == -1)
				{
					world->collisionBuckets[x][y][1] = pair.first;
				}
				else
				{
					//PRINT ERROR!
				}
			}
			else
			{
				physics->x = physics->position->x;
				physics->y = physics->position->y;
			}
			
			
		}
	}
	void render(SDL_Renderer* renderer, SDL_Rect* camera)
	{
		for (const auto& pair : graphicsComponents)
		{
			GraphicsComponent* graphics = pair.second;
			//make more robust obviously
			if (physicsComponents[pair.first] != NULL)
			{
				PhysicsComponent* physics = physicsComponents[pair.first];
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
		PhysicsComponent* physics = physicsComponents[inputControlled];
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				physics->setYVelocity(-1.0 * physics->getSpeed());
				//physics->setXVelocity(0);
				break;
			case SDLK_DOWN:
				physics->setYVelocity(physics->getSpeed());
				//physics->setXVelocity(0);
				break;
			case SDLK_LEFT:
				physics->setXVelocity(-1.0 * physics->getSpeed());
				//physics->setYVelocity(0);
				break;
			case SDLK_RIGHT:
				physics->setXVelocity(physics->getSpeed());
				//physics->setYVelocity(0);
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
	PhysicsComponent* getPhysicsComponent(Uint32 id)
	{
		return physicsComponents[id];
	}
private:
	World* world;
	Uint32 currentID = 0;
	Uint32 inputControlled = 0;
	std::unordered_map<Uint32, PhysicsComponent*> physicsComponents;
	std::unordered_map<Uint32, GraphicsComponent*> graphicsComponents;
};