#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include <stdio.h>

class Player
{
public:
	Player(SDL_Texture* t, int xPos, int yPos, double s, int size)
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
		texture = t;
	}
	void render(SDL_Renderer* renderer)
	{
		SDL_RenderCopy(renderer, texture, NULL, position);
	}
	void input(SDL_Event e)
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				yVelocity = -1.0 * speed;
				xVelocity = 0;
				break;
			case SDLK_DOWN:
				yVelocity = speed;
				xVelocity = 0;
				break;
			case SDLK_LEFT:
				xVelocity = -1.0 * speed;
				yVelocity = 0;
				break;
			case SDLK_RIGHT:
				xVelocity = speed;
				yVelocity = 0;
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
				yVelocity = 0;
				break;
			case SDLK_DOWN:
				yVelocity = 0;
				break;
			case SDLK_LEFT:
				xVelocity = 0;
				break;
			case SDLK_RIGHT:
				xVelocity = 0;
				break;
			default:
				break;
			}
		}
	}
	void update(Uint32 deltaT, int WORLD_WIDTH, int WORLD_HEIGHT)
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
private:
	SDL_Texture* texture;
	SDL_Rect* position;
	double x, y, xVelocity, yVelocity, speed;

};