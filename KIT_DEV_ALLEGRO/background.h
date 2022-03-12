#ifndef BACKGROUND
#define BACKGROUND

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "equations.h"

#define TOTAL_STARS 80

typedef struct Star {
    Circle coordenates;
    int speed;
} Star;

void init_star(Star *star, int speed);

void update_star(Star *star);

void draw_star(Star star);

#endif