#pragma once
#include "Component.h"
#ifdef _WIN32
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL_image.h>
#endif
class PhysicsComponent : public Component
{
public:
	PhysicsComponent(int xPos, int yPos, double s, int size, int wwidth, int wheight)
	{
		position = new SDL_Rect();
		position->x = xPos;
		position->y = yPos;
		position->w = size;
		position->h = size;
		x = xPos;
		y = yPos;
		xVelocity = 0;
		yVelocity = 0;
		speed = s;
		WORLD_WIDTH = wwidth;
		WORLD_HEIGHT = wheight;
	}
	void update(Uint32 deltaT)
	{
		if (x + xVelocity * deltaT >= 0 && x + position->w + xVelocity * deltaT <= WORLD_WIDTH)
		{
			x += xVelocity * deltaT;
		}
		if (y + yVelocity * deltaT >= 0 && y + position->h + yVelocity * deltaT <= WORLD_HEIGHT)
		{
			y += yVelocity * deltaT;
		}
		position->x = x;
		position->y = y;
	}
	SDL_Rect* getPosition()
	{
		return position;
	}
	double getXVelocity()
	{
		return xVelocity;
	}
	double getYVelocity()
	{
		return yVelocity;
	}
	void setXVelocity(double n)
	{
		xVelocity = n;
	}
	void setYVelocity(double n)
	{
		yVelocity = n;
	}
	double getSpeed()
	{
		return speed;
	}
private:
	SDL_Rect* position;
	double x, y, xVelocity, yVelocity, speed;
	int WORLD_WIDTH, WORLD_HEIGHT;
};