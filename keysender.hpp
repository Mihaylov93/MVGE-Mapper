#pragma once

#include <QObject>
#if defined(Q_OS_WIN)

//#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <winuser.h>

class KeySender : public QObject {
    Q_OBJECT
public:
    explicit KeySender(QObject *parent = nullptr);

public slots:
    void sendKeyPress(const int &iKeyValue, const QString &iState);

protected:
    BYTE getNativeKeyCode(const int &iKey);
};

#endif
