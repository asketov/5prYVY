#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;

const int WIDTH = 600, HEIGHT = 600;
const int framesPerMove = 120;



int main(int argc, char* argv[])
{
    int framesCounter = 0;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("5task_2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_Surface* win = IMG_Load("sprite1.png");
    SDL_Surface* temper = IMG_Load("sprite2.png");
    SDL_Surface* mercury = IMG_Load("sprite3.png");
    SDL_Surface* sun = IMG_Load("sprite4.png");
    SDL_Event event;
    if (!win || !temper || !mercury || !sun)
    {
        cout << "Картинка не открыта";
        return 0;
    }
    SDL_Texture* sun1 = SDL_CreateTextureFromSurface(renderer, sun);
    SDL_Texture* mercury1 = SDL_CreateTextureFromSurface(renderer, mercury);
    SDL_Texture* wind = SDL_CreateTextureFromSurface(renderer, win);
    SDL_Texture* tem = SDL_CreateTextureFromSurface(renderer, temper);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_Rect windowPosition = { 0, 0, 600, 600 };
    SDL_Rect temperuturePosition = {320,300,168,361};
    SDL_Rect mercuryPosition = {390,550,28,226};
    SDL_Rect sunPosition = {50,500,150,150};
    SDL_RenderCopy(renderer, sun1, NULL, &sunPosition);
    SDL_RenderCopy(renderer, wind, NULL, &windowPosition);
    SDL_RenderCopy(renderer, tem, NULL, &temperuturePosition);
    SDL_RenderCopy(renderer, mercury1, NULL, &mercuryPosition);
    SDL_bool done = SDL_FALSE;
    SDL_RenderPresent(renderer);
    while(!done)
    {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                  return 0;
            case SDL_KEYDOWN:
                done = SDL_TRUE;
                break;
            }
        }
    }
    bool stopSun = false;
    done = SDL_FALSE;
    while (!done) {
        SDL_Event event;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        if (framesCounter == 0) {
            if (!stopSun) 
            {
                    sunPosition.y-=6;
                    mercuryPosition.y -= 1;
                    if (sunPosition.y > 600 || sunPosition.y < 50)
                    {
                        stopSun = !stopSun;
                    }
            }
            else 
            {
                sunPosition.y+=6;
                mercuryPosition.y += 1;
                if (sunPosition.y > 600 || sunPosition.y < 50)
                {
                    stopSun = !stopSun;
                }
            }
        }
        SDL_RenderCopy(renderer, sun1, NULL, &sunPosition);
        SDL_RenderCopy(renderer, wind, NULL, &windowPosition);
        SDL_RenderCopy(renderer, tem, NULL, &temperuturePosition);
        SDL_RenderCopy(renderer, mercury1, NULL, &mercuryPosition);
        SDL_RenderPresent(renderer);
        framesCounter = (framesCounter + 1) % framesPerMove;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                done = SDL_TRUE;
                break;
            }
        }
    }
    return EXIT_SUCCESS;
    
}
