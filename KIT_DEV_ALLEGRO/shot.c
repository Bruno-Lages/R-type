#include "shot.h"

// inicia o tiro
void init_shot(Shot *shot) {
    shot->coordenates.x1 = 0;
    shot->coordenates.y1 = 0;
    shot->coordenates.radius = 5;
    shot->shooted = 0;
}

//adiciona o tiro
void draw_shot(Shot shot, ALLEGRO_BITMAP *shot_sprite, ALLEGRO_BITMAP *rshot_sprite) {
    if(shot.direction > 0) {
        al_draw_bitmap(shot_sprite, shot.coordenates.x1 - 34 + shot.coordenates.radius, shot.coordenates.y1 - shot.coordenates.radius, 0);
    } else {
        al_draw_bitmap(rshot_sprite, shot.coordenates.x1 - shot.coordenates.radius, shot.coordenates.y1 - shot.coordenates.radius, 0);
    }
}

// atualiza a posição do tiro
void update_shot(Shot *shot, Spaceship spaceship) {
    if(shot->coordenates.x1 <= SCREEN_W && shot->coordenates.x1 >= 0) {
        shot->coordenates.x1 += spaceship.speed * 3 * shot->direction;
    } else {
        shot->shooted = 0;
    }
}

// coloca o tiro pra fora
void shoot_out(Shot *shot, Spaceship spaceship) {
    shot->coordenates.x1 = spaceship.x;
    shot->coordenates.y1 = spaceship.y;
    shot->shooted = 1;
    shot->direction = -spaceship.multiplicator;
}

