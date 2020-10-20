
#include "spherecallback.h"

void SphereUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        if(mUp)
            mCount++;
        else
            mCount--;

        sp.Update();
        position = sp.getPosition();
        osg::Vec3d scaleFactor(position[0], position[0], - position[1]);
//        osg::Vec3d scaleFactor(mScaleStep*mCount+1.0, 1.0, 1.0);
        osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform *> (node);
//        pat->setScale(scaleFactor);
        pat->setPosition(scaleFactor);

        traverse(node, nv);

        if(mCount==30 || mCount==-30)
            mUp=!mUp;

    }