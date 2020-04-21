#pragma once
#include "basekeysender.hpp"

#include "X11/Xlib.h"
#include "X11/extensions/XTest.h"

class XlibKeysender : public BaseKeySender {
public:
    XlibKeysender();
    ~XlibKeysender() override;
    void keyDown(const unsigned int &iKey) override;
    void keyUp(const unsigned int &iKey) override;

private:
    Display *_display;
};
