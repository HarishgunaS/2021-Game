#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include <stdio.h>

#include "LuaHelper.h"

class Tilemap
{
public:
    Tilemap(LuaRef luaLayer, int s, int original_s, SDL_Texture* t, int col)
    {
        columns = col;
        size = s;
        original_size = original_s;
        w = luaLayer["width"].cast<int>();
        h = luaLayer["height"].cast<int>();
        arr = getLuaArray<int>(luaLayer["data"], w*h);
        textures = t;

    }
    SDL_Rect getTileRect(int i)
    {
        int row = i / columns;
        int column = i - row * columns;
        SDL_Rect src = SDL_Rect();
        src.w = original_size;
        src.h = original_size;
        src.x = column * original_size;
        src.y = row * original_size;
        return src;
    }
    void render(SDL_Renderer* renderer, SDL_Rect* camera)
    {
        SDL_Rect pos = SDL_Rect();
        pos.w = size;
        pos.h = size;
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                pos.x = i*size;
                pos.y = j*size;
                SDL_Rect src = getTileRect(arr[j*w + i] - 1);
                if (SDL_HasIntersection(&pos, camera) == SDL_TRUE)
                {
                    
                    pos.x = i*size - camera->x;
                    pos.y = j*size - camera->y;
                    SDL_RenderCopy(renderer, textures, &src, &pos);
                }
                
            }
        }
    }
    ~Tilemap()
    {
        delete arr;
        arr = NULL;
    }
    int w, h, size, original_size;
    int* arr;
    int columns;
    SDL_Texture* textures;

};