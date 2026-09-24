#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdint.h>

#define WIDTH 900
#define HEIGHT 900
#define WHITE 0xffffffff
#define BLACK 0x00000000
#define GRAY 0xFFF8DC
#define RAYS_NUMBER 1024

typedef struct{
        double x,y,radius;
} Circle;

typedef struct{
        double sX,sY,angle;
} Ray;

void fillCircle(SDL_Surface* surface, Circle circle, uint32_t color) {
        double radius_squared = pow(circle.radius, 2);
        for (double x = circle.x - circle.radius; x <= circle.x + circle.radius; x++) {
                for (double y = circle.y - circle.radius; y <= circle.y + circle.radius; y++) {
                        double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
                        if (distance_squared < radius_squared) {
                                SDL_Rect px = {x,y,1,1};
                                SDL_FillRect(surface, &px, color);
                        }
                }
        }
}

void cleanRect(SDL_Surface* surface) {
        SDL_Rect rect = {0,0,WIDTH,HEIGHT};
        SDL_FillRect(surface, &rect, BLACK);
}

void generatorRay(Circle circle, Ray rays[RAYS_NUMBER]) {
        for (int i = 0; i < RAYS_NUMBER; i++) {
                double angle = ((double)i / RAYS_NUMBER) * 2 * M_PI;
                Ray ray = {circle.x, circle.y, angle};
                rays[i] = ray;
        }
}

void fillRays(SDL_Surface* surface, Ray rays[RAYS_NUMBER], uint32_t color, Circle circle) {
        double radius_squared = pow(circle.radius, 2);
        for (int i = 0; i < RAYS_NUMBER; i++) {
                Ray ray = rays[i];
                int endScreen = 0;
                int objectHit = 0;
                int step = 1;
                double dx = ray.sX;
                double dy = ray.sY;
                while (!endScreen && !objectHit) {
                        dx += step * cos(ray.angle);
                        dy += step * sin(ray.angle);
                        SDL_Rect px = {dx,dy,1,1};
                        SDL_FillRect(surface, &px, color);

                        if (dx < 0 || dx > WIDTH) endScreen = 1;
                        if (dy < 0 || dy > HEIGHT) endScreen = 1;

                        double distance_squared = pow(dx - circle.x, 2) + pow(dy - circle.y, 2);
                        if (distance_squared < radius_squared) {
                                break;
                        }
                }
        }
}

int main(int argc, char *argv[])
{
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window* window = SDL_CreateWindow("LightShadow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_INIT_VIDEO);
        SDL_Surface* surface = SDL_GetWindowSurface(window);
        Circle circle = {210,210,100};
        Circle light = {800, 100, 200};
        
        int run = 1;
        SDL_Event event;
        Ray rays[RAYS_NUMBER];
        generatorRay(light, rays);
        while (run) {
                while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT){
                                run = 0;
                        }
                        if (event.key.keysym.sym == SDLK_q) {
                                run = 0;
                        }
                        if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                                circle.x = event.motion.x;
                                circle.y = event.motion.y;
                        }
                }
                cleanRect(surface);
                fillCircle(surface, circle, WHITE);

                fillRays(surface, rays, GRAY, circle);
                fillCircle(surface, light, WHITE);

                SDL_UpdateWindowSurface(window);
                SDL_Delay(10);
        }
        return 0;
}

