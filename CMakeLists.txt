cmake_minimum_required(VERSION 3.4)
project(QtGUI)

FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindowform.ui
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Gui
)
