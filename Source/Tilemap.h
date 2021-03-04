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
    Tilemap(int* arr, int w, int h, int size, int original_size, SDL_Texture* t)
     : arr(arr)
     , w(w)
     , h(h)
     , size(size)
     , textures(t)
     , original_size(original_size)
     { }
    void render(SDL_Renderer* renderer, SDL_Rect* camera)
    {
        SDL_Rect pos = SDL_Rect();
        pos.w = size;
        pos.h = size;
        SDL_Rect src = SDL_Rect();
        src.w = original_size;
        src.h = original_size;
        src.y = 0;
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                pos.x = i*size;
                pos.y = j*size;
                src.x = arr[j*w + i]*original_size;
                if (SDL_HasIntersection(&pos, camera) == SDL_TRUE)
                {
                    
                    pos.x = i*size - camera->x;
                    pos.y = j*size - camera->y;
                    SDL_RenderCopy(renderer, textures, &src, &pos);
                }
                
            }
        }
    }
    int w, h, size, original_size;
    int* arr;
    SDL_Texture* textures;

};