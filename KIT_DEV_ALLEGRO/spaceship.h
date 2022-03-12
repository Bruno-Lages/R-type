#ifndef SPACESHIP
#define SPACESHIP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "equations.h"

#define SPACESHIP_WIDTH  115
#define SPACESHIP_HEIGHT 55

//  cria uma estrutura nave
typedef struct Spaceship {
    int x_movement, y_movement;
    double x, y;
    Paralelogram border;
    double speed;
    int lifes;
    int damaged;
    int direction, heighness, multiplicator;
} Spaceship;

// configura a nave
void init_spaceship(Spaceship *spaceship);

//move a nave para cima
void move_spaceship_up(Spaceship *spaceship);

//move a nave para cima mais rápido
void move_spaceship_up_faster(Spaceship *spaceship);

//move a nave para trás
void move_spaceship_left(Spaceship *spaceship);

//move a nave para baixo
void move_spaceship_down(Spaceship *spaceship);

//move a nave para baixo mais rápido
void move_spaceship_down_faster(Spaceship *spaceship);

//move a nave para frente
void move_spaceship_right(Spaceship *spaceship);

void stabilize_spaceship(Spaceship *spaceship);

void update_spaceship(Spaceship *spaceship);


// desenha a nave
void draw_spaceship(Spaceship *spaceship, ALLEGRO_BITMAP *sprite);

//a nave recebe dano
void spaceship_damaged(Spaceship *spaceship);

#endif