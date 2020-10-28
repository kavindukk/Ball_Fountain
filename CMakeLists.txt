cmake_minimum_required(VERSION 3.4)
project(DancingWaterFountain)

FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osgText)

FIND_PACKAGE(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

INCLUDE_DIRECTORIES( ${OPENSCENEGRAPH_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

add_library( physics STATIC
    spherephysics.h
    spherephysics.cpp
)

add_library( graphics STATIC
    graphicsrepresentation.h
    graphicsrepresentation.cpp
)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindowform.ui
    osgwidget.cpp
    osgwidget.h
    spherecallback.cpp 
    spherecallback.h
    unitTest.cpp 
)

target_link_libraries(${PROJECT_NAME}
    ${OPENSCENEGRAPH_LIBRARIES}
    Qt5::Widgets
    Qt5::Gui
    physics
    graphics
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
)
