#include "spherephysics.h"

SpherePhysics::SpherePhysics(std::array<double,3> position, std::array<double,3> velocity, double dt)
    :position(position),velocity(velocity),dt(dt)
{
}

void SpherePhysics::UpdatePosition()
{
     if (position[2] - radiusOfSphere < -scaleFactorContainer/2.)
     {
         position[2] = -scaleFactorContainer/2. + radiusOfSphere;
     }
     else if (position[2] + radiusOfSphere > scaleFactorContainer/2.)
     {
         position[2] = scaleFactorContainer/2. - radiusOfSphere;
     }
     else if (position[0] - radiusOfSphere < -scaleFactorContainer/2.)
     {
         position[0] = -scaleFactorContainer/2. + radiusOfSphere;
     }
     else if (position[0] + radiusOfSphere > scaleFactorContainer/2.)
     {
         position[0] = scaleFactorContainer/2. - radiusOfSphere;
     }
     else if (position[1] - radiusOfSphere < -scaleFactorContainer/2.)
     {
         position[1] = -scaleFactorContainer/2. + radiusOfSphere;
     }
     else if (position[1] + radiusOfSphere > scaleFactorContainer/2.)
     {
         position[1] = scaleFactorContainer/2. - radiusOfSphere;
     }
     else
     {
         this->position = {  position[0] + velocity[0]*dt,
                             position[1] + velocity[1]*dt,
                             position[2] + velocity[2]*dt + 0.5*gravity*dt*dt,
                         };
     }
}

void SpherePhysics::UpdateVelocity()
{
    if (abs(position[2]) == abs(-scaleFactorContainer/2. + radiusOfSphere) )
    {
        update_velocity_when_sphere_just_hit_boundry(2);  
    } 
    else if (abs(position[0]) == abs(-scaleFactorContainer/2. + radiusOfSphere))
    {
        update_velocity_when_sphere_just_hit_boundry(0);  
    }
    else if (abs(position[1]) == abs(-scaleFactorContainer/2. + radiusOfSphere))
    {
        update_velocity_when_sphere_just_hit_boundry(1);  
    }  
    else
    {
        this->velocity = {  velocity[0],
                            velocity[1],
                            velocity[2]+ gravity*dt,
                        };        
    }    
}

void SpherePhysics::Update()
{
    this->UpdatePosition();
    this->UpdateVelocity();
}

void SpherePhysics::update_velocity_when_sphere_just_hit_boundry(int axisNo)
{
    velocity[axisNo] = verticalCOR*velocity[axisNo];
    for (int i = 0; i < 3; i++)
    {
        if (i != axisNo)
        {
            velocity[i] = horizontalCOR*velocity[i];
        }
        
    }
}

std::array<double, 3> SpherePhysics::getPosition()
{
    return this->position;
}

std::array<double, 3> SpherePhysics::get_velocity()
{
    return this->velocity;
}

double SpherePhysics::get_radius()
{
    return radiusOfSphere;
}

double SpherePhysics::get_collision_coefficient()
{
    return -verticalCOR;
}

void SpherePhysics::set_velocity(std::array<double,3> &vel)
{
    velocity = vel;
}

void SpherePhysics::set_position(std::array<double,3> &pos)
{
    position = pos;
}

void update_collisions_between_balls(SpherePhysics *ball1, SpherePhysics *ball2)
{
    std::array<double,3> v1 = ball1->get_velocity();
    std::array<double,3> v2 = ball2->get_velocity();
    std::array<double,3> x1 = ball1->getPosition();
    std::array<double,3> x2 = ball2->getPosition();
    double m1 = ball1->get_radius();
    double m2 = ball2->get_radius();
    double coeffCollision = ball1->get_collision_coefficient();

    std::array<double,3> pB1 = { x1[0]-v1[0]*(3./30.), x1[1]-v1[1]*(3./30.), x1[2]-v1[2]*(1./30.) };
    std::array<double,3> pB2 = { x2[0]-v2[0]*(3./30.), x2[1]-v2[1]*(3./30.), x2[2]-v2[2]*(1./30.) };
    ball1->set_position(pB1);
    ball2->set_position(pB2);

    double c1 = 2*m1/(m1+m2);
    c1 = c1 * calculate_dot_product(substract_2_arrays(v1, v2), substract_2_arrays(x1,x2));
    c1 = c1/calculate_2_norm(substract_2_arrays(x1,x2));
    std::array<double,3> x1_x2 = substract_2_arrays(x1,x2);
    std::array<double,3> vB1 =  substract_2_arrays(v1, list_multiply_by_scalar(x1_x2, c1));
    vB1 = list_multiply_by_scalar(vB1, coeffCollision);

    double c2 = 2*m1/(m1+m2);
    c2 = c2 * calculate_dot_product(substract_2_arrays(v2, v1), substract_2_arrays(x2,x1));
    c2 = c2/calculate_2_norm(substract_2_arrays(x2,x1));
    std::array<double,3> x2_x1 = substract_2_arrays(x2,x1);
    std::array<double,3> vB2 =  substract_2_arrays(v2, list_multiply_by_scalar(x2_x1, c2));
    vB2 = list_multiply_by_scalar(vB2, coeffCollision);
   
    ball1->set_velocity(vB1);
    ball2->set_velocity(vB2);
}

bool check_for_collisions(SpherePhysics* ball1, SpherePhysics* ball2)
{
    std::array<double,3> pos1 = ball1->getPosition();
    std::array<double,3> pos2 = ball2->getPosition();
    double r1 = ball1->get_radius();
    double r2 = ball2->get_radius();
    double distance_between_two_spheres = pow(pos1[0]-pos2[0], 2) + pow(pos1[1]-pos2[1], 2) 
                                        + pow(pos1[2]-pos2[2], 2);
    distance_between_two_spheres = sqrt(distance_between_two_spheres);

    if (distance_between_two_spheres <= r1 + r2 + 0.1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::array<double,3> list_multiply_by_scalar(std::array<double, 3> &v, double scalar)
{
    for(int i=0; i<3; i++)
    {
        v[i] = scalar*v[i];
    }
    return v;
}


std::array<double, 3> substract_2_arrays(const std::array<double, 3> &v1, const std::array<double, 3> &v2)
{
    std::array<double, 3> v = {0,0,0};
    for (int i=0; i<3; i++)
    {
        v[i] = v1[i] - v2[i];
    }
    return v;
}


double calculate_2_norm(const std::array<double, 3> &v)
{
    double norm = 0.;
    for(int i=0; i<3; i++)
    {
        norm = norm + v[i]*v[i];
    }
    return sqrt(norm);
}

double calculate_dot_product(const std::array<double, 3> &v1, const std::array<double, 3> &v2)
{
    double v = 0.;
    for(int i=0; i<3; i++)
    {
        v = v + v1[i]*v2[i];
    }
    return v;
}
