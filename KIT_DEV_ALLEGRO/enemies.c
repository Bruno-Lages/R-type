#include "enemies.h"


//min 1, max 3
int ENEMIES_SPEED = 2;

//===========================================inimigos simples=================================

//configura inimigos
void init_enemy(Enemy *enemy, int enemy_type) {
    enemy->coordenates.radius = BASIC_ENEMY_RADIUS;
    enemy->coordenates.x1 = SCREEN_W + rand() % SCREEN_W*2;
    enemy->wave_origin = SCREEN_H/2 +  sin(rand() % 7)*(int)(SCREEN_H/3 - enemy->coordenates.radius*2);
    enemy->coordenates.y1 = enemy->wave_origin;
    enemy->speed = ENEMIES_SPEED;
    enemy->shooted = 0;
    enemy->enemy_type = enemy_type;
}

//inicia um inimigo simples da fila
void init_follower_enemy(Enemy *follower, Enemy leader, int x) {
    follower->coordenates.radius = 24;
    follower->coordenates.x1 = x;
    follower->wave_origin = leader.wave_origin;
    follower->coordenates.y1 = leader.wave_origin;
    follower->speed = ENEMIES_SPEED;
    follower->shooted = 0;
    follower->enemy_type = 2;
}

//atualiza a posição dos inimigos
void update_enemy(Enemy *enemy) {
    if(enemy->coordenates.x1 > -enemy->coordenates.radius*3 && !enemy->shooted) {
        enemy->coordenates.x1 -= enemy->speed;
        enemy->coordenates.x1 -= enemy->speed;
        double wave_width = (SCREEN_W/3);
        double wave_height = enemy->coordenates.radius*3;
        double y = wave_equation(enemy->wave_origin, wave_height, wave_width, enemy->coordenates.x1);
        enemy->coordenates.y1 = y;
    }
    else {
        if(enemy->enemy_type == 1) init_enemy(enemy, 1);
        if(enemy->enemy_type == 2) enemy->coordenates.x1 -= enemy->speed;
    }
}

//desenha inimigo
void draw_enemy(Enemy enemy, ALLEGRO_BITMAP *enemy_sprite[]) {
    if(!enemy.shooted && enemy.coordenates.x1 < 1.2*SCREEN_W) {
        double rad = (((int)enemy.coordenates.x1 % 361) * PI) / 180;

        if(rad >= 5.4) al_draw_bitmap(enemy_sprite[6], enemy.coordenates.x1 - 24, enemy.coordenates.y1 - 24, 0);
        else if(rad >= 3.93) al_draw_bitmap(enemy_sprite[0], enemy.coordenates.x1 - 24, enemy.coordenates.y1 - 24, 0);
        else if(rad >= 3.17) al_draw_bitmap(enemy_sprite[3], enemy.coordenates.x1 - 24, enemy.coordenates.y1 - 24, 0);
        else if(rad >= 2.35) al_draw_bitmap(enemy_sprite[2], enemy.coordenates.x1 - 24, enemy.coordenates.y1 - 24, 0);
        else if(rad >= 1.40) al_draw_bitmap(enemy_sprite[1], enemy.coordenates.x1 - 24, enemy.coordenates.y1 - 24, 0);
        else if(rad >= 0.78) al_draw_bitmap(enemy_sprite[0], enemy.coordenates.x1 - 24, enemy.coordenates.y1 - 24, 0);
        else if(rad >= 0.18) al_draw_bitmap(enemy_sprite[7], enemy.coordenates.x1 - 24, enemy.coordenates.y1 - 24, 0);
        else if(rad >= 0) al_draw_bitmap(enemy_sprite[6], enemy.coordenates.x1 - 24, enemy.coordenates.y1 - 24, 0);
    }

}

//inicia uma fila de inimigos simples
void init_enemy_line(Enemy enemy[], int total_enemies) {
    init_enemy(&enemy[0], 2);
    for(int i = 1; i <= total_enemies; i++) {
        init_follower_enemy(&enemy[i], enemy[0], enemy[i-1].coordenates.x1 + enemy[i-1].coordenates.radius*4);
    }
    
}

//atualiza a fila de inimigos simples
void update_enemy_line(Enemy enemy[], int total_enemies) {
    for(int i = 0; i < total_enemies; i++) {
        update_enemy(&enemy[i]);
    }
    if(enemy[total_enemies-1].coordenates.x1 < enemy[total_enemies-1].coordenates.radius*2) {
        init_enemy_line(enemy, total_enemies);
    }
}

//===============================================robô==========================================================

//inicia o robô
void init_robot(Robot *robot) {
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->coordenates.x1 = SCREEN_W*1.3 + rand() % SCREEN_W*4;
    robot->coordenates.x2 = robot->coordenates.x1 + robot->width;
    robot->coordenates.y1 = SCREEN_BORDER_H + rand() % (SCREEN_H/2);
    robot->coordenates.y2 = robot->coordenates.y1 + robot->height;
    robot->speed = ENEMIES_SPEED;
    robot->shooted = 0;

    //inicia o tiro do robô
    init_enemy_shot(&robot->shot);

}

//atualiza o robô
void update_robot(Robot *robot, Spaceship spaceship, int shot_time) {
    if(robot->coordenates.x1 + robot->width < 0 || robot->shooted) init_robot(robot);
    robot->coordenates.x1 -= robot->speed;
    robot->coordenates.x2 -= robot->speed; 
    if(robot->coordenates.x1 < SCREEN_W) {

        if(shot_time) {
            if(spaceship.y > robot->coordenates.y1 + robot->height/2) {
                robot->coordenates.y1 += robot->speed;
                robot->coordenates.y2 += robot->speed;
            } else if(spaceship.y < robot->coordenates.y1){
                robot->coordenates.y1 -= robot->speed;
                robot->coordenates.y2 -= robot->speed;
            }

        }
        
        //a cada poucos segundos, atira
        if(robot->shot.shooted == 0 && shot_time && rand() % (1 + (6 - ENEMIES_SPEED)) == 0) enemy_shoot_out(&robot->shot, spaceship, robot->coordenates.x1, robot->coordenates.y1 + robot->height/2, robot->speed);
    
    }
}


//desenha o robô
void draw_robot(Robot robot, ALLEGRO_BITMAP *robot_sprite, ALLEGRO_TIMER *timer, float FPS) {
    if(robot.coordenates.x1 > 1.2*SCREEN_W) return;

    //pega um segundo, e divide por 4;
    int frame = ((int)(al_get_timer_count(timer) / FPS) % 4);

    //no quarto frame, vai para a segunda posição novamente
    if (frame == 3) {
        frame = 1;
    }

    al_draw_bitmap_region(robot_sprite, 59 * frame, 0, robot.width, robot.height, robot.coordenates.x1, robot.coordenates.y1, 0);
}

// ===========================================robô de chão/aspirador de pó=========================================

//inicia o robô do chão
void init_floor_robot(Floor_robot *floor_robot) {
    floor_robot->shooted = 0;
    floor_robot->direction = -1;
    floor_robot->speed = ENEMIES_SPEED;
    floor_robot->coordenates.x1 = SCREEN_W + rand() % (SCREEN_W*2);
    floor_robot->coordenates.x2 = floor_robot->coordenates.x1 + FLOOR_ROBOT_WIDTH;
    floor_robot->coordenates.y2 = SCREEN_H - FLOOR_HEIGHT;
    floor_robot->coordenates.y1 = floor_robot->coordenates.y2 -  FLOOR_ROBOT_HEIGHT;

    for(int i = 0; i < FLOOR_ROBOT_TOTAL_SHOTS; ++i) {
        init_enemy_shot(&floor_robot->shot[i]);
    }
}

//atualiza a posição e os tiros do robô de chão
void update_floor_robot(Floor_robot *floor_robot, Spaceship spaceship, int shot_time) {
    
    if(shot_time && floor_robot->coordenates.x1 < SCREEN_W && rand() % 6 == 0) {
        // procura pelo primeiro tiro não atirado e atira
        for(int i = 0; i < FLOOR_ROBOT_TOTAL_SHOTS; i++) {
            if(!floor_robot->shot[i].shooted) {
                
                enemy_shoot_out(&(floor_robot->shot[i]), spaceship, floor_robot->coordenates.x1 + FLOOR_ROBOT_WIDTH/2, floor_robot->coordenates.y1, floor_robot->speed);
                break;
            }
        }    
    }

    floor_robot->coordenates.x1 += floor_robot->direction * (floor_robot->speed + 1);
    floor_robot->coordenates.x2 += floor_robot->direction * (floor_robot->speed + 1);

    if(floor_robot->coordenates.x1 <= 1) {
        floor_robot->direction = 1;
    }

    if(floor_robot->coordenates.x2 >= SCREEN_W && floor_robot->coordenates.x1 < SCREEN_W) {
        floor_robot->direction = -1;
    }

    if(floor_robot->shooted) {
        init_floor_robot(floor_robot);
    }

}

//desenha o robô de chão
void draw_floor_robot(Floor_robot floor_robot, ALLEGRO_BITMAP *sprite, ALLEGRO_TIMER *timer, float FPS) {

    if(floor_robot.coordenates.x1 > 1.2*SCREEN_W) return;

    //pega um segundo, e divide por 4;
    int frame = 1 + ((int)(al_get_timer_count(timer) / FPS) % 4);

    //no terceiro frame, volta para o primeiro
    if(frame == 3) {
        frame = 1;
    }

    //no quarto frame, vai para a terceira posição
    if (frame == 4) {
        frame = 3;
    }

    int sprite_source = (floor_robot.direction > 0) ? 200 : 300;

    al_draw_bitmap_region(sprite, sprite_source + floor_robot.direction * 100 * frame, 0, FLOOR_ROBOT_WIDTH, FLOOR_ROBOT_HEIGHT, floor_robot.coordenates.x1, floor_robot.coordenates.y1, 0);
}

//===================================================canhão=======================================

//inicia o canhão e seus tiros
void init_cannon(Cannon *cannon, Obstacle wall) {
    cannon->shooted = 0;
    cannon->coordenates.x1 = wall.coordenates.x1 + rand() % (int)(wall.width - CANNON_WIDTH);
    cannon->coordenates.x2 = cannon->coordenates.x1 + CANNON_WIDTH;
    cannon->coordenates.y1 = wall.coordenates.y2;
    cannon->coordenates.y2 = cannon->coordenates.y1 + CANNON_HEIGHT;


    for(int i = 0; i < CANNON_TOTAL_SHOTS;i++) {
        init_enemy_shot(&cannon->shot[i]);
    }
}

//atualiza a posição dos tiros e sua coordenada
void update_cannon(Cannon *cannon, Obstacle wall, Spaceship spaceship, int shot_time, ALLEGRO_SAMPLE *sfx) {
    if(cannon->coordenates.x2 <= 0) cannon->shooted = 1;

        cannon->coordenates.x1 -= 1;
        cannon->coordenates.x2 -= 1;

    for(int i = 0; i < CANNON_TOTAL_SHOTS; i++) {

        if(spaceship.y > cannon->coordenates.y2 && spaceship.x < cannon->coordenates.x1 && cannon->coordenates.x1 < SCREEN_H*1.2 && !cannon->shot[i].shooted && shot_time && !cannon->shooted) {
            al_play_sample(sfx,0.4, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            enemy_shoot_out(&cannon->shot[i], spaceship, cannon->coordenates.x1, cannon->coordenates.y2, ENEMIES_SPEED);
            break;
        } 

    }
}

//desenha o canhão
void draw_cannon(Cannon cannon, ALLEGRO_BITMAP *sprite) { 
    if(cannon.shooted) return;
    al_draw_bitmap_region(sprite, CANNON_WIDTH, CANNON_HEIGHT, CANNON_WIDTH, CANNON_HEIGHT, cannon.coordenates.x1, cannon.coordenates.y1, 0);
}
