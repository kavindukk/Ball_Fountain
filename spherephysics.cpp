#include "spherephysics.h"

SpherePhysics::SpherePhysics(std::array<double,3> position,
    std::array<double,3> velocity, 
    double dt):
    position{position}, velocity{velocity}, dt{dt}
{

}

void SpherePhysics::UpdatePosition()
{
this->position = {  position[0] + velocity[0]*dt,
                    position[1] + velocity[1]*dt,
                    position[2] + velocity[2]*dt + 0.5*gravity*dt*dt,                                      
                };
}

void SpherePhysics::UpdateVelocity()
{
    this->velocity = {  velocity[0],
                        velocity[1],
                        velocity[2]+ gravity*dt,
                    };
}

void SpherePhysics::Update()
{
    this->UpdateVelocity();
    this->UpdatePosition();
}

std::array<double, 3> SpherePhysics::getPosition()
{
    return this->position;
}
