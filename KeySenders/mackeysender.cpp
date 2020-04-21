#include "mackeysender.hpp"

#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

MacKeySender::MacKeySender()
{
    CGEventRef CGEventCreateKeyboardEvent(CGEventSourceRef source, CGKeyCode virtualKey, bool keyDown);
}

MacKeySender::~MacKeySender()
{
}

void MacKeySender::keyDown(const unsigned int &iKey)
{
    CGEventRef mKeyEvent = CGEventCreateKeyboardEvent(NULL, iKey, true);
    CGEventPost(kCGSessionEventTap, mKeyEvent);
}

void MacKeySender::keyUp(const unsigned int &iKey)
{
    CGEventRef mKeyEvent = CGEventCreateKeyboardEvent(NULL, iKey, false);
    CGEventPost(kCGSessionEventTap, mKeyEvent);
}
