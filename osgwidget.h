#ifndef OSGWIDGET_H
#define OSGWIDGET_H

#include <QOpenGLWidget>

#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>

#include "spherephysics.h"
#include<spherecallback.h>

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
  osg::PositionAttitudeTransform * create_wireframe_tetrahedron(osg::Vec4 &color, osg::Vec3d &scaleFactor);
  

private:
  virtual void on_resize( int width, int height );
  osgGA::EventQueue* getEventQueue() const;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
  osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
  osg::ref_ptr<osgViewer::View> mView;
  osg::ref_ptr<osg::Group> mRoot;
  int mTimerId{0};
};

#endif

