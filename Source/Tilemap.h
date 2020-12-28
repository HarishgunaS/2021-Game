#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include <stdio.h>

class Tilemap
{
public:
    Tilemap(int* arr, int w, int h, int size, SDL_Texture* t)
     : arr(arr)
     , w(w)
     , h(h)
     , size(size)
     , textures(t)
     { }
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect pos = SDL_Rect();
        pos.w = size;
        pos.h = size;
        SDL_Rect src = SDL_Rect();
        src.w = size;
        src.h = size;
        src.y = 0;
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                pos.x = i*size;
                pos.y = j*size;
                src.x = arr[j*w + i]*size;
                SDL_RenderCopy(renderer, textures, &src, &pos);
            }
        }
    }
private:
    int w, h, size;
    int* arr;
    SDL_Texture* textures;

};