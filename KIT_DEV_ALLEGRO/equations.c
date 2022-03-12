#include "equations.h"


double points_distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}



//calcula uma equação de reta a partir de dois pontos
double angle(int sx1, int sy1, int tx2, int ty2) {
    return atan2((ty2 - sy1), (tx2 - sx1)) - PI;
}


//calcula a equação de onda de acordo com os dados fornecidos
double wave_equation(int wave_origin, int wave_height, int wave_width, double x_coordenate ) {
    return wave_origin + wave_height * cos(( (2*PI) / wave_width) * x_coordenate);
}
