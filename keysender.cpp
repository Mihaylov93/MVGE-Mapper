#include "keysender.hpp"
#include <QKeyEvent>
#include <QMetaEnum>
#include <QDebug>

#define KEY_PRESSED '1'
#define KEY_RELEASED '0'

KeySender::KeySender(QObject *parent) : QObject(parent)
{
#if defined(Q_OS_LINUX)
    display = XOpenDisplay(NULL);
#endif
}

KeySender::~KeySender()
{
#if defined(Q_OS_LINUX)
    XCloseDisplay(_display);
#endif
}

void KeySender::sendKeyPress(const quint32 &iKeyValue, const QString &iState)
{
#if defined(Q_OS_WIN)
    if (iState == KEY_PRESSED)
        keybd_event(static_cast<BYTE>(iKeyValue), 0, 0, 0);
    else if (iState == KEY_RELEASED)
        keybd_event(static_cast<BYTE>(iKeyValue), 0, KEYEVENTF_KEYUP, 0);
#endif

#if defined(Q_OS_LINUX)
    if (iState == KEY_PRESSED) {
        XTestFakeKeyEvent(_display, iKeyValue, True, 0);
        XFlush(_display);
    } else if (iState == KEY_RELEASED) {
        XTestFakeKeyEvent(_display, iKeyValue, False, 0);
        XFlush(_display);
    }
#endif

#if defined(Q_OS_MAC)
    CGEventRef CGEventCreateKeyboardEvent(CGEventSourceRef source, CGKeyCode virtualKey, bool keyDown);

    CGEventRef mKeyEvent;
    if (iState == KEY_PRESSED)
        mKeyEvent = CGEventCreateKeyboardEvent(NULL, iKeyValue, true);
    else
        mKeyEvent = CGEventCreateKeyboardEvent(NULL, iKeyValue, false);

    CGEventPost(kCGSessionEventTap, mKeyEvent);
#endif
}
