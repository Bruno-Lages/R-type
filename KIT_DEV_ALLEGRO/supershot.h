#ifndef SUPERSHOT
#define SUPERSHOT

#include <allegro5/allegro.h>
#include "equations.h"
#include "enemies.h"
#include "obstacles.h"

//estrutura do tiro especial
typedef struct Supershot {
    Circle coordenates;
    int shooted, loading, direction;
} Supershot;

//configura o tiro especial
void init_supershot(Supershot *supershot, Spaceship spaceship);

//carrega o supertiro
void load_supershot(Supershot *supershot, Spaceship spaceship);

//recarrega o supertiro
void reload_supershot(Supershot *supershot, Spaceship spaceship);

//atualiza a posição do supertiro
void update_supershot(Supershot *supershot, Spaceship spaceship);

//desenha o supertiro
void draw_supershot(Supershot supershot, ALLEGRO_BITMAP *sprite, ALLEGRO_BITMAP *rsprite, ALLEGRO_BITMAP *loading_sprite[], int timer);

#endif