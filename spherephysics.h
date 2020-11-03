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

//void update_collisions_between_balls(SpherePhysics* ball1, SpherePhysics* ball2);
//bool check_for_collisions(SpherePhysics* ball1, SpherePhysics* ball2);
//double calculate_dot_product(const std::array<double,3> &v1,const std::array<double,3> &v2);
//std::array<double,3> substract_2_arrays(const std::array<double,3> &v1,const std::array<double,3> &v2);
//double calculate_2_norm(const std::array<double,3> &v1);
//std::array<double,3> list_multiply_by_scalar(std::array<double,3> &v1,double scalar);

#endif // SPHEREPHYSICS_H
