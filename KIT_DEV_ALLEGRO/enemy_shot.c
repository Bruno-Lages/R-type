#include "enemy_shot.h"

//inicia o tiro do inimigo
void init_enemy_shot(Enemy_shot *enemy_shot) {
    enemy_shot->coordenates.x1 = 0;
    enemy_shot->coordenates.y1 = 0;
    enemy_shot->coordenates.radius = 8;
    enemy_shot->shooted = 0;
}

//inicia o tiro do inimigo
void enemy_shoot_out(Enemy_shot *enemy_shot, Spaceship spaceship, double x1, double y1, int speed) {
    enemy_shot->coordenates.x1 = x1 - enemy_shot->coordenates.radius;
    enemy_shot->coordenates.y1 = y1;
    enemy_shot->shooted = 1;
    enemy_shot->angle = angle(x1, y1, spaceship.x, spaceship.y);
    enemy_shot->speed = speed;
}

//atualiza o tiro do inimigo
void update_enemy_shot(Enemy_shot *enemy_shot, int is_tracker) {
    if(enemy_shot->coordenates.x1 - enemy_shot->coordenates.radius <= SCREEN_W && enemy_shot->coordenates.x1 + enemy_shot->coordenates.radius >= 0 && enemy_shot->shooted) {
        if(is_tracker)enemy_shot->coordenates.x1 -= 2 * enemy_shot->speed * cos(enemy_shot->angle);
        if(!is_tracker)enemy_shot->coordenates.x1 -= 2 * enemy_shot->speed;
        enemy_shot->coordenates.y1 -= 2 * enemy_shot->speed * sin(enemy_shot->angle);
    } else {
        enemy_shot->shooted = 0;
    }
}

//desenha o tiro do inimigo
void draw_enemy_shot(Enemy_shot shot, ALLEGRO_BITMAP *sprite) {
    if(shot.coordenates.x1 > 1.2*SCREEN_W || !shot.shooted) return;
    int animation = time(NULL) % 7;
    if(shot.shooted) al_draw_bitmap_region(sprite, 1 + 16*animation, 0, 16, 16, shot.coordenates.x1 - shot.coordenates.radius, shot.coordenates.y1 - shot.coordenates.radius, 0);
}