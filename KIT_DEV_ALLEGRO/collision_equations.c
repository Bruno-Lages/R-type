#include "collision_equations.h"

// calcula a colisão entre dois quadrados ou retângulos
int rectangular_collision(Paralelogram rectangle1, Paralelogram rectangle2) {
    int horizontal_collision_left = rectangle1.x1 >= rectangle2.x1 && rectangle1.x1 <= rectangle2.x2;
    int horizontal_collision_right = rectangle1.x2 >= rectangle2.x1 && rectangle1.x2 <= rectangle2.x2;
    int vertical_collision_up = rectangle1.y1 >= rectangle2.y1 && rectangle1.y1 <= rectangle2.y2;
    int vertical_collision_down = rectangle1.y2 >= rectangle2.y1 && rectangle1.y2 <= rectangle2.y2;
        
    return (horizontal_collision_left || horizontal_collision_right) && (vertical_collision_up || vertical_collision_down);
}

// calcula a colisão de dois círculos
int circular_collision(Circle circle1, Circle circle2) {
    // return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2)) <= radius1 + radius2;
    return (points_distance(circle1.x1, circle1.y1, circle2.x1, circle2.y1) <= circle1.radius + circle2.radius);
}

// calcula a colisão entre um quadrado ou retangulo e um círculo
int rectangular_circular_collision(Paralelogram rectangle, Circle circle) {
    int horizontal_collision_right = circle.x1 + circle.radius >= rectangle.x1 && circle.x1 + circle.radius <= rectangle.x2;
    int horizontal_collision_left = circle.x1 - circle.radius >= rectangle.x1 && circle.x1 - circle.radius <= rectangle.x2;
    int vertical_collision_down = circle.y1 + circle.radius >= rectangle.y1 && circle.y1 + circle.radius <= rectangle.y2;
    int vertical_collision_up = circle.y1 - circle.radius >= rectangle.y1 && circle.y1 - circle.radius <= rectangle.y2;
    if((horizontal_collision_left || horizontal_collision_right) && (vertical_collision_up || vertical_collision_down)) return 1;

    int center_in_rectangle = circle.y1 >= rectangle.y1 && circle.y1 <= rectangle.y2;
    if((horizontal_collision_left || horizontal_collision_right) && center_in_rectangle) return 1;

    int corner1 = points_distance(circle.x1, circle.y1, rectangle.x1, rectangle.y1) <= circle.radius;
    int corner2 = points_distance(circle.x1, circle.y1, rectangle.x1, rectangle.y2) <= circle.radius;
    int corner3 = points_distance(circle.x1, circle.y1, rectangle.x2, rectangle.y1) <= circle.radius;
    int corner4 = points_distance(circle.x1, circle.y1, rectangle.x2, rectangle.y2) <= circle.radius;

    return corner1 || corner2 || corner3 || corner4;
}
