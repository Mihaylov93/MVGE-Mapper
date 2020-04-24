#pragma once

#include "basekeysender.hpp"

class UinputKeySender : public BaseKeySender {
public:
    UinputKeySender();
    ~UinputKeySender() override;
    void keyDown(const unsigned int &iKey) override;
    void keyUp(const unsigned int &iKey) override;

private:
    int _device;

    void emitEvent(const int &iDevice, const int &iType, const int &iCode, const int &iVal);
    void enableKeyEvents();
};
