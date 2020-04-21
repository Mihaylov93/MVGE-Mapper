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
    execute_process(COMMAND bash -c "loginctl show-session $(loginctl | grep $(whoami) | awk '{print $1}') -p Type"
        OUTPUT_VARIABLE DISPLAY_SERVER)

    message(STATUS "Configuring for display server: " ${DISPLAY_SERVER})
    if (${DISPLAY_SERVER} MATCHES "Type=x11")
       set(USE_XLIB TRUE)
    else()
       set(USE_XLIB FALSE)
    endif()

    if(USE_XLIB) # Set this to FALSE to force disable use of xlib
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
          resources.qrc

          KeySenders/basekeysender.cpp
          KeySenders/basekeysender.hpp
          KeySenders/xlibkeysender.cpp
          KeySenders/xlibkeysender.hpp

          mainwindow.ui
        )
        target_compile_definitions(MVGE_Mapper PUBLIC USE_XLIB)
        target_link_libraries(MVGE_Mapper PRIVATE Qt5::Widgets Qt5::Network ${X11_LIBRARIES} Xtst)
    else()
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
          resources.qrc

          KeySenders/basekeysender.cpp
          KeySenders/basekeysender.hpp
          KeySenders/uinputkeysender.cpp
          KeySenders/uinputkeysender.hpp

          mainwindow.ui

        )
        target_link_libraries(MVGE_Mapper PRIVATE Qt5::Widgets Qt5::Network)
    endif()

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
      KeySenders/basekeysender.cpp
      KeySenders/basekeysender.hpp
      KeySenders/mskeysender.cpp
      KeySenders/mskeysender.hpp
    )
    target_link_libraries(MVGE_Mapper PRIVATE Qt5::Widgets Qt5::Network)
endif()
