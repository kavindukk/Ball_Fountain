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

TEST(MathsFunctions, CheckDotProductFunction)
{
    SpherePhysics sp;
    std::array<double,3> v1 = {1.,3.,5.};
    std::array<double,3> v2 = {2.,1.,2.};
    double Dot = sp.calculate_dot_product(v1,v2);

    EXPECT_EQ(15., Dot );
}

TEST(MathsFunctions, Check2NormFunction)
{
    SpherePhysics sp;
    std::array<double,3> v1 = {1.,3.,5.};
    double norm = sp.calculate_2_norm(v1);

    EXPECT_EQ(sqrt(35), norm );
}

TEST(MathsFunctions, CheckSubstract2ArraysFunction)
{
    SpherePhysics sp;
    std::array<double,3> v1 = {1.,3.,5.};
    std::array<double,3> v2 = {2.,-1.,1.};
    std::array<double,3> v = sp.substract_2_arrays(v1,v2);

    EXPECT_EQ(-1., v[0] );
    EXPECT_EQ(4., v[1] );
    EXPECT_EQ(4., v[2] );
}

TEST(MathsFunctions, CheckArrayScalarMultipicationFunction)
{
    SpherePhysics sp;
    std::array<double,3> v = {1.,3.,5.};
    sp.list_multiply_by_scalar(v,2.);

    EXPECT_EQ(2., v[0] );
    EXPECT_EQ(6., v[1] );
    EXPECT_EQ(10., v[2] );
}




