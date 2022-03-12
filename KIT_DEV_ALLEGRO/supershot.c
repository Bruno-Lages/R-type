#include "supershot.h"

//configura o tiro especial
void init_supershot(Supershot *supershot, Spaceship spaceship) {
    supershot->coordenates.x1 = spaceship.x;
    supershot->coordenates.y1 = spaceship.y;
    supershot->coordenates.radius = -5;
    supershot->loading = 0;
    supershot->shooted = 0;
    supershot->direction = -spaceship.multiplicator;
}

//carrega o supertiro
void load_supershot(Supershot *supershot, Spaceship spaceship) {
    if(supershot->loading && supershot->coordenates.radius <= 10) supershot->coordenates.radius++;
    supershot->direction = -spaceship.multiplicator;
}

//recarrega o supertiro
void reload_supershot(Supershot *supershot, Spaceship spaceship) {
    supershot->coordenates.x1 = spaceship.x;
    supershot->coordenates.y1 = spaceship.y;
    supershot->coordenates.radius = -5;
}

//atualiza a posição do supertiro
void update_supershot(Supershot *supershot, Spaceship spaceship) {
    // se atirado
    if(supershot->shooted) {
        // atualiza a posição
        if(supershot->coordenates.x1 <= SCREEN_W && supershot->coordenates.x1 + supershot->coordenates.radius > 0 ) {
            supershot->coordenates.x1 += spaceship.speed*2*supershot->direction;
        // devolve para a nave
        } else if(supershot->coordenates.x1 > SCREEN_W || supershot->coordenates.x1 + supershot->coordenates.radius < 0) {
            supershot->shooted = 0;
        }
    // se carregando
    } else if(supershot->loading) {
        supershot->coordenates.x1 = spaceship.x;
        supershot->coordenates.y1 = spaceship.y;
    }
}

//desenha o supertiro
void draw_supershot(Supershot supershot, ALLEGRO_BITMAP *sprite, ALLEGRO_BITMAP *rsprite, ALLEGRO_BITMAP *loading_sprite[], int timer) {
    if(supershot.loading) {
        if(supershot.direction > 0) {
            al_draw_bitmap_region(loading_sprite[15 - timer % 8], 0, 0, 55, 67, supershot.coordenates.x1 - 10, supershot.coordenates.y1 -SPACESHIP_HEIGHT/2, 0);
        } else {
            al_draw_bitmap_region(loading_sprite[timer % 8], 0, 0, 55, 67, supershot.coordenates.x1 - 45, supershot.coordenates.y1 -SPACESHIP_HEIGHT/2, 0);
        }

    } else if(supershot.shooted) {
        
        if(supershot.direction > 0) {
            al_draw_bitmap_region(sprite, (rand() % 2)*128, 0, 128, 30, supershot.coordenates.x1 - 113, supershot.coordenates.y1 - supershot.coordenates.radius, 0);
        } else {
            al_draw_bitmap_region(rsprite, (rand() % 2)*128, 0, 128, 30, supershot.coordenates.x1 - supershot.coordenates.radius, supershot.coordenates.y1 - supershot.coordenates.radius - 5 , 0);
        }

        // al_draw_filled_circle(supershot.coordenates.x1, supershot.coordenates.y1, supershot.coordenates.radius, supershot.color);
    }
}
