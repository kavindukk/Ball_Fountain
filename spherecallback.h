#ifndef SPHERECALLBACK_H
#define SPHERECALLBACK_H

#include <osg/PositionAttitudeTransform>

#include "spherephysics.h"

class SphereUpdateCallback: public osg::NodeCallback
{
public:
    SphereUpdateCallback(){}
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

protected:
    bool mUp{true};
//    unsigned int mCount{0};
    int mCount{0};
    double mScaleStep{1.0/30.0};
    SpherePhysics sp;
    std::array<double,3> position;

};

#endif
