#include <SDL2/SDL.h>
#include "include/circle.h"
#include "include/ray.h"

#define WIDTH 900
#define HEIGHT 900
#define WHITE 0xffffffff
#define BLACK 0x00000000
#define GRAY 0xFFF8DC

void cleanRect(SDL_Surface* surface) {
        SDL_Rect rect = {0,0,WIDTH,HEIGHT};
        SDL_FillRect(surface, &rect, BLACK);
}

int main(int argc, char *argv[])
{
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window* window = SDL_CreateWindow("LightShadow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_INIT_VIDEO);
        SDL_Surface* surface = SDL_GetWindowSurface(window);

        Ray rays[RAYS_NUMBER];
        Circle circle = {210,210,100};
        Circle light = {800, 100, 200};
        
        int run = 1;
        SDL_Event event;

        while (run) {
                cleanRect(surface);
                while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT){
                                run = 0;
                        }
                        if (event.key.keysym.sym == SDLK_q) {
                                run = 0;
                        }
                        if ((event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) && event.motion.state != 0) {
                                double ox = event.motion.x;
                                double oy = event.motion.y;
                                if (isHit(ox, oy, circle)) {
                                        circle.x = ox;
                                        circle.y = oy;
                                }
                                if (isHit(ox, oy, light)) {
                                        light.x = ox;
                                        light.y = oy;
                                }
                        }
                }

                generatorRay(circle, rays);
                fillCircle(surface, circle, WHITE);

                fillRays(surface, rays, GRAY, light, circle, WIDTH, HEIGHT);
                fillCircle(surface, light, WHITE);

                SDL_UpdateWindowSurface(window);
                SDL_Delay(10);
        }
        return 0;
}

