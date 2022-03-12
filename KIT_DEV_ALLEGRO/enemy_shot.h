#ifndef ENEMY_SHOT
#define ENEMY_SHOT

#include <allegro5/allegro_primitives.h>
#include "equations.h"
#include "spaceship.h"

typedef struct Enemy_shot {
    Circle coordenates;
    int shooted;
    double angle;
    int speed;
} Enemy_shot;

//inicia o tiro do inimigo
void init_enemy_shot(Enemy_shot *enemy_shot);

//atira o tiro do inimigo
void enemy_shoot_out(Enemy_shot *enemy_shot, Spaceship spaceship, double x1, double y1, int speed);

//atualiza o tiro do inimigo
void update_enemy_shot(Enemy_shot *enemy_shot, int is_tracker);

//desenha o tiro do inimigo
void draw_enemy_shot(Enemy_shot shot, ALLEGRO_BITMAP *sprite);

#endif
