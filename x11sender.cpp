#include "x11sender.hpp"


#include "X11/keysym.h"
#include "X11/keysymdef.h"

X11Sender::X11Sender()
{
    _display = XOpenDisplay(nullptr);
}

X11Sender::~X11Sender()
{
    XCloseDisplay(_display);
}

void X11Sender::keyDown(const unsigned int &iKey)
{
    XTestFakeKeyEvent(_display, iKey, True, 0);
    XFlush(_display);
}

void X11Sender::keyUp(const unsigned int &iKey)
{
    XTestFakeKeyEvent(_display, iKey, False, 0);
    XFlush(_display);
}
