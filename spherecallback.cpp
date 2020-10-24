
#include "spherecallback.h"

void SphereUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        sp.Update();
        position = sp.getPosition();
        osg::Vec3d spherePosition(position[0], position[1], position[2]);
        osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform *> (node);
        pat->setPosition(spherePosition);

        traverse(node, nv);
    }
