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
        velocity[2] = verticalCOR*velocity[2];
        velocity[0] = horizontalCOR*velocity[0];
        velocity[1] = horizontalCOR*velocity[1];
    } 
    else if (abs(position[0]) == abs(-scaleFactorContainer/2. + radiusOfSphere))
    {
        velocity[0] = verticalCOR*velocity[0];
        velocity[1] = horizontalCOR*velocity[1];
        velocity[2] = horizontalCOR*velocity[2];
    }
    else if (abs(position[1]) == abs(-scaleFactorContainer/2. + radiusOfSphere))
    {
        velocity[1] = verticalCOR*velocity[1];
        velocity[0] = horizontalCOR*velocity[0];
        velocity[2] = horizontalCOR*velocity[2];
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

std::array<double, 3> SpherePhysics::getPosition()
{
    return this->position;
}

std::array<double, 3> SpherePhysics::get_velocity()
{
    return this->velocity;
}
