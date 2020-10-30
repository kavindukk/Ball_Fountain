#ifndef BALL_H
#define BALL_H

#include "spherephysics.h"
#include "graphicsrepresentation.h"

struct ball
{
    ball(SpherePhysics* _sp, graphicsRepresentation* _gr);
    SpherePhysics* mSp;
    graphicsRepresentation* mGr;
};

#endif // BALL_H
