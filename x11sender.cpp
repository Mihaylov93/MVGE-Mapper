#include "x11sender.hpp"

#include <linux/input.h>
#include <linux/uinput.h>
#include <fcntl.h>


#include <stdio.h>
#include <string.h>
#include <unistd.h>





X11Sender::X11Sender()
{
    struct uinput_setup usetup;

    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);


    /*
     * The ioctls below will enable the device that is about to be
     * created, to pass key events, in this case the space key.
     */
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, KEY_SPACE);

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234; /* sample vendor */
    usetup.id.product = 0x5678; /* sample product */
    strcpy(usetup.name, "Example device");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);
    sleep(1);

}

X11Sender::~X11Sender()
{
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
}

void X11Sender::emitEvent(int fd, int type, int code, int val)
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

void X11Sender::keyDown(const unsigned int &iKey)
{




    /* Key press, report the event*/
    emitEvent(fd, EV_KEY, KEY_SPACE, 1);
    emitEvent(fd, EV_SYN, SYN_REPORT, 0);

}

void X11Sender::keyUp(const unsigned int &iKey)
{
       /* Key press, report the event*/
       emitEvent(fd, EV_KEY, KEY_SPACE, 0);
       emitEvent(fd, EV_SYN, SYN_REPORT, 0);
}
