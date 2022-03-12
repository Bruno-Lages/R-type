#ifndef COLLISIONS
#define COLLISIONS

#include <allegro5/allegro.h>
#include "equations.h"
#include "collision_equations.h"
#include "obstacles.h"
#include "spaceship.h"
#include "shot.h"
#include "enemy_shot.h"
#include "supershot.h"
#include "enemies.h"
#include "power_up.h"

//=============================================colisões com obstáculos===============================================

//calcula a colisão de dois obstáculos
void obstacles_collision(Obstacle *obstacle1, Obstacle *obstacle2);

//calcula a colisão da nave com obstáculos
void spaceship_obstacle_collision(Obstacle wall, Spaceship *spaceship);

//calcula a colisão entre um tiro e um obstáculo
void shot_obstacle_collision(Obstacle obstacle, Shot *shot);

//calcula a colisão entre o tiro especial e um obstáculo
void supershot_obstacle_collision(Obstacle obstacle, Supershot *supershot);

//calcula a colisão entre um tiro inimigo e um obstáculo
void enemy_shot_obstacle_collision(Obstacle obstacle, Enemy_shot *shot);

//calcula a colisão entre inimigos e colisões
void basic_enemies_obstacle_collision(Obstacle Obstacle, Enemy *enemy);

//calcula a colisão um robô e um obstáculo
void robots_obstacle_collision(Obstacle obstacle, Robot *robot);

//calcula a colisão entre um robô de chão e um obstáculo
void floor_robot_obstacle_collision(Obstacle obstacle, Floor_robot *floor_robot);

//calcula a colisão entre um canhão e um obstáculo
void cannon_obstacle_collision(Obstacle obstacle, Cannon *cannon);

//calcula a colisão da gasolina com obstáculos
void power_up_obstacle_collision(Power_up *power_up, Obstacle obstacle);

//=============================================colisões com a nave===============================================

//calcula a colisão da nave com um tiro inimigo
void spaceship_enemy_shot_collision(Spaceship *spaceship, Enemy_shot *shot);

//calcula a colisão da nave com um inimigo simples
void spaceship_basic_enemy_collision(Spaceship *spaceship, Enemy *enemy);

//calcula a colisão da nave com um robô
void spaceship_robot_collision(Spaceship *spaceship, Robot *robot);

//calcula a colisão da nave com um robô de chão
void spaceship_floor_robot_collision(Spaceship *spaceship, Floor_robot *floor_robot);

//calcula a colisão da nave com um canhão
void spaceship_cannon_collision(Spaceship *spaceship, Cannon *cannon);

//calcula a colisão da gasolina com a nave
void spaceship_power_up_collision(Spaceship *spaceship, Power_up *power_up);

//=============================================colisões com o tiro====================================================

//calcula a colisão entre um tiro da nave e um tiro inimigo
void shot_enemy_shot_collision(Shot *shot, Enemy_shot *enemy_shot, int *score);

//calcula a colisão entre um tiro e um inimigo
void shot_basic_enemy_collision(Shot *shot, Enemy *enemy, int *score);

//calcula a colisão entre um tiro e um inimigo
void shot_robot_collision(Shot *shot, Robot *robot, int *score);

//calcula a colisão entre um tiro e um robô inimigo
void shot_floor_robot_collision(Shot *shot, Floor_robot *floor_robot, int *score);

//calcula a colisão entre um tiro e um canhão
void shot_cannon_collision(Shot *shot, Cannon *cannon, int *score);

//calcula a colisão entre um tiro e gasolina
void shot_power_up_collision(Shot *shot, Power_up *power_up);

//==============================================colisões com o supertiro===========================================

//calcula a colisão do supertiro com o tiro inimigo
void supershot_enemy_shot_collision(Supershot *supershot, Enemy_shot *enemy_shot, int *score);

//calcula a colisão do supertiro com os inimigos
void supershot_basic_enemy_collision(Supershot *supershot, Enemy *enemy, int *score);

//calcula a colisão do supertiro com os inimigos
void supershot_robot_collision(Supershot *supershot, Robot *robot, int *score);

//calcula a colisão do supertiro com os inimigos
void supershot_floor_robot_collision(Supershot *supershot, Floor_robot *floor_robot, int *score);

//calcula a colisão do supertiro com os inimigos
void supershot_cannon_collision(Supershot *supershot, Cannon *cannon, int *score);

//calcula a colisão do supertiro com os inimigos
void supershot_power_up_collision(Supershot *supershot, Power_up *power_up);

//=========================================colisões com o tiro inimigo==============================================

//calcula a colisão entre dois tiros inimigos
void enemy_shots_collision(Enemy_shot *shot1, Enemy_shot *shot2);

//calcula a colisão entre um tiro inimigo e um inimigo simples
void enemy_shot_basic_enemy_collision(Enemy_shot *shot, Enemy *enemy);

//calcula a colisão entre um robô e o tiro inimigo
void enemy_shot_robot_collision(Robot *robot, Enemy_shot *shot);

//calcula a colisão entre um robô de chão e o tiro inimigo
void enemy_shot_floor_robot_collision(Floor_robot *robot, Enemy_shot *shot);

//calcula a colisão entre um canhão e o tiro inimigo
void enemy_shot_cannon_collision(Cannon *cannon, Enemy_shot *shot);

//calcula a colisão da gasolina com um tiro inimigo
void enemy_shot_power_up_collision(Power_up *power_up, Enemy_shot *shot);

//=======================================colisões com o inimigo simples============================================

//calcula a colisão entre dois inimigos simples
void basic_enemies_collision(Enemy *enemy1, Enemy *enemy2);

//calcula a colisão entre um inimigo simples e um robô
void basic_enemies_robot_collision(Enemy *enemy, Robot *robot);

//calcula a colisão entre um inimigo simples e um robô de chão
void basic_enemies_floor_robot_collision(Enemy *enemy, Floor_robot *floor_robot);

//calcula a colisão entre um inimigo simples e um canhão
void basic_enemies_cannon_collision(Enemy *enemy, Cannon *cannon);

//calcula a colisão entre um inimigo simples e gasolina
void basic_enemies_power_up_collision(Enemy *enemy, Power_up *power_up);

//========================================colisões com robôs========================================================

//calcula a colisão entre dois robôs
void robots_collision(Robot *robot1, Robot *robot2);

//calcula a colisão entre um robô e um robô de chão
void robots_floor_robot_collision(Robot *robot, Floor_robot *floor_robot);

//calcula a colisão entre um robô e um canhão
void robots_cannon_collision(Robot *robot, Cannon *cannon);

//calcula a colisão entre um robô e gasolina
void robots_power_up_collision(Robot *robot, Power_up *power_up);

//========================================colisões com robôs de chão=======================================================

//calcula a colisão entre dois robôs de chão
void floor_robot_collision(Floor_robot *floor_robot1, Floor_robot *floor_robot2);

//calcula a colisão entre um robô de chão e um canhão
void floor_robot_cannon_collision(Floor_robot *floor_robot, Cannon *cannon);

//calcula a colisão entre um robô de chão e gasolina
void floor_robot_power_up_collision(Floor_robot *floor_robot, Power_up *power_up);

//========================================colisões com canhões==========================================================

//calcula a colisão entre dois canhões
void cannons_collision(Cannon *cannon1, Cannon *cannon2);

//calcula a colisão entre canhão e gasolina
void cannon_power_up_collision(Cannon *cannon, Power_up *power_up);

#endif