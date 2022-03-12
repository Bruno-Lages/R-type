#ifndef SHOT
#define SHOT

#include <allegro5/allegro.h>
#include "equations.h"
#include "spaceship.h"
#include "obstacles.h"
#include "enemies.h"

#define TOTAL_SHOTS 10


// estrutura do tiro
typedef struct Shot {
    Circle coordenates;
    int shooted, direction;
} Shot;

// inicia o tiro
void init_shot(Shot *shot);

//adiciona o tiro
void draw_shot(Shot shot, ALLEGRO_BITMAP *shot_sprite, ALLEGRO_BITMAP *rshot_sprite);

// atualiza a posição do tiro
void update_shot(Shot *shot, Spaceship spaceship);

// coloca o tiro pra fora
void shoot_out(Shot *shot, Spaceship spaceship);

#endif