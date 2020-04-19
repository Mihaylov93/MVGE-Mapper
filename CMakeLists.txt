cmake_minimum_required(VERSION 3.5)

project(MVGE_Mapper LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

if(LINUX)
    find_package(X11 REQUIRED)

    include_directories(${X11_INCLUDE_DIR})
    link_directories(${X11_LIBRARIES})

    add_executable(MVGE_Mapper
      main.cpp
      mainwindow.cpp
      mainwindow.hpp
      udplistener.cpp
      udplistener.hpp
      keysender.cpp
      keysender.hpp
      setkeydialog.cpp
      setkeydialog.hpp
      x11sender.cpp
      x11sender.hpp
      resources.qrc
      mainwindow.ui
    )

    target_link_libraries(MVGE_Mapper PRIVATE Qt5::Widgets Qt5::Network ${X11_LIBRARIES} Xtst)
else()
    add_executable(MVGE_Mapper WIN32
      main.cpp
      mainwindow.cpp
      mainwindow.hpp
      udplistener.cpp
      udplistener.hpp
      keysender.cpp
      keysender.hpp
      setkeydialog.cpp
      setkeydialog.hpp
      resources.qrc
      mainwindow.ui
    )
    target_link_libraries(MVGE_Mapper PRIVATE Qt5::Widgets Qt5::Network)
endif()
