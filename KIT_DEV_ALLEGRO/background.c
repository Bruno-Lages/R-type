#include "background.h"

#define STAR_RADIUS 1

void init_star(Star *star, int speed) {
    star->coordenates.radius = STAR_RADIUS;
    star->coordenates.x1 = rand() % SCREEN_W;
    star->coordenates.y1 = rand() % SCREEN_H;
    star->speed = speed;
}

void update_star(Star *star) {
    if(star->coordenates.x1 > -star->coordenates.radius*2) star->coordenates.x1 -= star->speed+1;
    else (star->coordenates.x1 = SCREEN_W + star->coordenates.radius*2);
}

void draw_star(Star star) {
    al_draw_filled_circle(star.coordenates.x1, star.coordenates.y1, star.coordenates.radius, al_map_rgb(250, 250, 250));
}


