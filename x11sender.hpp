#pragma once


class X11Sender
{
public:
    explicit X11Sender();
    ~X11Sender();

    void keyDown(const unsigned int &iKey);
    void keyUp(const unsigned int &iKey);
    void emitEvent(int,int,int,int);
private:
    int fd;
};
