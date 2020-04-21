#pragma once

#include "basekeysender.hpp"
#include <set>

class UinputKeySender : public BaseKeySender {
public:
    UinputKeySender();
    ~UinputKeySender() override;
    void keyDown(const unsigned int &iKey) override;
    void keyUp(const unsigned int &iKey) override;

private:
    int _device;
    std::set<unsigned int> mEnabledKeys;

    void emitEvent(const int &iDevice, const int &iType, const int &iCode, const int &iVal);
};
