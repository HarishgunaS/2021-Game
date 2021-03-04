#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#endif
#include <stdio.h>
#include "PhysicsComponent.h"
class Camera
{
public:
    Camera(int W_WIDTH, int W_HEIGHT, int SCREEN_WIDTH, int SCREEN_HEIGHT)
    {
        WORLD_WIDTH = W_WIDTH;
        WORLD_HEIGHT = W_HEIGHT;
        camera = new SDL_Rect();
        innerCamera = new SDL_Rect();
        camera->w = SCREEN_WIDTH;
        camera->h = SCREEN_HEIGHT;
        camera->x = 0;
        camera->y = 0;
        innerCamera->w = SCREEN_WIDTH/2;
        innerCamera->h = SCREEN_HEIGHT/2;
        innerCamera->x = SCREEN_WIDTH/4;
        innerCamera->y = SCREEN_HEIGHT/4;

    }
    Camera(int W_WIDTH, int W_HEIGHT, int SCREEN_WIDTH, int SCREEN_HEIGHT, int cX, int cY)
    {
        WORLD_WIDTH = W_WIDTH;
        WORLD_HEIGHT = W_HEIGHT;
        cameraX = cX;
        cameraY = cY;
        camera = new SDL_Rect();
        innerCamera = new SDL_Rect();
        camera->w = SCREEN_WIDTH;
        camera->h = SCREEN_HEIGHT;
        camera->x = cameraX;
        camera->y = cameraY;
        innerCamera->w = SCREEN_WIDTH/2;
        innerCamera->h = SCREEN_HEIGHT/2;
        innerCamera->x = cameraX + SCREEN_WIDTH/4;
        innerCamera->y = cameraY + SCREEN_HEIGHT/4;
    }
    void update(Uint32 deltaT, PhysicsComponent* player)
    {
        
        if (player->getXVelocity() * deltaT > 0)
        {
            if (player->getPosition()->x + player->getPosition()->w > innerCamera->x + innerCamera->w)
            {
                if (cameraX + player->getXVelocity() * deltaT <= (double)(WORLD_WIDTH) -(double)(camera->w))
                {
                    cameraX += player->getXVelocity() * deltaT;
                }
                
            }
            
        }
        else if (player->getXVelocity()* deltaT < 0)
        {
            if (player->getPosition()->x < innerCamera->x)
            {
                if (cameraX + player->getXVelocity() * deltaT >= 0)
                {
                    cameraX += player->getXVelocity() * deltaT;
                }
            }
        }
        else if (player->getYVelocity()* deltaT > 0)
        {
            
            if (player->getPosition()->y + player->getPosition()->h > innerCamera->y + innerCamera->h)
            {
                if (cameraY + player->getYVelocity() * deltaT <= (double)(WORLD_HEIGHT) -(double)(camera->h))
                {
                    cameraY += player->getYVelocity() * deltaT;
                }
                
            }
        }
        else if (player->getYVelocity()* deltaT < 0)
        {
            if (player->getPosition()->y < innerCamera->y)
            {
                if (cameraY + player->getYVelocity() * deltaT >= 0)
                {
                    cameraY += player->getYVelocity() * deltaT;
                }
            }
        }
        innerCamera->x = cameraX+camera->w/4;
        innerCamera->y = cameraY+camera->h/4;
        camera->x = cameraX;
        camera->y = cameraY;
    }
    double returnX() {return cameraX;}
    double returnY() {return cameraY;}
    void incrementX(double i) {cameraX += i;}
    void incrementY(double i) {cameraY += i;}
    SDL_Rect* returnRect() {return camera;}
private:
    SDL_Rect* camera;
    SDL_Rect* innerCamera;
    double cameraX = 0.0, cameraY = 0.0;
    int WORLD_WIDTH, WORLD_HEIGHT;

};