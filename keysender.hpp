#pragma once

#include <QObject>

#if defined(Q_OS_WIN)
#include "KeySenders/mskeysender.hpp"
#elif defined(Q_OS_LINUX)

#if defined(USE_XLIB)
#include "KeySenders/xlibkeysender.h"
#elif
#include "KeySenders/uinputkeysender.h"
#endif

#elif defined(Q_OS_MAC)
#include "KeySenders/mackeysender.h"
#endif

class KeySender : public QObject {
    Q_OBJECT
public:
    explicit KeySender(QObject *parent = nullptr);
    ~KeySender();
public slots:
    void sendKeyPress(const quint32 &iKeyValue, const QString &iState);

private:
    BaseKeySender *_keySender;
};
