#include "mskeysender.hpp"

MsKeySender::MsKeySender()
{
}

MsKeySender::~MsKeySender()
{
}

void MsKeySender::keyDown(const unsigned int &iKey)
{
    keybd_event(static_cast<BYTE>(iKey), 0, 0, 0);
}

void MsKeySender::keyUp(const unsigned int &iKey)
{
    keybd_event(static_cast<BYTE>(iKey), 0, KEYEVENTF_KEYUP, 0);
}
