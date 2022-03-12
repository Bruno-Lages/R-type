#ifndef ENEMIES
#define ENEMIES

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "equations.h"
#include "enemy_shot.h"
#include "obstacles.h"

#define TOTAL_ENEMIES 10
#define MAX_ENEMIES_SPEED 5

#define BASIC_ENEMY_RADIUS 24

#define ROBOT_WIDTH 59
#define ROBOT_HEIGHT 55

#define TOTAL_FLOOR_ROBOTS 2
#define FLOOR_ROBOT_HEIGHT 100
#define FLOOR_ROBOT_WIDTH 100
#define FLOOR_ROBOT_TOTAL_SHOTS 1

#define CANNON_TOTAL_SHOTS 10
#define CANNON_WIDTH 40
#define CANNON_HEIGHT 40

extern int ENEMIES_SPEED;

// estrutura dos inimigos
typedef struct Enemy {
    Circle coordenates;
    double wave_origin;
    double speed;
    int shooted;
    int enemy_type;
} Enemy;

//configura inimigos
void init_enemy(Enemy *enemy, int enemy_type);

//inicia um inimigo simples da fila
void init_follower_enemy(Enemy *follower, Enemy leader, int x);

//atualiza a posição dos inimigos
void update_enemy(Enemy *enemy);

//desenha inimigo
void draw_enemy(Enemy enemy, ALLEGRO_BITMAP *enemy_sprite[]);

//inicia uma fila de inimigos simples
void init_enemy_line(Enemy enemy[], int total_enemies);

//atualiza a fila de inimigos simples
void update_enemy_line(Enemy enemy[], int total_enemies);

typedef struct Robot {
    int width;
    int height;
    Paralelogram coordenates;
    double speed;
    int shooted;
    Enemy_shot shot;
} Robot;

//inicia o robô
void init_robot(Robot *robot);

//atualiza o robô
void update_robot(Robot *robot, Spaceship spaceship, int shot_time);

//desenha o robô
void draw_robot(Robot robot, ALLEGRO_BITMAP *robot_sprite, ALLEGRO_TIMER *timer, float FPS);

typedef struct Floor_robot {
    Paralelogram coordenates;
    Enemy_shot shot[FLOOR_ROBOT_TOTAL_SHOTS];
    int direction;
    int shooted;
    double speed;
} Floor_robot;

void init_floor_robot(Floor_robot *floor_robot);

void update_floor_robot(Floor_robot *floor_robot, Spaceship spaceship, int shot_time);

void draw_floor_robot(Floor_robot floor_robot, ALLEGRO_BITMAP *sprite, ALLEGRO_TIMER *timer, float FPS);

typedef struct Cannon {
    int direction;
    Paralelogram coordenates;
    Enemy_shot shot[CANNON_TOTAL_SHOTS];
    int shooted;
} Cannon;

//inicia o canhão e seus tiros
void init_cannon(Cannon *cannon, Obstacle wall);

//atualiza a posição dos tiros e sua coordenadas
void update_cannon(Cannon *cannon, Obstacle wall, Spaceship spaceship, int shot_time, ALLEGRO_SAMPLE *sfx);

//desenha o canhão
void draw_cannon(Cannon cannon, ALLEGRO_BITMAP *sprite);

#endif