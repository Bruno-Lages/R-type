#include "power_up.h"


#define GASOLINE_WIDTH 50
#define GASOLINE_HEIGHT 55

//configura a gasolina
void init_power_up(Power_up *power_up) {
    power_up->type = rand() % 2;

    power_up->is_circle = !power_up->type;

    power_up->rectangular_coordenates.x1 = SCREEN_W + rand() % SCREEN_W;
    power_up->rectangular_coordenates.x2 = power_up->rectangular_coordenates.x1 + GASOLINE_WIDTH;
    power_up->rectangular_coordenates.y1 = GASOLINE_HEIGHT + rand() % (SCREEN_H - GASOLINE_HEIGHT);
    power_up->rectangular_coordenates.y2 = power_up->rectangular_coordenates.y1 + GASOLINE_HEIGHT;

    power_up->circular_coordenates.radius = SCREWDRIVER_RADIUS;
    power_up->circular_coordenates.x1 = power_up->rectangular_coordenates.x1 + SCREWDRIVER_RADIUS;
    power_up->circular_coordenates.y1 = power_up->rectangular_coordenates.y1 + SCREWDRIVER_RADIUS;
}

//atualiza a gasolina
void update_power_up(Power_up *power_up) {
    if(power_up->circular_coordenates.x1 > -GASOLINE_WIDTH) {
        power_up->rectangular_coordenates.x1 -= 3;
        power_up->rectangular_coordenates.x2 -= 3;
        power_up->circular_coordenates.x1 -= 3;
    } else init_power_up(power_up);
}

//desenha a gasolina
void draw_power_up(Power_up power_up, ALLEGRO_BITMAP *gasoline_sprite, ALLEGRO_BITMAP *screwdriver_sprite) {
    if(!power_up.type) al_draw_bitmap(screwdriver_sprite, power_up.rectangular_coordenates.x1, power_up.rectangular_coordenates.y1, 0);
    if(power_up.type) al_draw_bitmap(gasoline_sprite, power_up.rectangular_coordenates.x1, power_up.rectangular_coordenates.y1, 0);
}
