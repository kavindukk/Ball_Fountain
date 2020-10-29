#ifndef SPHEREPHYSICS_H
#define SPHEREPHYSICS_H

#include <array>
#include <vector>

#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>

//#include "spherecallback.h"

class SpherePhysics
{
public:
    SpherePhysics(std::array<double,3> position={0.,0.,0.}, std::array<double,3> velocity={0.,0.,0}, double dt = 1.0/30.0);
    void UpdatePosition();
    void UpdateVelocity();
    void update_velocity_when_sphere_just_hit_boundry(int axisNo);
    void Update();
    void update_collisions_between_balls(SpherePhysics* ball1, SpherePhysics* ball2);
    double calculate_dot_product(const std::array<double,3> &v1,const std::array<double,3> &v2);
    std::array<double,3> substract_2_arrays(const std::array<double,3> &v1,const std::array<double,3> &v2);
    double calculate_2_norm(const std::array<double,3> &v1);
    std::array<double,3> list_multiply_by_scalar(std::array<double,3> &v1,double scalar);
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
