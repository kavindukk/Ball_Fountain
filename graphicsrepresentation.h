#ifndef GRAPHICSREPRESENTATION_H
#define GRAPHICSREPRESENTATION_H

#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osg/PositionAttitudeTransform>

#include "spherecallback.h"

class graphicsRepresentation
{
public:
    graphicsRepresentation(osg::Group* Root, float Radius, osg::Vec4 Color);
    void create_sphere_geode();
    void create_transform();

protected:
    osg::Geode* mGd;
    osg::PositionAttitudeTransform* mPat;
    osg::Group* mRoot;
    float mRadius;
    osg::Vec4 mColor;
};

#endif // GRAPHICSREPRESENTATION_H
