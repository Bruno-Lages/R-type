#include "collisions.h"

//=============================================colisões com obstáculos===============================================

void obstacles_collision(Obstacle *obstacle1, Obstacle *obstacle2) {
    if(obstacle1->coordenates.y2 > (SCREEN_H - FLOOR_HEIGHT)) init_wall(obstacle1);
    if(obstacle2->coordenates.y2 > (SCREEN_H - FLOOR_HEIGHT)) init_wall(obstacle2);
    if(rectangular_collision(obstacle1->coordenates, obstacle2->coordenates)) {
        obstacle1->coordenates.x1 = -obstacle1->width - 10;
        obstacle1->coordenates.x2 = -10;
        init_wall(obstacle1);
    }
}

//calcula a colisão da nave com obstáculos
void spaceship_obstacle_collision(Obstacle obstacle, Spaceship *spaceship) {
    if(obstacle.coordenates.x1 > SCREEN_W*2 || !spaceship->lifes) return;
    if(spaceship->border.y2 > (SCREEN_H - FLOOR_HEIGHT) || rectangular_collision(spaceship->border, obstacle.coordenates)) {
        spaceship->lifes = 0;
    }
}

//calcula a colisão entre um tiro e um obstáculo
void shot_obstacle_collision(Obstacle obstacle, Shot *shot) {
    if(!shot->shooted || obstacle.coordenates.x1 > 2*SCREEN_W) return;
    if( shot->coordenates.y1 + shot->coordenates.radius > (SCREEN_H - FLOOR_HEIGHT) || rectangular_circular_collision(obstacle.coordenates, shot->coordenates)) {
        shot->shooted = 0;
    }
}

//calcula a colisão do tiro especial com um obstáculo
void supershot_obstacle_collision(Obstacle obstacle, Supershot *supershot) {
    if(!supershot->shooted || obstacle.coordenates.x1 > 2*SCREEN_W) return;
    if( supershot->coordenates.y1 + supershot->coordenates.radius > (SCREEN_H - FLOOR_HEIGHT) || rectangular_circular_collision(obstacle.coordenates, supershot->coordenates)) {
        supershot->shooted = 0;
    }
}

//calcula a colisão entre um tiro de robô e um obstáculo
void enemy_shot_obstacle_collision(Obstacle obstacle, Enemy_shot *shot) {
    if(!shot->shooted) return;

    if(shot->coordenates.y1 + shot->coordenates.radius > (SCREEN_H - FLOOR_HEIGHT) || rectangular_circular_collision(obstacle.coordenates, shot->coordenates)) {
        shot->shooted = 0;
    }
}

//calcula a colisão entre inimigos e colisões
void basic_enemies_obstacle_collision(Obstacle obstacle, Enemy *enemy) {
    if(enemy->shooted || obstacle.coordenates.x1 > 2*SCREEN_W) return;
    if(enemy->coordenates.y1 + enemy->coordenates.radius > (SCREEN_H - FLOOR_HEIGHT) || rectangular_circular_collision(obstacle.coordenates, enemy->coordenates)) {
        enemy->shooted = 1;
    }
}

//calcula a colisão um robô um obstáculo
void robots_obstacle_collision(Obstacle obstacle, Robot *robot) {
    if(robot->shooted || obstacle.coordenates.x1 > 2*SCREEN_W) return;
    if(robot->coordenates.y2 > (SCREEN_H - FLOOR_HEIGHT) || rectangular_collision(robot->coordenates, obstacle.coordenates)) {
        robot->shooted = 1;
    }
}

//calcula a colisão entre um robô de chão e um obstáculo
void floor_robot_obstacle_collision(Obstacle obstacle, Floor_robot *floor_robot) {
    if(floor_robot->shooted || obstacle.coordenates.x1 > 2*SCREEN_W) return;
    if(floor_robot->coordenates.y2 > (SCREEN_H - FLOOR_HEIGHT) || rectangular_collision(floor_robot->coordenates, obstacle.coordenates)) {
        floor_robot->shooted = 1;
    }
}

//calcula a colisão entre um canhão e um obstáculo
void cannon_obstacle_collision(Obstacle obstacle, Cannon *cannon) {
    if(cannon->shooted || obstacle.coordenates.x1 > 2*SCREEN_W) return;
    if(cannon->coordenates.y2 > (SCREEN_H - FLOOR_HEIGHT) || rectangular_collision(cannon->coordenates, obstacle.coordenates)) {
        cannon->shooted = 1;
    }
}

//calcula a colisão do power_up com obstáculos
void power_up_obstacle_collision(Power_up *power_up, Obstacle obstacle) {
    if(power_up->rectangular_coordenates.y2 > (SCREEN_H - FLOOR_HEIGHT)) {
        init_power_up(power_up);
        return;
    }

    if(!power_up->is_circle)
        if(rectangular_collision(power_up->rectangular_coordenates, obstacle.coordenates)) {
            init_power_up(power_up);
            return;
        }

    if(power_up->is_circle)
        if(rectangular_circular_collision(obstacle.coordenates, power_up->circular_coordenates)) {
            init_power_up(power_up);
            return;
    }
}

//=============================================colisões com a nave===============================================

//calcula a colisão da nave com um tiro de robô
void spaceship_enemy_shot_collision(Spaceship *spaceship, Enemy_shot *shot) {
    if(!shot->shooted || !spaceship->lifes) return;

    if(rectangular_circular_collision(spaceship->border, shot->coordenates)) {
        shot->shooted = 0;
        spaceship_damaged(spaceship);
    }
}

//calcula a colisão da nave com um inimigo simples
void spaceship_basic_enemy_collision(Spaceship *spaceship, Enemy *enemy) {
    if(enemy->shooted || enemy->coordenates.x1 > 2*SCREEN_W || !spaceship->lifes) return;

    if(rectangular_circular_collision(spaceship->border, enemy->coordenates)) {
        enemy->shooted = 1;
        spaceship_damaged(spaceship);
    }
}

//calcula a colisão da nave com um robô
void spaceship_robot_collision(Spaceship *spaceship, Robot *robot) {
    if(robot->shooted || robot->coordenates.x1 > 2*SCREEN_W || !spaceship->lifes) return;

    if(rectangular_collision(spaceship->border, robot->coordenates)) {
        robot->shooted = 1;
        spaceship_damaged(spaceship);
    }
}

//colisão da nave com um robô de chão
void spaceship_floor_robot_collision(Spaceship *spaceship, Floor_robot *floor_robot) {
    if(floor_robot->shooted && floor_robot->coordenates.x1 > 2*SCREEN_W || !spaceship->lifes) return;

    if(rectangular_collision(spaceship->border, floor_robot->coordenates)) {
        floor_robot->shooted = 1;
        spaceship_damaged(spaceship);
    }
}

//colisão da nave com um canhão
void spaceship_cannon_collision(Spaceship *spaceship, Cannon *cannon) {
    if(cannon->shooted || cannon->coordenates.x1 > 2*SCREEN_W || !spaceship->lifes) return;

    if(rectangular_collision(spaceship->border, cannon->coordenates)) {
        cannon->shooted = 1;
        spaceship_damaged(spaceship);
    }
}

//calcula a colisão do power_up com a nave
void spaceship_power_up_collision(Spaceship *spaceship, Power_up *power_up) {
    if(!spaceship->lifes) return;
    if(!power_up->is_circle)
        if(rectangular_collision(spaceship->border, power_up->rectangular_coordenates)) {
            if(power_up->type)spaceship->speed += 2;
            init_power_up(power_up);
        }

    if(power_up->is_circle)
        if(rectangular_circular_collision(spaceship->border, power_up->circular_coordenates)) {
            if(!power_up->type)spaceship->lifes++;
            init_power_up(power_up);
        }
}

//=============================================colisões com o tiro====================================================

//calcula a colisão entre um tiro da nave e um tiro inimigo
void shot_enemy_shot_collision(Shot *shot, Enemy_shot *enemy_shot, int *score) {
    if(!enemy_shot->shooted || !shot->shooted) return;
    if(circular_collision(enemy_shot->coordenates, shot->coordenates)) {
        shot->shooted = 0;
        enemy_shot->shooted = 0;
        *score += enemy_shot->speed;
    }
}

//calcula a colisão entre um tiro e um inimigo
void shot_basic_enemy_collision(Shot *shot, Enemy *enemy, int *score) {
    if(!shot->shooted || enemy->shooted || enemy->coordenates.x1 > 2*SCREEN_W) return;
    if(circular_collision(shot->coordenates, enemy->coordenates)) {
        shot->shooted = 0;
        enemy->shooted = 1;
        *score += 1 + enemy->coordenates.radius;
    }
}

//calcula a colisão entre um tiro e um inimigo
void shot_robot_collision(Shot *shot, Robot *robot, int *score) {
    if(robot->shooted || !shot->shooted || robot->coordenates.x1 > 2*SCREEN_W) return;
    if(rectangular_circular_collision(robot->coordenates, shot->coordenates)) {
        shot->shooted = 0;
        robot->shooted = 1;
        *score += 1 + robot->width;
    }
}

//calcula a colisão entre um tiro inimigo e um robô
void shot_floor_robot_collision(Shot *shot, Floor_robot *floor_robot, int *score) {
    if(floor_robot->shooted || !shot->shooted || floor_robot->coordenates.x1 > 2*SCREEN_W) return;
    if(rectangular_circular_collision(floor_robot->coordenates, shot->coordenates)) {
        shot->shooted = 0;
        floor_robot->shooted = 1;
        *score += 1 + FLOOR_ROBOT_WIDTH;
    }
}

void shot_cannon_collision(Shot *shot, Cannon *cannon, int *score) {
    if(cannon->shooted || !shot->shooted || cannon->coordenates.x1 > 2*SCREEN_W) return;
    if(rectangular_circular_collision(cannon->coordenates, shot->coordenates)) {
        shot->shooted = 0;
        cannon->shooted = 1;
        *score += 1 + FLOOR_ROBOT_WIDTH;
    }
}

void shot_power_up_collision(Shot *shot, Power_up *power_up) {
    if(!shot->shooted) return;
    
    if(!power_up->is_circle)    
        if(rectangular_circular_collision(power_up->rectangular_coordenates, shot->coordenates)) {
            shot->shooted = 0;
        }

    if(power_up->is_circle)    
        if(circular_collision(power_up->circular_coordenates, shot->coordenates)) {
            shot->shooted = 0;
    }
}

//==============================================colisões com o supertiro===========================================

//calcula a colisão do supertiro com o tiro inimigo
void supershot_enemy_shot_collision(Supershot *supershot, Enemy_shot *enemy_shot, int *score) {
    if(!supershot->shooted) return;
    if(circular_collision(supershot->coordenates, enemy_shot->coordenates)) {
        enemy_shot->shooted = 0;
        *score += enemy_shot->speed;
    }
}

//calcula a colisão do supertiro com os inimigos
void supershot_basic_enemy_collision(Supershot *supershot, Enemy *enemy, int *score) {
    if(!supershot->shooted) return;
    if(circular_collision(supershot->coordenates, enemy->coordenates)) {
        enemy->shooted = 1;
        *score += 1 + enemy->coordenates.radius;
    }
}

//calcula a colisão do supertiro com os inimigos
void supershot_robot_collision(Supershot *supershot, Robot *robot, int *score) {
    if(!supershot->shooted) return;
    if(rectangular_circular_collision(robot->coordenates, supershot->coordenates)) {
        robot->shooted = 1;
        *score += 1 + FLOOR_ROBOT_WIDTH;
    }
}

void supershot_floor_robot_collision(Supershot *supershot, Floor_robot *floor_robot, int *score) {
    if(!supershot->shooted) return;
    if(rectangular_circular_collision(floor_robot->coordenates, supershot->coordenates)) {
        floor_robot->shooted = 1;
        *score += 1 + FLOOR_ROBOT_WIDTH;        
    }
}

void supershot_cannon_collision(Supershot *supershot, Cannon *cannon, int *score) {
    if(!supershot->shooted) return;
    if(rectangular_circular_collision(cannon->coordenates, supershot->coordenates)) {
        cannon->shooted = 1;
        *score += 1 + FLOOR_ROBOT_WIDTH;
    }
} 

void supershot_power_up_collision(Supershot *supershot, Power_up *power_up) {
    if(!supershot->shooted) return;
    
    if(!power_up->is_circle)
    if(rectangular_circular_collision(power_up->rectangular_coordenates, supershot->coordenates)) {
        init_power_up(power_up);
    }

    if(power_up->is_circle)
    if(circular_collision(power_up->circular_coordenates, supershot->coordenates)) {
        init_power_up(power_up);
    }
} 

//==========================================tiro inimigo============================================================

//calcula a colisão entre um tiro de robô e um inimigo simples
void enemy_shots_collision(Enemy_shot *shot1, Enemy_shot *shot2) {
    if(!shot2->shooted || !shot1->shooted) return;
    if(circular_collision(shot1->coordenates, shot2->coordenates)) {
        shot1->shooted = 0;
        shot2->shooted = 0;
    }
}

//calcula a colisão entre um tiro de robô e um inimigo simples
void enemy_shot_basic_enemy_collision(Enemy_shot *shot, Enemy *enemy) {
    if(enemy->shooted || !shot->shooted) return;
    if(circular_collision(shot->coordenates, enemy->coordenates)) {
        shot->shooted = 0;
        enemy->shooted = 1;
    }
}

//calcula a colisão entre um robô e o tiro inimigo
void enemy_shot_robot_collision(Robot *robot, Enemy_shot *shot) {
    if(robot->shooted || !shot->shooted) return;
    if(rectangular_circular_collision(robot->coordenates, shot->coordenates)) {
        shot->shooted = 0;
        robot->shooted = 1;
    }
}

//calcula a colisão entre um robô de chão e o tiro inimigo
void enemy_shot_floor_robot_collision(Floor_robot *floor_robot, Enemy_shot *shot) {
    if(floor_robot->shooted || !shot->shooted) return;
    if(rectangular_circular_collision(floor_robot->coordenates, shot->coordenates)) {
        shot->shooted = 0;
        floor_robot->shooted = 1;
    }
}

//calcula a colisão entre um canhão e o tiro inimigo
void enemy_shot_cannon_collision(Cannon *cannon, Enemy_shot *shot) {
    if(cannon->shooted || !shot->shooted) return;
    if(rectangular_circular_collision(cannon->coordenates, shot->coordenates)) {
        shot->shooted = 0;
        cannon->shooted = 1;
    }
}

//calcula a colisão de power ups e tiros inimigos
void enemy_shot_power_up_collision(Power_up *power_up, Enemy_shot *shot) {
    if(!shot->shooted) return;
    
    if(!power_up->is_circle)
        if(rectangular_circular_collision(power_up->rectangular_coordenates, shot->coordenates)) {
            init_power_up(power_up);
        }

    if(power_up->is_circle)
        if(circular_collision(power_up->circular_coordenates, shot->coordenates)) {
            init_power_up(power_up);
        }
} 

//============================================colisões com inimigos simples========================================

//calcula a colisão entre dois inimigos
void basic_enemies_collision(Enemy *enemy1, Enemy *enemy2) {
    if(enemy1->shooted || enemy2->shooted /*|| enemy1->coordenates.x1 > 2*SCREEN_H*/) return;
    if(circular_collision(enemy1->coordenates, enemy2->coordenates)) {
        enemy2->shooted = 1;
    }
}

//calcula a colisão entre um inimigo simples e um robô
void basic_enemies_robot_collision(Enemy *enemy, Robot *robot) {
    if(enemy->shooted || robot->shooted) return;
    if(rectangular_circular_collision(robot->coordenates, enemy->coordenates)) {
        robot->shooted = 1;
    }
}

//calcula a colisão entre um inimigo simples e um robô de chão
void basic_enemies_floor_robot_collision(Enemy *enemy, Floor_robot *floor_robot) {
    if(enemy->shooted || floor_robot->shooted) return;
    if(rectangular_circular_collision(floor_robot->coordenates, enemy->coordenates)) {
        floor_robot->shooted = 1;
    }
}

//calcula a colisão entre um inimigo simples e um canhão
void basic_enemies_cannon_collision(Enemy *enemy, Cannon *cannon) {
    if(enemy->shooted || cannon->shooted) return;
    if(rectangular_circular_collision(cannon->coordenates, enemy->coordenates)) {
        cannon->shooted = 1;
    }
}

//calcula a colisão entre um inimigo simples e power_up
void basic_enemies_power_up_collision(Enemy *enemy, Power_up *power_up) {
    if(enemy->shooted) return;
    
    if(power_up->is_circle)
        if(rectangular_circular_collision(power_up->rectangular_coordenates, enemy->coordenates)) {
            init_power_up(power_up);
        }

    if(!power_up->is_circle)
        if(circular_collision(power_up->circular_coordenates, enemy->coordenates)) {
            init_power_up(power_up);
        }
}

//========================================colisões com robôs========================================================

//calcula a colisão entre dois robôs
void robots_collision(Robot *robot1, Robot *robot2) {
    if(robot1->shooted || robot2->shooted || robot1->coordenates.x1 > 2*SCREEN_W) return;
    if(rectangular_collision(robot1->coordenates, robot2->coordenates)) {
        robot2->shooted = 1;
    }
}

//calcula a colisão entre um robô e um robô de chão
void robots_floor_robot_collision(Robot *robot, Floor_robot *floor_robot) {
    if(robot->shooted || floor_robot->shooted) return;
    if(rectangular_collision(robot->coordenates, floor_robot->coordenates)) {
        floor_robot->shooted = 1;
    }
}

//calcula a colisão entre um robô e um canhão
void robots_cannon_collision(Robot *robot, Cannon *cannon) {
    if(robot->shooted || cannon->shooted) return;
    if(rectangular_collision(robot->coordenates, cannon->coordenates)) {
        cannon->shooted = 1;
    }
}

//calcula a colisão entre um robô e power_up
void robots_power_up_collision(Robot *robot, Power_up *power_up) {
    if(robot->shooted) return;

    if(!power_up->is_circle)
    if(rectangular_collision(robot->coordenates, power_up->rectangular_coordenates)) {
        init_power_up(power_up);
    }

    if(power_up->is_circle)
    if(rectangular_circular_collision(robot->coordenates, power_up->circular_coordenates)) {
        init_power_up(power_up);
    }
}

//=======================================colisões com robôs de chão=======================================================

//calcula a colisão entre dois robôs de chão
void floor_robot_collision(Floor_robot *floor_robot1, Floor_robot *floor_robot2) {
    if(floor_robot1->shooted || floor_robot2->shooted) return;
    if(rectangular_collision(floor_robot1->coordenates, floor_robot2->coordenates)) {
        floor_robot1->shooted = 1;
    }
}

//calcula a colisão entre um robô de chão e um canhão
void floor_robot_cannon_collision(Floor_robot *floor_robot, Cannon *cannon) {
    if(floor_robot->shooted || cannon->shooted) return;
    if(rectangular_collision(floor_robot->coordenates, cannon->coordenates)) {
        floor_robot->shooted = 1;
    }
}

//calcula a colisão entre um robô de chão e power_up
void floor_robot_power_up_collision(Floor_robot *floor_robot, Power_up *power_up) {
    if(floor_robot->shooted) return;
    
    if(!power_up->is_circle)
    if(rectangular_collision(floor_robot->coordenates, power_up->rectangular_coordenates)) {
        init_power_up(power_up);
    }

    if(power_up->is_circle)
    if(rectangular_circular_collision(floor_robot->coordenates, power_up->circular_coordenates)) {
        init_power_up(power_up);
    }
}

//===========================================colisões com canhões======================================================

//calcula a colisão entre dois canhões
void cannons_collision(Cannon *cannon1, Cannon *cannon2) {
    if(cannon1->shooted || cannon2->shooted) return;
    if(rectangular_collision(cannon1->coordenates, cannon2->coordenates)) {
        cannon2->shooted;
    }
}

//calcula a colisão entre canhão e power_up
void cannon_power_up_collision(Cannon *cannon, Power_up *power_up) {
    if(cannon->shooted) return;
    
    if(!power_up->is_circle)
    if(rectangular_collision(cannon->coordenates, power_up->rectangular_coordenates)) {
        init_power_up(power_up);
    }

    if(power_up->is_circle)
    if(rectangular_circular_collision(cannon->coordenates, power_up->circular_coordenates)) {
        init_power_up(power_up);
    }
}
