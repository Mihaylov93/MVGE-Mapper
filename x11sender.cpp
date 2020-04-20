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
    //http://t-sato.in.coocan.jp/xvkbd/events.html
    Window mRoot, mChild, mWindow;
    int mRoot_x, mRoot_y, mX, mY;
    unsigned int mMask;
    int mRevert_to;

    XGetInputFocus(_display, &mWindow, &mRevert_to);

    XQueryPointer(_display, mWindow,&mRoot, &mChild, &mRoot_x, &mRoot_y, &mX, &mY, &mMask);
    XWarpPointer(_display, None, mWindow, 0, 0, 0, 0, 1, 1);
    XFlush(_display);

    XTestFakeKeyEvent(_display, iKey, True, 0);
    XFlush(_display);

    XWarpPointer(_display, None, mRoot, 0, 0, 0, 0, mRoot_x, mRoot_y);
    XFlush(_display);
}

void X11Sender::keyUp(const unsigned int &iKey)
{
    Window mRoot, mChild, mWindow;
    int mRoot_x, mRoot_y, mX, mY;
    unsigned int mMask;
    int mRevert_to;

    XGetInputFocus(_display, &mWindow, &mRevert_to);

    XQueryPointer(_display, mWindow,&mRoot, &mChild, &mRoot_x, &mRoot_y, &mX, &mY, &mMask);
    XWarpPointer(_display, None, mWindow, 0, 0, 0, 0, 1, 1);
    XFlush(_display);

    XTestFakeKeyEvent(_display, iKey, False, 0);
    XFlush(_display);

    XWarpPointer(_display, None, mRoot, 0, 0, 0, 0, mRoot_x, mRoot_y);
    XFlush(_display);
}
