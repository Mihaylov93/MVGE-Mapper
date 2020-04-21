#pragma once

#include "basekeysender.hpp"

// Just a stub, untested. Most likely wont compile
class MacKeySender : public BaseKeySender {
public:
    MacKeySender();
    ~MacKeySender() override;
    void keyDown(const unsigned int &iKey) override;
    void keyUp(const unsigned int &iKey) override;
};
