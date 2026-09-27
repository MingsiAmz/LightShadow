#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 900
#define WHITE 0xffffffff
#define BLACK 0x00000000
#define GRAY 0xFFF8DC
#define RAYS_NUMBER 4096

typedef struct{
        double x,y,radius;
} Circle;

typedef struct{
        double angle;
} Ray;

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

void cleanRect(SDL_Surface* surface) {
        SDL_Rect rect = {0,0,WIDTH,HEIGHT};
        SDL_FillRect(surface, &rect, BLACK);
}

void generatorRay(Circle circle, Ray rays[RAYS_NUMBER]) {
        const double step = 2 * M_PI / RAYS_NUMBER;
        for (int i = 0; i < RAYS_NUMBER; i++) {
                rays[i].angle = i * step;
        }
}

int isHit(double x, double y, Circle circles) {
        double dx = x - circles.x;
        double dy = y - circles.y;
        double r = circles.radius;
        if (dx * dx + dy * dy < r * r) {
                return 1;
        }
        return 0;    
}

void fillRays(SDL_Surface* surface, Ray rays[RAYS_NUMBER], uint32_t color, Circle lightCircle, Circle targetCircle) {
        double r = lightCircle.radius * lightCircle.radius;
        for (int i = 0; i < RAYS_NUMBER; i++) {
                double ca = cos(rays[i].angle);
                double sa = sin(rays[i].angle);
                double x = lightCircle.x + ca * lightCircle.radius;
                double y = lightCircle.y + sa * lightCircle.radius;
                while (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                        if (isHit(x, y, targetCircle) == 1) break;
                        SDL_Rect px = {x,y,1,1};
                        SDL_FillRect(surface, &px, GRAY);
                        x += ca;
                        y += sa;
                }
        }
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

                generatorRay(circle, rays);
                cleanRect(surface);
                fillCircle(surface, circle, WHITE);

                fillRays(surface, rays, GRAY, light, circle);
                fillCircle(surface, light, WHITE);

                SDL_UpdateWindowSurface(window);
                SDL_Delay(10);
        }
        return 0;
}

