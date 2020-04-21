#pragma once

class BaseKeySender {
public:
    BaseKeySender() = default;
    virtual ~BaseKeySender();
    virtual void keyDown(const unsigned int &iKey) = 0;
    virtual void keyUp(const unsigned int &iKey) = 0;
};
