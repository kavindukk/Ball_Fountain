#ifndef SPHERECALLBACK_H
#define SPHERECALLBACK_H

#include <osg/PositionAttitudeTransform>
#include<array>

#include "spherephysics.h"

class SphereUpdateCallback: public osg::NodeCallback
{
public:
    SphereUpdateCallback(){}
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

protected:
    double mScaleStep{1.0/30.0};
    std::array<double,3> initPos = {0.,0.,0.};
    std::array<double,3> initVel={0.,0.,5.};
    SpherePhysics sp;
    std::array<double,3> position;
};

#endif
