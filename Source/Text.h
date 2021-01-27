#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif
#include <stdio.h>
#include <string>

class Text
{
public:
    Text(TTF_Font* f, SDL_Color c)
    {
        font = f;
        texture = NULL;
        textPosition = new SDL_Rect();
        color = c;
    }
    void setText(std::string string, SDL_Renderer* renderer)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, string.c_str(), color);
        if (textSurface == NULL)
        {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        }
        else
        {
            //Create texture from surface pixels
            texture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (texture == NULL)
            {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                //Get image dimensions
                textPosition->w = textSurface->w;
                textPosition->h = textSurface->h;
            }

            //Get rid of old surface
            SDL_FreeSurface(textSurface);
        }
    }
    void setPosition(int x, int y)
    {
        textPosition->x = x;
        textPosition->y = y;
    }
    void render(SDL_Renderer* renderer)
    {
        SDL_RenderCopy(renderer, texture, NULL, textPosition);
    }
    SDL_Rect* getRect()
    {
        return textPosition;
    }
private:
    SDL_Texture* texture;
    TTF_Font* font;
    SDL_Color color;
    SDL_Rect* textPosition;



};