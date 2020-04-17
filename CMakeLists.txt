cmake_minimum_required(VERSION 3.5)

project(MVGE_Mapper LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

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
