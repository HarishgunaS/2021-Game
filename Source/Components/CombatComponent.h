#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL_image.h>
#endif
typedef struct CombatComponent
{
	int maxHealth, currentHealth, standardAttack, standardDefense;
	Uint32 cooldown, lastAttacked = 0;
	CombatComponent(int h, int a, int d, Uint32 c)
	{
		maxHealth = h;
		currentHealth = maxHealth;
		standardAttack = a;
		standardDefense = d;
		cooldown = c;
	}
} CombatComponent;