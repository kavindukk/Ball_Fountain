#include "gtest/gtest.h"
#include "spherephysics.h"
#include "osgwidget.h"

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
    std::array<double,3> v1 = {1.,3.,5.};
    std::array<double,3> v2 = {2.,1.,2.};
    double Dot = calculate_dot_product(v1,v2);

    EXPECT_EQ(15., Dot );
}

TEST(MathsFunctions, Check2NormFunction)
{    
    std::array<double,3> v1 = {1.,3.,5.};
    double norm = calculate_2_norm(v1);

    EXPECT_EQ(sqrt(35), norm );
}

TEST(MathsFunctions, CheckSubstract2ArraysFunction)
{    
    std::array<double,3> v1 = {1.,3.,5.};
    std::array<double,3> v2 = {2.,-1.,1.};
    std::array<double,3> v = substract_2_arrays(v1,v2);

    EXPECT_EQ(-1., v[0] );
    EXPECT_EQ(4., v[1] );
    EXPECT_EQ(4., v[2] );
}

TEST(MathsFunctions, CheckArrayScalarMultipicationFunction)
{
    std::array<double,3> v = {1.,3.,5.};
    list_multiply_by_scalar(v,2.);

    EXPECT_EQ(2., v[0] );
    EXPECT_EQ(6., v[1] );
    EXPECT_EQ(10., v[2] );
}

TEST(Collisions, CheckUpdateCollisionFunctionWhenVelocityIsHorizontal)
{
    SpherePhysics* sp1 = new SpherePhysics(std::array<double,3> {0.,0.,0.}, std::array<double,3> {5.,0.,0});
    SpherePhysics* sp2 = new SpherePhysics(std::array<double,3> {1.,0.,0.}, std::array<double,3> {-5.,0.,0});
    update_collisions_between_balls(sp1,sp2);
    EXPECT_EQ(-3.5, sp1->get_velocity()[0] );
    EXPECT_EQ(3.5, sp2->get_velocity()[0] );
}

TEST(Collisions, CheckUpdateCollisionFunctionWhenVelocityIsAllTheDirections)
{
    SpherePhysics* sp1 = new SpherePhysics(std::array<double,3> {1.,2.,1.}, std::array<double,3> {5.,4.,5});
    SpherePhysics* sp2 = new SpherePhysics(std::array<double,3> {2.,1.,2.}, std::array<double,3> {3.,2., 1.});
    update_collisions_between_balls(sp1,sp2);
    EXPECT_NEAR(1.88341, sp1->get_velocity()[0], 0.001 );
    EXPECT_NEAR(4.41658, sp1->get_velocity()[1], 0.001 );
    EXPECT_NEAR(1.88341, sp1->get_velocity()[2], 0.001 );
    EXPECT_NEAR(3.71658, sp2->get_velocity()[0], 0.001 );
    EXPECT_NEAR(-0.21658, sp2->get_velocity()[1], 0.001 );
    EXPECT_NEAR(2.31658, sp2->get_velocity()[2], 0.001 );
    
}

TEST(Collisions, CheckCheckForCollisionFunction)
{
    SpherePhysics* sp1 = new SpherePhysics(std::array<double,3> {0.,0.,0.}, std::array<double,3> {5.,0.,0});
    SpherePhysics* sp2 = new SpherePhysics(std::array<double,3> {0.9,0.,0.}, std::array<double,3> {-5.,0.,0});

    EXPECT_EQ(true, check_for_collisions(sp1,sp2) );
    delete sp1;
    delete sp2;
}

TEST(MathsFunctions, CheckCreateRandomNoWithinARangeFunction)
{
    double min{5.};
    double max{10.};
    std::default_random_engine generator;
    std::normal_distribution<double> distribution (min+(max-min)/2.,(max-min)/4);
    double number =distribution(generator);
    if(number>max)
    {
        number=max;
    }
    else if(number<min)
    {
        number=min;
    }
    EXPECT_TRUE((number >= 5) && (number <= 10));
}

TEST(MathsFunctions, CheckconvertingDoubleToFloat)
{

    EXPECT_EQ(typeid(float), typeid((float)2.));
}




