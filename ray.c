#include <SDL2/SDL.h>
#include <math.h>
#include "include/ray.h"

int isHit(double x, double y, Circle circles) {
        double dx = x - circles.x;
        double dy = y - circles.y;
        double r = circles.radius;
        if (dx * dx + dy * dy < r * r) {
                return 1;
        }
        return 0;    
}

void generatorRay(Circle circle, Ray rays[RAYS_NUMBER]) {
        double step = 2 * M_PI / RAYS_NUMBER;
        for (int i = 0; i < RAYS_NUMBER; i++) {
                rays[i].angle = i * step;
        }
}

void fillRays(SDL_Surface* surface, Ray rays[RAYS_NUMBER], uint32_t color, Circle lightCircle, Circle targetCircle, int height, int width) {
        double r = lightCircle.radius * lightCircle.radius;
        for (int i = 0; i < RAYS_NUMBER; i++) {
                double t = SDL_GetTicks() / 1000.0;
                rays[i].angle += t * 0.3;

                double ca = cos(rays[i].angle);
                double sa = sin(rays[i].angle);
                double x = lightCircle.x + ca * lightCircle.radius;
                double y = lightCircle.y + sa * lightCircle.radius;
                
                double step = 0;
                while (x >= 0 && x < width && y >= 0 && y < height) {
                        if (isHit(x, y, targetCircle) == 1) break;
                        double fade = 1 - step / width;
                        uint8_t v = 255 * fade;
                        uint32_t color = SDL_MapRGB(surface -> format, v, v, v);
                        SDL_Rect px = {x,y,1,1};
                        SDL_FillRect(surface, &px, color);
                        x += ca;
                        y += sa;
                        step++;
                }
        }
}

