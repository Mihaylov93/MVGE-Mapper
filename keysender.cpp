#include "keysender.hpp"
#include <QKeyEvent>
#include <QMetaEnum>
#include <QDebug>

#define KEY_PRESSED '1'
#define KEY_RELEASED '0'

KeySender::KeySender(QObject *parent) : QObject(parent)
{
#if defined(Q_OS_WIN)
    _keySender = new MsKeySender();
#elif defined(Q_OS_LINUX)
#if defined(USE_XLIB)
    _keySender = new XlibKeysender();
#else
    _keySender = new UinputKeySender();
#endif
#else // Q_OS_MAC
    _keySender = new MacKeySender();
#endif
}

KeySender::~KeySender()
{
    delete _keySender;
}

void KeySender::sendKeyPress(const quint32 &iKeyValue, const QString &iState)
{
    if (iState == KEY_PRESSED)
        _keySender->keyDown(iKeyValue);
    else if (iState == KEY_RELEASED)
        _keySender->keyUp(iKeyValue);
}
