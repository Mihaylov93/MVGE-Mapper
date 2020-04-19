#pragma once

#include <QObject>

#if defined(Q_OS_WIN)
//#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <winuser.h>
#endif

#if defined(Q_OS_MAC)
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#endif
class X11Sender;
class KeySender : public QObject {
    Q_OBJECT
public:
    explicit KeySender(QObject *parent = nullptr);
    ~KeySender();
public slots:
    void sendKeyPress(const quint32 &iKeyValue, const QString &iState);

#if defined(Q_OS_LINUX)
private:
    X11Sender *_x11Sender;
#endif
};
