#include "keysender.hpp"
#include <QKeyEvent>
#include <QMetaEnum>
#include <QDebug>

#if defined(Q_OS_LINUX)
#include "x11sender.hpp"
#endif

#define KEY_PRESSED '1'
#define KEY_RELEASED '0'

KeySender::KeySender(QObject *parent) : QObject(parent)
{
#if defined(Q_OS_LINUX)
    _x11Sender = new X11Sender();
#endif
}

KeySender::~KeySender()
{
#if defined(Q_OS_LINUX)
    delete _x11Sender;
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
        _x11Sender->keyDown(iKeyValue);
    } else if (iState == KEY_RELEASED) {
        _x11Sender->keyUp(iKeyValue);
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
