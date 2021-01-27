#pragma once
#include <vector>
#include <string>
#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#endif
class Component
{
public:
	Component()
	{
		
	}
	virtual void update(Uint32 deltaT) {};
private:
};