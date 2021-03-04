#pragma once
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "CombatComponent.h"

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
	
	Entity(int n)
	{
		ID = n;
	}
	//maybe component adding functions (generic single or multiple specialized???)
	//list components here (subclass, not base class)
	PhysicsComponent* physics = NULL;
	GraphicsComponent* graphics = NULL;
	CombatComponent* combat = NULL;
private:
	Uint32 ID;
};