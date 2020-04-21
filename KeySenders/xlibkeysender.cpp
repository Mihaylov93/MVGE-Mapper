#include "xlibkeysender.hpp"

#include "X11/Xlib.h"
#include "X11/extensions/XTest.h"
#include "X11/keysym.h"
#include "X11/keysymdef.h"

XlibKeysender::XlibKeysender()
{
    _display = XOpenDisplay(nullptr);
}

XlibKeysender::~XlibKeysender()
{
    XCloseDisplay(_display);
}

void XlibKeysender::keyDown(const unsigned int &iKey)
{
    XTestFakeKeyEvent(_display, iKey, True, 0);
    XFlush(_display);
}

void XlibKeysender::keyUp(const unsigned int &iKey)
{
    XTestFakeKeyEvent(_display, iKey, False, 0);
    XFlush(_display);
}
