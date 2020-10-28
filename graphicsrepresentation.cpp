#include "graphicsrepresentation.h"

graphicsRepresentation::graphicsRepresentation(osg::Group* Root, float Radius, osg::Vec4 Color):
    mRoot(Root), mRadius(Radius), mColor(Color)
{

}

void graphicsRepresentation::create_sphere_geode()
{
    osg::Sphere* sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 0.f ), mRadius );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
    sd->setColor( mColor );
    sd->setName( "Sphere" );

    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;
    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
    stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    this->mGd = geode;
}

void graphicsRepresentation::create_transform()
{
//    osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform;
//    transform->setPosition(osg::Vec3( 0.f, 0.f, 0.f ));
//    transform->setUpdateCallback(new SphereUpdateCallback());
//    transform->addChild(geode);
//    return transform;
}
