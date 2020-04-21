#pragma once
#include "basekeysender.hpp"

struct _XDisplay;
class XlibKeysender : public BaseKeySender {
public:
    XlibKeysender();
    ~XlibKeysender() override;
    void keyDown(const unsigned int &iKey) override;
    void keyUp(const unsigned int &iKey) override;

private:
    _XDisplay *_display;
};
