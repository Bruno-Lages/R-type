#ifndef OBSTACLES
#define OBSTACLES

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "equations.h"
#include "spaceship.h"

#define WALL_UNITY 33

#define TOTAL_FLOOR_SPLITS 7
#define FLOOR_WIDTH 189
#define FLOOR_HEIGHT 72

// cria a estrutura da parede
typedef struct Obstacle {
    Paralelogram coordenates;
    double width, height;
} Obstacle;

// configura a parede
void init_wall(Obstacle *wall);

// atualiza parede
void update_wall(Obstacle *wall);

// desenha a parede
void draw_wall(Obstacle wall, ALLEGRO_BITMAP *sprite);

// configura o chão
void init_floor(Obstacle floor[]);

// atualiza o chão
void update_floor(Obstacle floor[]);

// desenha o chão
void draw_floor(Obstacle floor[], ALLEGRO_BITMAP *sprite);


#endif