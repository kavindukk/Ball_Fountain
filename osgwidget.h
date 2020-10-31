#ifndef OSGWIDGET_H
#define OSGWIDGET_H

#include <QOpenGLWidget>
#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <QPainter>

#include "spherephysics.h"
#include <spherecallback.h>
#include "graphicsrepresentation.h"
#include "ball.h"

#include <vector>
#include <random>

class OSGWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  OSGWidget( QWidget* parent = 0,
             Qt::WindowFlags f = 0 );

  virtual ~OSGWidget();
protected:
  virtual void paintEvent( QPaintEvent* paintEvent );
  virtual void paintGL();
  virtual void resizeGL( int width, int height );

  void timerEvent(QTimerEvent *); 

  void createCamera(osgViewer::View *mView);
  void createManipulator(osgViewer::View *mView);  
  void createViewer(osgViewer::CompositeViewer *mViewer, osgViewer::View *mView);
  void create_timer_event();  
  osg::Geode* createSpheregeode();
  osg::PositionAttitudeTransform* createTransformation(osg::Geode* geode, SpherePhysics* _sp);  
  // osg::PositionAttitudeTransform * create_wireframe_tetrahedron(osg::Vec4 &color, osg::Vec3d &scaleFactor);
  osg::PositionAttitudeTransform * create_wireframe_tetrahedron();
  ball* create_sphere(osg::Group* root, std::array<double,3> pos, std::array<double,3> vel,
                     osg::Vec4 Color, float radius );
  double create_random_no_between_a_range(double min, double max);
  osg::Vec4 create_a_random_color(std::array<double,6> rangesRGB={0.,1.,0.,1.,0.,1.});
  std::array<double,3> create_a_random_velocity(std::array<double, 3> factor = {10.,10.,10.});
  

private:
  virtual void on_resize( int width, int height );
  osgGA::EventQueue* getEventQueue() const;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
  osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
  osg::ref_ptr<osgViewer::View> mView;
  osg::ref_ptr<osg::Group> mRoot;
  int mTimerId{0};
  SpherePhysics* sp1;
  SpherePhysics* sp2;
  SpherePhysics* sp3;
  std::vector<ball*> ballList;
};

#endif

