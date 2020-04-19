#pragma once
#include "X11/Xlib.h"

#include "X11/extensions/XTest.h"

class X11Sender
{
public:
    explicit X11Sender();
    ~X11Sender();

    void keyDown(const unsigned int &iKey);
    void keyUp(const unsigned int &iKey);
private:
    Display *_display;
};
