#include "keysender.hpp"
#include <QKeyEvent>
#include <QMetaEnum>
#include <QDebug>

#define KEY_PRESSED '1'
#define KEY_RELEASED '0'

KeySender::KeySender(QObject *parent) : QObject(parent)
{
}

void KeySender::sendKeyPress(const int &iKeyValue, const QString &iState)
{
    const BYTE mVirtualKey = getNativeKeyCode(iKeyValue);

    if (iState == KEY_PRESSED)
        keybd_event(mVirtualKey, 0, 0, 0);
    else if (iState == KEY_RELEASED)
        keybd_event(mVirtualKey, 0, KEYEVENTF_KEYUP, 0);
}

// https://docs.microsoft.com/es-es/windows/win32/inputdev/virtual-key-codes
BYTE KeySender::getNativeKeyCode(const int &iKey)
{
    switch (iKey) {
        case Qt::Key_Escape:
            return VK_ESCAPE;
        case Qt::Key_Tab:
            Q_FALLTHROUGH();
        case Qt::Key_Backtab:
            return VK_TAB;
        case Qt::Key_Backspace:
            return VK_BACK;
        case Qt::Key_Return:
            Q_FALLTHROUGH();
        case Qt::Key_Enter:
            return VK_RETURN;
        case Qt::Key_Insert:
            return VK_INSERT;
        case Qt::Key_Delete:
            return VK_DELETE;
        case Qt::Key_Pause:
            return VK_PAUSE;
        case Qt::Key_Print:
            return VK_PRINT;
        case Qt::Key_Clear:
            return VK_CLEAR;
        case Qt::Key_Home:
            return VK_HOME;
        case Qt::Key_End:
            return VK_END;
        case Qt::Key_Left:
            return VK_LEFT;
        case Qt::Key_Up:
            return VK_UP;
        case Qt::Key_Right:
            return VK_RIGHT;
        case Qt::Key_Down:
            return VK_DOWN;
        case Qt::Key_PageUp:
            return VK_PRIOR;
        case Qt::Key_PageDown:
            return VK_NEXT;
        case Qt::Key_F1:
            return VK_F1;
        case Qt::Key_F2:
            return VK_F2;
        case Qt::Key_F3:
            return VK_F3;
        case Qt::Key_F4:
            return VK_F4;
        case Qt::Key_F5:
            return VK_F5;
        case Qt::Key_F6:
            return VK_F6;
        case Qt::Key_F7:
            return VK_F7;
        case Qt::Key_F8:
            return VK_F8;
        case Qt::Key_F9:
            return VK_F9;
        case Qt::Key_F10:
            return VK_F10;
        case Qt::Key_F11:
            return VK_F11;
        case Qt::Key_F12:
            return VK_F12;
        case Qt::Key_F13:
            return VK_F13;
        case Qt::Key_F14:
            return VK_F14;
        case Qt::Key_F15:
            return VK_F15;
        case Qt::Key_F16:
            return VK_F16;
        case Qt::Key_F17:
            return VK_F17;
        case Qt::Key_F18:
            return VK_F18;
        case Qt::Key_F19:
            return VK_F19;
        case Qt::Key_F20:
            return VK_F20;
        case Qt::Key_F21:
            return VK_F21;
        case Qt::Key_F22:
            return VK_F22;
        case Qt::Key_F23:
            return VK_F23;
        case Qt::Key_F24:
            return VK_F24;
        case Qt::Key_Space:
            return VK_SPACE;
        case Qt::Key_Asterisk:
            return VK_MULTIPLY;
        case Qt::Key_Plus:
            return VK_ADD;
        case Qt::Key_Comma:
            return VK_SEPARATOR;
        case Qt::Key_Minus:
            return VK_SUBTRACT;
        case Qt::Key_Slash:
            return VK_DIVIDE;
        case Qt::Key_MediaNext:
            return VK_MEDIA_NEXT_TRACK;
        case Qt::Key_MediaPrevious:
            return VK_MEDIA_PREV_TRACK;
        case Qt::Key_MediaPlay:
            return VK_MEDIA_PLAY_PAUSE;
        case Qt::Key_MediaStop:
            return VK_MEDIA_STOP;
            // case Qt::Key_MediaLast:
            // case Qt::Key_MediaRecord:
        case Qt::Key_VolumeDown:
            return VK_VOLUME_DOWN;
        case Qt::Key_VolumeUp:
            return VK_VOLUME_UP;
        case Qt::Key_VolumeMute:
            return VK_VOLUME_MUTE;
        case Qt::Key_Meta:
            return VK_LWIN;

            // numbers
        case Qt::Key_0:
            Q_FALLTHROUGH();
        case Qt::Key_1:
            Q_FALLTHROUGH();
        case Qt::Key_2:
            Q_FALLTHROUGH();
        case Qt::Key_3:
            Q_FALLTHROUGH();
        case Qt::Key_4:
            Q_FALLTHROUGH();
        case Qt::Key_5:
            Q_FALLTHROUGH();
        case Qt::Key_6:
            Q_FALLTHROUGH();
        case Qt::Key_7:
            Q_FALLTHROUGH();
        case Qt::Key_8:
            Q_FALLTHROUGH();
        case Qt::Key_9:
            return static_cast<BYTE>(iKey);

            // letters
        case Qt::Key_A:
            Q_FALLTHROUGH();
        case Qt::Key_B:
            Q_FALLTHROUGH();
        case Qt::Key_C:
            Q_FALLTHROUGH();
        case Qt::Key_D:
            Q_FALLTHROUGH();
        case Qt::Key_E:
            Q_FALLTHROUGH();
        case Qt::Key_F:
            Q_FALLTHROUGH();
        case Qt::Key_G:
            Q_FALLTHROUGH();
        case Qt::Key_H:
            Q_FALLTHROUGH();
        case Qt::Key_I:
            Q_FALLTHROUGH();
        case Qt::Key_J:
            Q_FALLTHROUGH();
        case Qt::Key_K:
            Q_FALLTHROUGH();
        case Qt::Key_L:
            Q_FALLTHROUGH();
        case Qt::Key_M:
            Q_FALLTHROUGH();
        case Qt::Key_N:
            Q_FALLTHROUGH();
        case Qt::Key_O:
            Q_FALLTHROUGH();
        case Qt::Key_P:
            Q_FALLTHROUGH();
        case Qt::Key_Q:
            Q_FALLTHROUGH();
        case Qt::Key_R:
            Q_FALLTHROUGH();
        case Qt::Key_S:
            Q_FALLTHROUGH();
        case Qt::Key_T:
            Q_FALLTHROUGH();
        case Qt::Key_U:
            Q_FALLTHROUGH();
        case Qt::Key_V:
            Q_FALLTHROUGH();
        case Qt::Key_W:
            Q_FALLTHROUGH();
        case Qt::Key_X:
            Q_FALLTHROUGH();
        case Qt::Key_Y:
            Q_FALLTHROUGH();
        case Qt::Key_Z:
            return static_cast<BYTE>(iKey);

        default:
            return 0;
    }
}
