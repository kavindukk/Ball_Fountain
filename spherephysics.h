#ifndef SPHEREPHYSICS_H
#define SPHEREPHYSICS_H

#include <array>
#include <vector>

#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>
//#include <Eigen/Core>

class SpherePhysics
{
public:
    SpherePhysics(std::array<double,3> position={0.,0.,0.}, std::array<double,3> velocity={0.,0.,0},
                double radius = 0.4);
    void UpdatePosition();
    void UpdateVelocity();
    void update_velocity_when_sphere_just_hit_boundry(int axisNo);
    void Update();    
    std::array<double,3> getPosition();
    std::array<double,3> get_velocity();
    void set_position(std::array<double,3> &pos);
    void set_velocity(std::array<double,3> &vel);
    double get_radius();    
    double get_collision_coefficient();    

protected:
    std::array<double,3> position;
    std::array<double,3> velocity;
    double gravity{-9.81};
    double dt{1./30.};
    double verticalCOR{-.7};
    double horizontalCOR{.8};
    double radiusOfSphere;
    double scaleFactorContainer{8.};
};

#endif // SPHEREPHYSICS_H
