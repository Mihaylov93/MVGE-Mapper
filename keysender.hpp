#pragma once

#include <QObject>

#if defined(Q_OS_WIN)
//#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <winuser.h>
#endif

#if defined(Q_OS_LINUX)
// http://bharathi.posterous.com/x11-fake-key-event-generation-using-xtest-ext
// http://www.doctort.org/adam/nerd-notes/x11-fake-keypress-event.html
#include "X11/Xlib.h"
#include "X11/keysym.h"
#include "X11/keysymdef.h"
#include "X11/extensions/XTest.h"
#endif

#if defined(Q_OS_MAC)
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#endif

class KeySender : public QObject {
    Q_OBJECT
public:
    explicit KeySender(QObject *parent = nullptr);
    ~KeySender();
public slots:
    void sendKeyPress(const quint32 &iKeyValue, const QString &iState);

protected:
    BYTE getNativeKeyCode(const int &iKey);
};
