#include "uinputkeysender.hpp"

#include <linux/input.h>
#include <linux/uinput.h>

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>

// https://www.kernel.org/doc/html/v4.12/input/uinput.html

UinputKeySender::UinputKeySender()
{
    struct uinput_setup mUsetup;

    _device = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    memset(&mUsetup, 0, sizeof(mUsetup));
    mUsetup.id.bustype = BUS_USB;
    mUsetup.id.vendor = 0x1234;  // sample vendor
    mUsetup.id.product = 0x5678; // sample product
    strcpy(mUsetup.name, "MVGE Kbd Dev");

    ioctl(_device, UI_SET_EVBIT, EV_KEY);
    ioctl(_device, UI_SET_EVBIT, EV_SYN);

    ioctl(_device, UI_DEV_SETUP, &mUsetup);
    ioctl(_device, UI_DEV_CREATE);
    sleep(1);
}

UinputKeySender::~UinputKeySender()
{
    ioctl(_device, UI_DEV_DESTROY);
    close(_device);
}

void UinputKeySender::keyDown(const unsigned int &iKey)
{
    // iKey is X keycode, ioctl expects Linux-base-system keycodes
    // Key A is iKey=38, KEY_A is 30 in input-event-codes.h

    const unsigned int mKeyCode = iKey - 8;
    if (mEnabledKeys.find(mKeyCode) == mEnabledKeys.end()) {

        ioctl(_device, UI_SET_KEYBIT, mKeyCode);
        mEnabledKeys.insert(mKeyCode);
    }
    // Key press, report the event
    emitEvent(_device, EV_KEY, static_cast<int>(mKeyCode), 1);
    emitEvent(_device, EV_SYN, SYN_REPORT, 0);
}

void UinputKeySender::keyUp(const unsigned int &iKey)
{
    const unsigned int mKeyCode = iKey - 8;
    emitEvent(_device, EV_KEY, static_cast<int>(mKeyCode), 0);
    emitEvent(_device, EV_SYN, SYN_REPORT, 0);
}

void UinputKeySender::emitEvent(const int &iDevice, const int &iType, const int &iCode, const int &iVal)
{
    struct input_event ie;

    ie.type = static_cast<__u16>(iType);
    ie.code = static_cast<__u16>(iCode);
    ie.value = iVal;
    // timestamp values below are ignored.
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    write(iDevice, &ie, sizeof(ie));
}
