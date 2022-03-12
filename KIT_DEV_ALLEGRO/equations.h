#ifndef EQUATIONS
#define EQUATIONS

#include <math.h>

#define PI 3.14159265358979323846

#define SCREEN_H 759
#define SCREEN_W 1122

#define SCREEN_BORDER_H 40

typedef struct Coordenates {
    double x1, y1;
} Coordenates;

typedef struct Paralelogram {
    double x1, x2;
    double y1, y2;
} Paralelogram;

typedef struct Circle {
    double x1, y1;
    double radius;
} Circle;

// calcula a distância do centro de dois círculos
double points_distance(int x1, int y1, int x2, int y2);

double angle(int sx1, int sy1, int tx2, int ty2);

//calcula a equação de onda de acordo com os dados fornecidos
double wave_equation(int wave_origin, int wave_height, int wave_width, double x_coordenate );

#endif