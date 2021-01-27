#pragma once
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "InputComponent.h"

#include <vector>
#include <string>
#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#endif
class Entity
{
public:
	static int currentID;
	static void init()
	{
		currentID = 0;
	}
	Entity()
	{
		ID = currentID++;
	}
	//special version for entities with names (idk if neccessary)
	Entity(std::string n) : Entity()
	{
		name = n;
	}
	void update(Uint32 deltaT)
	{
		if (physics != NULL)
		{
			physics->update(deltaT);
		}
	}
	void render(SDL_Renderer* renderer)
	{
		if (graphics != NULL)
		{
			graphics->render(renderer, physics);
		}
	}
	//maybe component adding functions (generic single or multiple specialized???)
	//list components here (subclass, not base class)
	PhysicsComponent* physics = NULL;
	GraphicsComponent* graphics = NULL;
	InputComponent* input = NULL;
private:
	Uint32 ID;
	std::string name = "";
};