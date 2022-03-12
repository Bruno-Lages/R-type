#ifndef GASOLINE
#define GASOLINE

#include <allegro5\allegro.h>
#include "equations.h"
#include "spaceship.h"
#include "obstacles.h"

typedef struct Power_up {
    Paralelogram rectangular_coordenates;
    Circle circular_coordenates;
    int type;
    int is_circle;
} Power_up;

#define GASOLINE_WIDTH 50
#define GASOLINE_HEIGHT 55
#define SCREWDRIVER_RADIUS 25


//configura o power up
void init_power_up(Power_up *power_up);

//atualiza o power up
void update_power_up(Power_up *power_up);

//desenha o power up
void draw_power_up(Power_up power_up, ALLEGRO_BITMAP *gasoline_sprite, ALLEGRO_BITMAP *screwdriver_sprite);


#endif