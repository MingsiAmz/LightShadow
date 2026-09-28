#ifndef RAY
#define RAY

#include "circle.h"
#define RAYS_NUMBER 1024

typedef struct{
        double angle;
        uint32_t color;
} Ray;

int isHit(double x, double y, Circle circles);
void generatorRay(Circle circle, Ray rays[RAYS_NUMBER]);
void fillRays(SDL_Surface* surface, Ray rays[RAYS_NUMBER], uint32_t color, Circle lightCircle, Circle targetCircle, int height, int width);

#endif
