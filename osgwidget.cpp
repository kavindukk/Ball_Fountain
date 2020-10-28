#include "osgwidget.h"
#include "spherephysics.h"

#include <osg/Camera>
#include <osg/DisplaySettings>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osgDB/WriteFile>
#include <osgGA/EventQueue>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
#include <osg/LineWidth>
#include <osgUtil/SmoothingVisitor>
#include <osg/PositionAttitudeTransform>
#include <osg/BlendFunc>

#include <cassert>
#include <vector>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>

OSGWidget::OSGWidget( QWidget* parent, Qt::WindowFlags flags ):
    QOpenGLWidget{ parent,flags },
    mGraphicsWindow{ new osgViewer::GraphicsWindowEmbedded{ this->x(),
                                                            this->y(),
                                                            this->width(),
                                                            this->height() } }
  , mViewer{ new osgViewer::CompositeViewer }
{
    mRoot = new osg::Group;
    mView = new osgViewer::View;
    createViewer(mViewer, mView);
    osg::Geode* geode = createSpheregeode();
    osg::PositionAttitudeTransform *transform = createTransformation(geode);
    mRoot->addChild(transform);
    // osg::PositionAttitudeTransform *transform2 = create_wireframe_tetrahedron(osg::Vec4(0.f,0.f,0.f,1.f), osg::Vec3d(4., 4., 4.));
    // mRoot->addChild(transform2);
    createContainer(mRoot);
    
    this->setFocusPolicy( Qt::StrongFocus );
    this->setMinimumSize( 100, 100 );
    this->setMouseTracking( true );

    this->update();

    double framesPerSecond{30};
    double timeStep{1.0/framesPerSecond};
    double timerDurationInMilliSeconds{timeStep * 1000};
    mTimerId=startTimer(timerDurationInMilliSeconds);

}

OSGWidget::~OSGWidget()
{
    killTimer(mTimerId);
    delete mViewer;
}

void OSGWidget::timerEvent(QTimerEvent *)
{
    update();
}

void OSGWidget::paintEvent( QPaintEvent* /* paintEvent */ )
{
    this->makeCurrent();

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );

    this->paintGL();

    painter.end();

    this->doneCurrent();
}

void OSGWidget::paintGL()
{
    mViewer->frame();
}

void OSGWidget::resizeGL( int width, int height )
{
    this->getEventQueue()->windowResize( this->x(), this->y(), width, height );
    mGraphicsWindow->resized( this->x(), this->y(), width, height );

    this->on_resize( width, height );
}

void OSGWidget::on_resize( int width, int height )
{
    std::vector<osg::Camera*> cameras;
    mViewer->getCameras( cameras );

    auto pixelRatio = this->devicePixelRatio();

    cameras[0]->setViewport( 0, 0, width * pixelRatio, height * pixelRatio );
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if( eventQueue )
        return eventQueue;
    else
        throw std::runtime_error( "Unable to obtain valid event queue");
}

void OSGWidget::createCamera(osgViewer::View *mView)
{
    float aspectRatio = static_cast<float>( this->width() ) / static_cast<float>( this->height() );
    auto pixelRatio   = this->devicePixelRatio();

    osg::Camera* camera = new osg::Camera;
    camera->setViewport( 0, 0, this->width() * pixelRatio, this->height() * pixelRatio );

    camera->setClearColor( osg::Vec4( 0.f, 0.f, 0.5, 1.f ) );
    camera->setProjectionMatrixAsPerspective( 45.f, aspectRatio, 1.f, 1000.f );
    camera->setGraphicsContext( mGraphicsWindow );
    mView->setCamera( camera );
    mView->setSceneData( mRoot.get() );
    mView->addEventHandler( new osgViewer::StatsHandler );
}

void OSGWidget::createManipulator(osgViewer::View *mView)
{
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
    manipulator->setAllowThrow( false );
    manipulator->setHomePosition(osg::Vec3d(-5.0,-20.0,8.0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));
    mView->setCameraManipulator( manipulator );
}

osg::Geode* OSGWidget::createSpheregeode()
{
    //Create Sphere
    osg::Sphere* sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 0.f ), 0.5f );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
    sd->setColor( osg::Vec4( 1.f, 0.f, 1.f, 1.f ) );
    sd->setName( "Sphere" );
    //

    //Create Geometry
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
    stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    //
    return geode;
}

 osg::PositionAttitudeTransform* OSGWidget::createTransformation(osg::Geode* geode)
 {
     SpherePhysics *sp = new SpherePhysics(std::array<double,3>{0,0,0},std::array<double,3>{10,0,0},1.0/30.0);
    osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform;
    transform->setPosition(osg::Vec3( 0.f, 0.f, 0.f ));
    transform->setUpdateCallback(new SphereUpdateCallback(sp));
    transform->addChild(geode);
    return transform;
 }

void OSGWidget::createViewer(osgViewer::CompositeViewer *mViewer, osgViewer::View *mView)
{
    mView = new osgViewer::View;
    this->createCamera(mView);
    this->createManipulator(mView);
    mViewer->addView( mView );
    mViewer->setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );
    mViewer->realize();
    mView->home();
}

 void OSGWidget::createContainer(osg::Group * mRoot)
 {
    osg::ShapeDrawable * shape1 = new osg::ShapeDrawable( new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f),  8.0f, 8.0f, 8.0f) );
    shape1->setColor(osg::Vec4(1.f, 0.f, 0.f, 0.1f));
    osg::Geode * boxGeode = new osg::Geode;
    boxGeode->addDrawable( shape1 );
    osg::StateSet* Bstateset = boxGeode->getOrCreateStateSet();
    osg::PositionAttitudeTransform *boxTransform = new osg::PositionAttitudeTransform;
    boxTransform->addChild(boxGeode);
    mRoot->addChild(boxTransform);
 }

osg::PositionAttitudeTransform * OSGWidget::create_wireframe_tetrahedron(osg::Vec4 &color, osg::Vec3d &scaleFactor)
{
    osg::Vec3Array* v = new osg::Vec3Array;
    v->resize( 8 );
    (*v)[0].set( 1.f, 1.f, -.5f );
    (*v)[1].set(-1.f, 1.f, -.5f );
    (*v)[2].set(1.f, -1.f, -.5f );
    (*v)[3].set(-1.f, -1.f, -.5f );
    (*v)[4].set( 1.f, 1.f, .5f );
    (*v)[5].set(-1.f, 1.f, .5f );
    (*v)[6].set(1.f, -1.f, .5f );
    (*v)[7].set(-1.f, -1.f, .5f );

    osg::Geometry* geom = new osg::Geometry;
    geom->setUseDisplayList( false );

    osg::Vec4Array* c = new osg::Vec4Array;
    c->push_back( color );
    geom->setColorArray( c, osg::Array::BIND_OVERALL );
    GLushort idxLines[15] = {0, 1, 3,  2, 0, 4, 5, 2, 3, 6, 5, 6, 7, 1, 3};
    GLushort idxLoops[3] = {0, 1, 2 };

    geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINES, 15, idxLines ) );
    geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINE_LOOP, 3, idxLoops ) ); 
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( geom );

    geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );
    geode->getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    osg::PositionAttitudeTransform* transform = new osg::PositionAttitudeTransform;
    transform->setScale(scaleFactor);

    transform->addChild(geode);
    return transform;
}
