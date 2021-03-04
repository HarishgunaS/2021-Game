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
	PhysicsComponent(int xPos, int yPos, double s, int size)
	{
		position = new SDL_Rect();
		position->x = xPos;
		position->y = yPos;
		position->w = size;
		position->h = size;

		collider = new SDL_Rect();
		collider->x = xPos;
		collider->y = yPos;
		collider->w = size;
		collider->h = size;

		x = xPos;
		y = yPos;
		xVelocity = 0;
		yVelocity = 0;
		speed = s;
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
	SDL_Rect* position;
	SDL_Rect* collider;
	double x, y, xVelocity, yVelocity, speed;
};