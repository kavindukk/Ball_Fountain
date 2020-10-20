#include "spherephysics.h"

SpherePhysics::SpherePhysics(std::array<double,2> position,
    std::array<double,2> velocity, 
    double dt):
    position{position}, velocity{velocity}, dt{dt}
{

}

void SpherePhysics::UpdatePosition()
{
this->position = {  position[0] + velocity[0]*dt,
                    position[1] + velocity[1]*dt + 0.5*gravity*dt*dt,                                      
                };
}

void SpherePhysics::UpdateVelocity()
{
    this->velocity = {  velocity[0],
                        velocity[1]+ gravity*dt,
                    };
}

void SpherePhysics::Update()
{
    this->UpdateVelocity();
    this->UpdatePosition();
}

std::array<double, 2> SpherePhysics::getPosition()
{
    return this->position;
}
