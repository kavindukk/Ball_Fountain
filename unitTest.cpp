#include "gtest/gtest.h"
#include "spherephysics.h"

#include<array>

TEST(FallingOnlyUnderGravity, CheckPositionWithoutBouncingBack)
{
    SpherePhysics sp;
    for (size_t i = 0; i < 5; i++)
    {
        sp.Update();
    }
//    std::array<double,3> position = sp.getPosition();
    
    EXPECT_NEAR(-0.13625, sp.getPosition()[2], 0.001 );
}

TEST(FallingOnlyUnderGravity, CheckVelocityWithoutBouncingBack)
{
    SpherePhysics sp;
    for (size_t i = 0; i < 5; i++)
    {
        sp.Update();
    }
//    std::array<double,3> position = sp.getPosition();
    
    EXPECT_NEAR(-1.635, sp.get_velocity()[2], 0.001 );
}
