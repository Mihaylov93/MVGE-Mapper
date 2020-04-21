#include "uinputkeysender.hpp"

#include <linux/input.h>
#include <linux/uinput.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <algorithm>

UinputKeySender::UinputKeySender()
{
    struct uinput_setup usetup;

    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234;  /* sample vendor */
    usetup.id.product = 0x5678; /* sample product */
    strcpy(usetup.name, "Example device");

    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_EVBIT, EV_SYN);

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);
    sleep(1);
}

UinputKeySender::~UinputKeySender()
{
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
}

void UinputKeySender::keyDown(const unsigned int &iKey)
{
    const unsigned int mKeyCode = iKey - 8;
    if (mEnabledKeys.find(mKeyCode) == mEnabledKeys.end()) {

        ioctl(fd, UI_SET_KEYBIT, mKeyCode);
        mEnabledKeys.insert(mKeyCode);
    }

    /* Key press, report the event*/
    emitEvent(fd, EV_KEY, mKeyCode, 1);
    emitEvent(fd, EV_SYN, SYN_REPORT, 0);
}

void UinputKeySender::keyUp(const unsigned int &iKey)
{
    const unsigned int mKeyCode = iKey - 8;
    emitEvent(fd, EV_KEY, mKeyCode, 0);
    emitEvent(fd, EV_SYN, SYN_REPORT, 0);
}

void UinputKeySender::emitEvent(int fd, int type, int code, int val)
{
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    write(fd, &ie, sizeof(ie));
}
