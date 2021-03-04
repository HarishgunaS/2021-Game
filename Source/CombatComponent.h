#pragma once
#include "Component.h"
#ifdef _WIN32
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL_image.h>
#endif
class CombatComponent : public Component
{
public:
	CombatComponent(int h, int a)
	{
		maxHealth = h;
		currentHealth = maxHealth;
		standardAttack = a;
	}


private:
	int maxHealth, currentHealth, standardAttack;
};