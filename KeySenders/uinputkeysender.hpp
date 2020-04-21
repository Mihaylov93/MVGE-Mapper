#pragma once

#include "basekeysender.hpp"

class UinputKeySender : public BaseKeySender {
public:
    UinputKeySender();
    ~UinputKeySender() override;
    void keyDown(const unsigned int &iKey) override;
    void keyUp(const unsigned int &iKey) override;

private:
    int fd;
    std::set<unsigned int> mEnabledKeys;

    void emitEvent(int fd, int type, int code, int val);
};
