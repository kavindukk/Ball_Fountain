#include "ball.h"

ball::ball(SpherePhysics* _sp, graphicsRepresentation* _gr)
{
    mSp = _sp;
    mGr = _gr;
}

ball::~ball()
{
    delete[] mSp;
    delete[] mGr;
}
