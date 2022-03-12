#include "obstacles.h"

//===================================================parede=====================================================


// configura a parede
void init_wall(Obstacle *wall) {
    //divide a tela em blocos
    int unities_per_screen_width = (int)(SCREEN_W / WALL_UNITY);
    int unities_per_screen_height_fraction = (int)((SCREEN_H) / WALL_UNITY);

    wall->width = unities_per_screen_width * WALL_UNITY + WALL_UNITY * (rand() % (unities_per_screen_width * 1));
    wall->height = (int)(0.2 * unities_per_screen_height_fraction) * WALL_UNITY + WALL_UNITY * (int)(rand() % unities_per_screen_height_fraction * 0.4);
    wall->coordenates.x1 = SCREEN_W*1 + rand() % (SCREEN_W*2);
    wall->coordenates.x2 = wall->coordenates.x1 + wall->width;
    wall->coordenates.y1 = SCREEN_BORDER_H + rand() % (int)(SCREEN_H - wall->height - FLOOR_HEIGHT - SCREEN_BORDER_H ); 
    wall->coordenates.y2 = wall->coordenates.y1 + wall->height;
}

// atualiza parede
void update_wall(Obstacle *wall) {
    if(wall->coordenates.x2 >= 0) {
        wall->coordenates.x1 -= 1;
        wall->coordenates.x2 -= 1;
    }
    else {
        init_wall(wall);
    }
}

// desenha a parede
void draw_wall(Obstacle wall, ALLEGRO_BITMAP *sprite) {
    if(wall.coordenates.x1 < 1.1 * SCREEN_W) {
        for(int i = 0; i < wall.height / WALL_UNITY; i++) {
            for(int j = 0; j < wall.width / WALL_UNITY; j++) {
                al_draw_bitmap(sprite, wall.coordenates.x1 + j * WALL_UNITY, wall.coordenates.y1 + i * WALL_UNITY, 0);
            }
        }
    }
}

//===================================================chão=====================================================

// inicia o chão
void init_floor(Obstacle floor[]) {
    for(int i = 0; i < TOTAL_FLOOR_SPLITS; i++) {
        floor[i].width = FLOOR_WIDTH;
        floor[i].height = FLOOR_HEIGHT;
        floor[i].coordenates.x1 = i * FLOOR_WIDTH;
        floor[i].coordenates.x2 = floor[i].coordenates.x1 + FLOOR_WIDTH;
        floor[i].coordenates.y1 =  SCREEN_H - FLOOR_HEIGHT;
        floor[i].coordenates.y2 =  SCREEN_H;
    }
}

// atualiza o chão
void update_floor(Obstacle floor[]) {
    for(int i = 0; i < TOTAL_FLOOR_SPLITS; i++) {
        if(floor[i].coordenates.x2  < 0) {
            int predecessor = (i - 1 >= 0) ? (i - 1) : (TOTAL_FLOOR_SPLITS - 1);
            floor[i].coordenates.x1 = floor[predecessor].coordenates.x2 + 1;
            floor[i].coordenates.x2 = floor[i].coordenates.x1 + floor[i].width;
        } else {
            floor[i].coordenates.x1--;
            floor[i].coordenates.x2--;
        }
    }
}

// desenha o chão
void draw_floor(Obstacle floor[], ALLEGRO_BITMAP *sprite) {
    for(int i = 0; i < TOTAL_FLOOR_SPLITS; i++) {
        if(floor[i].coordenates.x1 < 1.2*SCREEN_W) al_draw_bitmap(sprite, floor[i].coordenates.x1, floor[i].coordenates.y1, 0);
    }
}

