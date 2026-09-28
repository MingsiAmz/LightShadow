#include "./include/circle.h"
void fillCircle(SDL_Surface* surface, Circle circle, uint32_t color) {
        double radius_squared = circle.radius * circle.radius;
        for (double x = circle.x - circle.radius; x <= circle.x + circle.radius; x++) {
                for (double y = circle.y - circle.radius; y <= circle.y + circle.radius; y++) {
                        double distance_squared = (x - circle.x) * (x - circle.x) + (y - circle.y) * (y - circle.y);
                        if (distance_squared < radius_squared) {
                                SDL_Rect px = {x,y,1,1};
                                SDL_FillRect(surface, &px, color);
                        }
                }
        }
}
