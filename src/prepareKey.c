#include "prepareKey.h"
#include <linux/input.h>
#include <stdbool.h>

char *prepareKey(__u16 code, __s32 value, bool *isShiftActive, bool *isCtrlActive, bool *isCapsLockActive) {
    switch (code) {
    case KEY_LEFTSHIFT:
        if (value == 0) {
            *isShiftActive = false;
            return "</Left Shift>";
        } else if (value == 1) {
            *isShiftActive = true;
            return "<Left Shift>";
        }
        *isShiftActive = true;
        return "";

    case KEY_RIGHTSHIFT:
        if (value == 0) {
            *isShiftActive = false;
            return "</Right Shift>";
        } else if (value == 1) {
            *isShiftActive = true;
            return "<Right Shift>";
        }
        *isShiftActive = true;
        return "";

    case KEY_LEFTCTRL:
        if (value == 0) {
            *isCtrlActive = false;
            return "</Left Ctrl>";
        } else if (value == 1) {
            *isCtrlActive = true;
            return "<Left Ctrl>";
        }
        *isCtrlActive = true;
        return "";

    case KEY_RIGHTCTRL:
        if (value == 0) {
            *isCtrlActive = false;
            return "</Right Ctrl>";
        } else if (value == 1) {
            *isCtrlActive = true;
            return "<Right Ctrl>";
        }
        *isCtrlActive = true;
        return "";

    case KEY_ENTER:
        if (value != 1) {
            return "<Enter />";
        }
        return "";

    case KEY_BACKSPACE:
        if (value != 1) {
            return "<Backspace />";
        }
        return "";

    case KEY_ESC:
        if (value != 1) {
            return "<Escape />";
        }
        return "";

    case KEY_TAB:
        if (value != 1) {
            return "Tab />";
        }
        return "";

    case KEY_DELETE:
        if (value != 1) {
            return "<Delete />";
        }
        return "";

    case KEY_F1:
        if (value != 1) {
            return "<F1 />";
        }
        return "";

    case KEY_F2:
        if (value != 1) {
            return "<F2 />";
        }
        return "";

    case KEY_F3:
        if (value != 1) {
            return "<F3 />";
        }
        return "";

    case KEY_F4:
        if (value != 1) {
            return "<F4 />";
        }
        return "";

    case KEY_F5:
        if (value != 1) {
            return "<F5 />";
        }
        return "";

    case KEY_F6:
        if (value != 1) {
            return "<F6 />";
        }
        return "";

    case KEY_F7:
        if (value != 1) {
            return "<F7 />";
        }
        return "";

    case KEY_F8:
        if (value != 1) {
            return "<F8 />";
        }
        return "";

    case KEY_F9:
        if (value != 1) {
            return "<F9 />";
        }
        return "";

    case KEY_F10:
        if (value != 1) {
            return "<F10 />";
        }
        return "";

    case KEY_F11:
        if (value != 1) {
            return "<F11 />";
        }
        return "";

    case KEY_F12:
        if (value != 1) {
            return "<F12 />";
        }
        return "";

    case KEY_F13:
        if (value != 1) {
            return "<F13 />";
        }
        return "";

    case KEY_F14:
        if (value != 1) {
            return "<F14 />";
        }
        return "";

    case KEY_F15:
        if (value != 1) {
            return "<F15 />";
        }
        return "";

    case KEY_F16:
        if (value != 1) {
            return "<F16 />";
        }
        return "";

    case KEY_F17:
        if (value != 1) {
            return "<F17 />";
        }
        return "";

    case KEY_F18:
        if (value != 1) {
            return "<F18 />";
        }
        return "";

    case KEY_F19:
        if (value != 1) {
            return "<F19 />";
        }
        return "";

    case KEY_F20:
        if (value != 1) {
            return "<F20 />";
        }
        return "";

    case KEY_F21:
        if (value != 1) {
            return "<F21 />";
        }
        return "";

    case KEY_F22:
        if (value != 1) {
            return "<F22 />";
        }
        return "";

    case KEY_F23:
        if (value != 1) {
            return "<F23 />";
        }
        return "";

    case KEY_F24:
        if (value != 1) {
            return "<F24 />";
        }
        return "";

    case KEY_FN:
        if (value == 0) {
            return "</Fn>";
        } else if (value == 1) {
            return "<Fn>";
        }
        return "";

    case KEY_CAPSLOCK:
        if (value != 1) {
            if (!*isCapsLockActive) {
                *isCapsLockActive = true;
                return "<Caps Lock>";
            } else {
                *isCapsLockActive = false;
                return "</Caps Lock>";
            }
        }
        return "";

    case KEY_LEFTMETA:
        if (value == 0) {
            return "</Left Meta>";
        } else if (value == 1) {
            return "<Left Meta>";
        }
        return "";

    case KEY_RIGHTMETA:
        if (value == 0) {
            return "</Right Meta>";
        } else if (value == 1) {
            return "<Right Meta>";
        }
        return "";

    case KEY_SPACE:
        if (value != 1) {
            return "<Space />";
        }
        return "";

    case KEY_LEFT:
        if (value != 0) {
            return "<Left Arrow />";
        }
        return "";

    case KEY_RIGHT:
        if (value != 0) {
            return "<Right Arrow />";
        }
        return "";

    case KEY_UP:
        if (value != 0) {
            return "<Up Arrow />";
        }
        return "";

    case KEY_DOWN:
        if (value != 0) {
            return "<Down Arrow />";
        }
        return "";

    case KEY_END:
        if (value != 0) {
            return "<End />";
        }
        return "";

    case KEY_HOME:
        if (value != 0) {
            return "<Home />";
        }
        return "";

    case KEY_LEFTALT:
        if (value == 0) {
            return "</Left Alt>";
        } else if (value == 1) {
            return "<Left Alt>";
        }
        return "";

    case KEY_RIGHTALT:
        if (value == 0) {
            return "</Right Alt>";
        } else if (value == 1) {
            return "<Left Alt>";
        }
        return "";

    case KEY_PAGEUP:
        if (value != 0) {
            return "<Page Up />";
        }
        return "";

    case KEY_PAGEDOWN:
        if (value != 0) {
            return "<Page Down />";
        }
        return "";

    case KEY_INSERT:
        if (value != 0) {
            return "<Insert />";
        }
        return "";

    default:
        break;
    }

    if (value == 0) {
        return "";
    }

    switch (code) {
    case KEY_A:
        if (*isShiftActive || *isCapsLockActive)
            return "A";
        else
            return "a";

    case KEY_B:
        if (*isShiftActive || *isCapsLockActive)
            return "B";
        else
            return "b";

    case KEY_C:
        if (*isShiftActive || *isCapsLockActive)
            return "C";
        else
            return "c";

    case KEY_D:
        if (*isShiftActive || *isCapsLockActive)
            return "D";
        else
            return "d";

    case KEY_E:
        if (*isShiftActive || *isCapsLockActive)
            return "E";
        else
            return "e";

    case KEY_F:
        if (*isShiftActive || *isCapsLockActive)
            return "F";
        else
            return "f";

    case KEY_G:
        if (*isShiftActive || *isCapsLockActive)
            return "G";
        else
            return "g";

    case KEY_H:
        if (*isShiftActive || *isCapsLockActive)
            return "H";
        else
            return "h";

    case KEY_I:
        if (*isShiftActive || *isCapsLockActive)
            return "I";
        else
            return "i";

    case KEY_J:
        if (*isShiftActive || *isCapsLockActive)
            return "J";
        else
            return "j";

    case KEY_K:
        if (*isShiftActive || *isCapsLockActive)
            return "K";
        else
            return "k";

    case KEY_L:
        if (*isShiftActive || *isCapsLockActive)
            return "L";
        else
            return "l";

    case KEY_M:
        if (*isShiftActive || *isCapsLockActive)
            return "H";
        else
            return "m";

    case KEY_N:
        if (*isShiftActive || *isCapsLockActive)
            return "N";
        else
            return "n";

    case KEY_O:
        if (*isShiftActive || *isCapsLockActive)
            return "O";
        else
            return "o";

    case KEY_P:
        if (*isShiftActive || *isCapsLockActive)
            return "P";
        else
            return "p";

    case KEY_Q:
        if (*isShiftActive || *isCapsLockActive)
            return "Q";
        else
            return "q";

    case KEY_R:
        if (*isShiftActive || *isCapsLockActive)
            return "R";
        else
            return "r";

    case KEY_S:
        if (*isShiftActive || *isCapsLockActive)
            return "S";
        else
            return "s";

    case KEY_T:
        if (*isShiftActive || *isCapsLockActive)
            return "T";
        else
            return "t";

    case KEY_U:
        if (*isShiftActive || *isCapsLockActive)
            return "U";
        else
            return "u";

    case KEY_V:
        if (*isShiftActive || *isCapsLockActive)
            return "V";
        else
            return "v";

    case KEY_W:
        if (*isShiftActive || *isCapsLockActive)
            return "W";
        else
            return "w";

    case KEY_X:
        if (*isShiftActive || *isCapsLockActive)
            return "X";
        else
            return "x";

    case KEY_Y:
        if (*isShiftActive || *isCapsLockActive)
            return "Y";
        else
            return "y";

    case KEY_Z:
        if (*isShiftActive || *isCapsLockActive)
            return "Z";
        else
            return "z";

    case KEY_0:
        if (*isShiftActive)
            return ")";
        else
            return "0";

    case KEY_1:
        if (*isShiftActive)
            return "!";
        else
            return "1";

    case KEY_2:
        if (*isShiftActive)
            return "@";
        else
            return "2";

    case KEY_3:
        if (*isShiftActive)
            return "#";
        else
            return "3";

    case KEY_4:
        if (*isShiftActive)
            return "$";
        else
            return "4";

    case KEY_5:
        if (*isShiftActive)
            return "%";
        else
            return "5";

    case KEY_6:
        if (*isShiftActive)
            return "^";
        else
            return "6";

    case KEY_7:
        if (*isShiftActive)
            return "&";
        else
            return "7";

    case KEY_8:
        if (*isShiftActive)
            return "*";
        else
            return "8";

    case KEY_9:
        if (*isShiftActive)
            return "(";
        else
            return "9";

    case KEY_LEFTBRACE:
        if (*isShiftActive)
            return "{";
        else
            return "[";

    case KEY_RIGHTBRACE:
        if (*isShiftActive)
            return "}";
        else
            return "]";

    case KEY_SEMICOLON:
        if (*isShiftActive)
            return ":";
        else
            return ";";

    case KEY_APOSTROPHE:
        if (*isShiftActive)
            return "'";
        else
            return "\"";

    case KEY_GRAVE:
        if (*isShiftActive)
            return "~";
        else
            return "`";

    case KEY_BACKSLASH:
        if (*isShiftActive)
            return "|";
        else
            return "\\";

    case KEY_COMMA:
        if (*isShiftActive)
            return "<";
        else
            return ",";

    case KEY_DOT:
        if (*isShiftActive)
            return ">";
        else
            return ".";

    case KEY_SLASH:
        if (*isShiftActive)
            return "?";
        else
            return "/";

    case KEY_MINUS:
        if (*isShiftActive)
            return "_";
        else
            return "-";

    case KEY_EQUAL:
        if (*isShiftActive)
            return "+";
        else
            return "=";

    default:
        return "z";
    }
}
