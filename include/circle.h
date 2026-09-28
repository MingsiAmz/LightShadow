#ifndef CIRCLE
#define CIRCLE
#include <SDL2/SDL.h>

typedef struct{
        double x,y,radius;
} Circle;

void fillCircle(SDL_Surface* surface, Circle circle, uint32_t color);
#endif
