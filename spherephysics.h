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
    SpherePhysics(std::array<double,3> position={0.,0.,0.}, std::array<double,3> velocity={15.,8.,20.}, double dt = 1.0/30.0);
    void UpdatePosition();
    void UpdateVelocity();
    void update_velocity_when_sphere_just_hit_boundry(int axisNo);
    void Update();
    std::array<double,3> getPosition();
    std::array<double,3> get_velocity();
protected:
    std::array<double,3> position;
    std::array<double,3> velocity;
    double gravity{-9.81};
    double dt;
    double verticalCOR{-.7};
    double horizontalCOR{.8};
    double radiusOfSphere{0.4};
    double scaleFactorContainer{8.};
};

#endif // SPHEREPHYSICS_H
