#pragma once

//#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <winuser.h>

#include "basekeysender.hpp"

class MsKeySender : public BaseKeySender {
public:
    MsKeySender();
    ~MsKeySender() override;
    void keyDown(const unsigned int &iKey) override;
    void keyUp(const unsigned int &iKey) override;
};
