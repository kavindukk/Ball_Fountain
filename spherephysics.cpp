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

void SpherePhysics::update_collisions_between_balls(SpherePhysics *ball1, SpherePhysics *ball2)
{
    std::array<double,3> v1 = ball1->velocity;
    std::array<double,3> v2 = ball2->velocity;
    std::array<double,3> x1 = ball1->position;
    std::array<double,3> x2 = ball2->position;
    double m1 = ball1->radiusOfSphere;
    double m2 = ball2->radiusOfSphere;
    double coeffCollision = -ball1->verticalCOR;

//    std::array<double,3> vB1 = v1 - (2*m1/(m1+m2))*(calculate_dot_product(v1-v2, x1-x2))

}


double SpherePhysics::calculate_2_norm(const std::array<double, 3> &v)
{
    double norm = 0.;
    for(int i=0; i<3; i++)
    {
        norm = norm + v[i]*v[i];
    }
    return sqrt(norm);
}

double SpherePhysics::calculate_dot_product(const std::array<double, 3> &v1, const std::array<double, 3> &v2)
{
    double v = 0.;
    for(int i=0; i<3; i++)
    {
        v = v + v1[i]*v2[i];
    }
    return v;
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
