#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#endif
#include <stdio.h>

class Player
{
public:

private:
    SDL_Rect* camera;
    SDL_Rect* innerCamera;
    double cameraX = 0.0, cameraY = 0.0;
    int WORLD_WIDTH, WORLD_HEIGHT;

};