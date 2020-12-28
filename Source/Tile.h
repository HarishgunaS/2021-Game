#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

class Tile
{
public:
    Tile(int t, int x, int y)
     : x(x)
     , y(y)
     , texture(t)
     { }
private:
    int texture, x, y;

};