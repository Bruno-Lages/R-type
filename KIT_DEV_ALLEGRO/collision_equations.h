#ifndef COLLISION_EQUATIONS
#define COLLISION_EQUATIONS

#include "equations.h"

// calcula a colisão entre dois quadrados ou retângulos
int rectangular_collision(Paralelogram rectangle1, Paralelogram rectangle2);

// calcula a colisão de dois círculos
int circular_collision(Circle circle1, Circle circle2);

// calcula a colisão entre um quadrado ou retangulo e um círculo
int rectangular_circular_collision(Paralelogram rectangle, Circle circle);

#endif