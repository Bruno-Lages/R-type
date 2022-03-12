#include "spaceship.h"


// configura a nave
void init_spaceship(Spaceship *spaceship) {
    spaceship->x = 10 + SPACESHIP_WIDTH;
    spaceship->y = SCREEN_H/2 + SPACESHIP_HEIGHT/2;
    spaceship->border.x1 = spaceship->x - SPACESHIP_WIDTH;
    spaceship->border.x2 = spaceship->x;
    spaceship->border.y1 = spaceship->y - SPACESHIP_HEIGHT/2;
    spaceship->border.y2 = spaceship->y + SPACESHIP_HEIGHT/2;
    spaceship->speed = 3;
    spaceship->lifes = 3;
    spaceship->damaged = 0;
    //0 = left 1 = right
    spaceship->direction = 1;
    spaceship->multiplicator = spaceship->direction ? -1 : 1;
    //0 = up 1 = going up 2 = normal 3 = going down 4 = down
    spaceship->heighness = 2;
}

//move a nave para cima
void move_spaceship_up(Spaceship *spaceship) {
    if(spaceship->y - SPACESHIP_HEIGHT/2 <= SCREEN_BORDER_H) return;
    spaceship->y -= spaceship->speed;
    spaceship->border.y1 -= spaceship->speed;
    spaceship->border.y2 -= spaceship->speed;
    spaceship->heighness = 1;
}

//move a nave para cima mais rápido
void move_spaceship_up_faster(Spaceship *spaceship) {
    if(spaceship->y - SPACESHIP_HEIGHT/2 <= SCREEN_BORDER_H) return;
    spaceship->y -= spaceship->speed + 3;
    spaceship->border.y1 -= spaceship->speed + 3;
    spaceship->border.y2 -= spaceship->speed + 3;
    spaceship->heighness = 0;
}

//move a nave para trás
void move_spaceship_left(Spaceship *spaceship) {
    if(spaceship->x < 0) return;
    spaceship->x -= spaceship->speed;
    spaceship->border.x1 -= spaceship->speed;
    spaceship->border.x2 -= spaceship->speed;
    if(spaceship->direction) spaceship->x -= SPACESHIP_WIDTH; 
    spaceship->direction = 0;
    spaceship->multiplicator = 1;
}

//move a nave para baixo
void move_spaceship_down(Spaceship *spaceship) {
    if(spaceship->y + SPACESHIP_HEIGHT/2 > SCREEN_H) return;
    spaceship->y += spaceship->speed;
    spaceship->border.y1 += spaceship->speed;
    spaceship->border.y2 += spaceship->speed;
    spaceship->heighness = 3;
}

//move a nave para baixo mais rápido
void move_spaceship_down_faster(Spaceship *spaceship) {
    if(spaceship->y + SPACESHIP_HEIGHT/2 > SCREEN_H) return;
    spaceship->y += spaceship->speed + 3;
    spaceship->border.y1 += (spaceship->speed + 3);
    spaceship->border.y2 += (spaceship->speed + 3);
    spaceship->heighness = 4;
}

//move a nave para frente
void move_spaceship_right(Spaceship *spaceship) {
    if(spaceship->x > SCREEN_W) return;
    spaceship->x += spaceship->speed;
    spaceship->border.x1 += spaceship->speed;
    spaceship->border.x2 += spaceship->speed;
    if(!spaceship->direction) spaceship->x += SPACESHIP_WIDTH;
    spaceship->direction = 1;
    spaceship->multiplicator = -1;
}

void stabilize_spaceship(Spaceship *spaceship) {
    spaceship->heighness = 2;
}

void update_spaceship(Spaceship *spaceship) {
    if(spaceship->x_movement == 1) move_spaceship_right(spaceship);
    if(spaceship->x_movement == -1) move_spaceship_left(spaceship);
    if(spaceship->y_movement == 1) move_spaceship_up(spaceship);
    if(spaceship->y_movement == -1) move_spaceship_down(spaceship);
    if(spaceship->y_movement == 2) move_spaceship_up_faster(spaceship);
    if(spaceship->y_movement == -2) move_spaceship_down_faster(spaceship);
    if(!spaceship->y_movement) stabilize_spaceship(spaceship);
}

// desenha a nave
void draw_spaceship(Spaceship *spaceship, ALLEGRO_BITMAP *sprite) {
    if(!spaceship->lifes) return;

    if(spaceship->damaged) {
        al_draw_tinted_bitmap_region(sprite, al_map_rgb(200, 60, 0), SPACESHIP_WIDTH*spaceship->direction, 8 + SPACESHIP_HEIGHT*spaceship->heighness, SPACESHIP_WIDTH, SPACESHIP_HEIGHT, spaceship->x - spaceship->direction*SPACESHIP_WIDTH, spaceship->y - SPACESHIP_HEIGHT/2, 0);

        //atualiza o dano da nave
        if(time(NULL) % 3 == 0) spaceship->damaged--;

    }
    else {
        al_draw_bitmap_region(sprite, SPACESHIP_WIDTH*spaceship->direction, 8 + SPACESHIP_HEIGHT*spaceship->heighness, SPACESHIP_WIDTH, SPACESHIP_HEIGHT, spaceship->x - spaceship->direction*SPACESHIP_WIDTH, spaceship->y - SPACESHIP_HEIGHT/2, 0);
    }
}

//a nave recebe dano
void spaceship_damaged(Spaceship *spaceship) {
    spaceship->damaged = 2;
    spaceship->lifes--;
}