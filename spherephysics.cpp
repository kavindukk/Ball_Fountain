#include "spherephysics.h"

SpherePhysics::SpherePhysics(std::array<double,3> position, std::array<double,3> velocity, double radius)
    :position(position),velocity(velocity), radiusOfSphere(radius)
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
