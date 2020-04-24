#pragma once

#include <QObject>

#if defined(Q_OS_WIN)
#include "KeySenders/mskeysender.hpp"
#elif defined(Q_OS_LINUX)

#if defined(USE_XLIB)
#include "KeySenders/xlibkeysender.hpp"
#else
#include "KeySenders/uinputkeysender.hpp"
#endif

#else
#include "KeySenders/mackeysender.hpp"
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
