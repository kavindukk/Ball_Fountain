#include "osgwidget.h"

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
    // osg::Geode* geode = createSpheregeode();
    // sp1 = new SpherePhysics(std::array<double,3>{0,0,3},std::array<double,3>{0.05,0,0});
    // SpherePhysics * sp2 = new SpherePhysics(std::array<double,3>{1,1,1},std::array<double,3>{15,8,15});
    // osg::PositionAttitudeTransform *transform1 = createTransformation(geode, sp1);
    // osg::PositionAttitudeTransform *transform2 = createTransformation(geode, sp2);
    // mRoot->addChild(transform1);
    // mRoot->addChild(transform2);

    for (int i = 0; i < 5; i++)
    {
        ballList.push_back(create_sphere(mRoot, std::array<double,3>{0,0,-3.5}, create_a_random_velocity(), create_a_random_color(),(float)create_random_no_between_a_range(0.3,0.9)));
    }
    

    // ball* ball1 = create_sphere(mRoot, std::array<double,3>{-3,0,3}, std::array<double,3>{8,10,12}, osg::Vec4(0.0f, 1.f, 0.f, 1.f), 0.8f);
    // ball* ball1 = create_sphere(mRoot, std::array<double,3>{0,0,-3.5}, create_a_random_velocity(), create_a_random_color(),(float)create_random_no_between_a_range(0.3,0.9));
    // ballList.push_back(ball1);
    // ball* ball2 = create_sphere(mRoot, std::array<double,3>{0,0,-3.5}, create_a_random_velocity(), create_a_random_color(), (float)create_random_no_between_a_range(0.3,0.9));
    // ballList.push_back(ball2);

    sp3 = new SpherePhysics(std::array<double,3>{0,0,-3},std::array<double,3>{0,0,10});
    graphicsRepresentation* gr = new graphicsRepresentation(mRoot, sp3, 0.6f, osg::Vec4(1.0f, 0.f, 0.f, 1.f));

//    osg::PositionAttitudeTransform *wireFrame = create_wireframe_tetrahedron(osg::Vec4(1.f,1.f,1.f,1.f), osg::Vec3d(4., 4., 4.));
    osg::PositionAttitudeTransform *wireFrame = create_wireframe_tetrahedron();
    mRoot->addChild(wireFrame);

    create_timer_event();
}

OSGWidget::~OSGWidget()
{
    killTimer(mTimerId);
    delete mViewer;
}

void OSGWidget::set_ball_color(double val, int index)
{
    ballColor[index] = val;
}

void OSGWidget::set_ball_radius(double val, int index)
{
    ballRadius[index] = val;
}

void OSGWidget::set_ball_velocity(double val, int index)
{
    ballVelocity[index] = val;
}

void OSGWidget::timerEvent(QTimerEvent *)
{
    if(check_for_collisions(sp1,sp3)){
        update_collisions_between_balls(sp1,sp3);
    }
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
    manipulator->setHomePosition(osg::Vec3d(10.0,-20.0,3.0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));
    mView->setCameraManipulator( manipulator );
}

osg::Geode* OSGWidget::createSpheregeode()
{
    osg::Sphere* sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 0.f ), 0.5f );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
    sd->setColor( osg::Vec4( 1.f, 0.f, 1.f, 1.f ) );
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
    return geode;
}

 osg::PositionAttitudeTransform* OSGWidget::createTransformation(osg::Geode* geode, SpherePhysics* _sp)
 {
    // SpherePhysics *sp = new SpherePhysics(std::array<double,3>{0,0,0},std::array<double,3>{10,0,0},1.0/30.0);
    SpherePhysics *sp = _sp;
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

    this->setFocusPolicy( Qt::StrongFocus );
    this->setMinimumSize( 100, 100 );
    this->setMouseTracking( true );

    this->update();
}

osg::PositionAttitudeTransform * OSGWidget::create_wireframe_tetrahedron()
{
    osg::Vec3Array* v = new osg::Vec3Array;
    v->resize( 8 );
    (*v)[0].set( -1.f, 1.f, 1.f);
    (*v)[1].set(1.f, 1.f, 1.f);
    (*v)[2].set(1.f, -1.f, 1.f );
    (*v)[3].set(-1.f, -1.f, 1.f );
    (*v)[4].set( -1.f, 1.f, -1.f );
    (*v)[5].set(1.f, 1.f, -1.f );
    (*v)[6].set(1.f, -1.f, -1.f );
    (*v)[7].set(-1.f, -1.f, -1.f );

    osg::Geometry* geom = new osg::Geometry;
    geom->setUseDisplayList( false );
    geom->setVertexArray( v );

    osg::Vec4Array* c = new osg::Vec4Array;
    // c->push_back( color );
    c->push_back( osg::Vec4(1.f,1.f,1.f,1.f));
    geom->setColorArray( c, osg::Array::BIND_OVERALL );

    GLushort idxLines[8] = {0, 3, 1,  2, 5, 6, 4, 7};
    GLushort idxLoops1[4] = {0, 4, 5, 1 };
    GLushort idxLoops2[4] = {3, 7, 6, 2 };

    geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINES, 8, idxLines ) );
    geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINE_LOOP, 4, idxLoops1 ) );
    geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINE_LOOP, 4, idxLoops2 ) );

    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( geom );

    geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF
                                         | osg::StateAttribute::PROTECTED );
    geode->getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    osg::PositionAttitudeTransform* transform = new osg::PositionAttitudeTransform;
    // transform->setScale(scaleFactor);
    transform->setScale(osg::Vec3d(4., 4., 4.) );

    transform->addChild(geode);
    return transform;
}

double OSGWidget::create_random_no_between_a_range(double min, double max)
{
    double number = (max - min) * ( (double)(rand()%100) / 100. ) + min;
    return number;
}

std::array<double,3> OSGWidget::create_a_random_velocity(std::array<double, 3> factor)
{
    std::array<double,3> vel = {create_random_no_between_a_range(0.2,2.)*factor[0],
                                create_random_no_between_a_range(0.2,2.)*factor[1],
                                create_random_no_between_a_range(0.4,2.)*factor[2]
                                };
    return vel;
}

osg::Vec4 OSGWidget::create_a_random_color( std::array<double,6> rangesRGB)
{
    std::vector<float> values = {
    (float)create_random_no_between_a_range(rangesRGB[0], rangesRGB[1]),
    (float)create_random_no_between_a_range(rangesRGB[2], rangesRGB[3]),
    (float)create_random_no_between_a_range(rangesRGB[4], rangesRGB[5]),
    };
    osg::Vec4 color(values[0], values[1], values[2], 1.f);
    return color;
}

ball* OSGWidget::create_sphere(osg::Group *root, std::array<double,3> pos, std::array<double,3> vel,
                                 osg::Vec4 Color, float radius)
{
     SpherePhysics * sp = new SpherePhysics(pos,vel,radius);
     graphicsRepresentation* gr = new graphicsRepresentation(root, sp, radius, Color);
     ball* sphere = new ball(sp, gr);
    return sphere;
}

void OSGWidget::create_timer_event()
{
    double framesPerSecond{30};
    double timeStep{1.0/framesPerSecond};
    double timerDurationInMilliSeconds{timeStep * 1000};
    mTimerId=startTimer(timerDurationInMilliSeconds);

}


