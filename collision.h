#ifndef COLLISION_H
#define COLLISION_H

#include "spherephysics.h"

void update_collisions_between_balls(SpherePhysics* ball1, SpherePhysics* ball2);
bool check_for_collisions(SpherePhysics* ball1, SpherePhysics* ball2);
double calculate_dot_product(const std::array<double,3> &v1,const std::array<double,3> &v2);
std::array<double,3> substract_2_arrays(const std::array<double,3> &v1,const std::array<double,3> &v2);
double calculate_2_norm(const std::array<double,3> &v1);
std::array<double,3> list_multiply_by_scalar(std::array<double,3> &v1,double scalar);

#endif // COLLISION_H
