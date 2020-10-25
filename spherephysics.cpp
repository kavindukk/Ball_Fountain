#include "spherephysics.h"

SpherePhysics::SpherePhysics(std::array<double,3> position,
    std::array<double,3> velocity, 
    double dt):
    position{position}, velocity{velocity}, dt{dt}
{

}

void SpherePhysics::UpdatePosition()
{
    if (position[2] + radiusOfSphere < -scaleFactorContainer)
    {
        position[2] = -scaleFactorContainer;
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
    if (position[2] + radiusOfSphere <= -scaleFactorContainer)
    {
        velocity[2] = verticalCOR*velocity[2];
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
