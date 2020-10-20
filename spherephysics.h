#ifndef SPHEREPHYSICS_H
#define SPHEREPHYSICS_H

#include <array>

#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>

class SpherePhysics
{
public:
    SpherePhysics(std::array<double,2> position={0,0}, std::array<double,2> velocity={0,0}, double dt = 1.0/30.0);
    void UpdatePosition();
    void UpdateVelocity();
    void Update();
    std::array<double,2> getPosition();
protected:
    std::array<double,2> position;
    std::array<double,2> velocity;
    double gravity{9.81};
    double dt;
};

#endif // SPHEREPHYSICS_H