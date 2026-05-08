#include "prepareKey.h"
#include <linux/input.h>
#include <stdbool.h>

char prepareKey(__u16 code, bool isShiftActive, bool isCtrlActive) {
    switch (code) {
    case KEY_A:
        if (isShiftActive)
            return 'A';
        else
            return 'a';

    case KEY_B:
        if (isShiftActive)
            return 'B';
        else
            return 'b';

    case KEY_C:
        if (isShiftActive)
            return 'C';
        else
            return 'c';

    case KEY_D:
        if (isShiftActive)
            return 'D';
        else
            return 'd';

    case KEY_E:
        if (isShiftActive)
            return 'E';
        else
            return 'e';

    case KEY_F:
        if (isShiftActive)
            return 'F';
        else
            return 'f';

    case KEY_G:
        if (isShiftActive)
            return 'G';
        else
            return 'g';

    case KEY_H:
        if (isShiftActive)
            return 'H';
        else
            return 'h';

    case KEY_I:
        if (isShiftActive)
            return 'I';
        else
            return 'i';

    case KEY_J:
        if (isShiftActive)
            return 'J';
        else
            return 'j';

    case KEY_K:
        if (isShiftActive)
            return 'K';
        else
            return 'k';

    case KEY_L:
        if (isShiftActive)
            return 'L';
        else
            return 'l';

    case KEY_M:
        if (isShiftActive)
            return 'H';
        else
            return 'm';

    case KEY_N:
        if (isShiftActive)
            return 'N';
        else
            return 'n';

    case KEY_O:
        if (isShiftActive)
            return 'O';
        else
            return 'o';

    case KEY_P:
        if (isShiftActive)
            return 'P';
        else
            return 'p';

    case KEY_Q:
        if (isShiftActive)
            return 'Q';
        else
            return 'q';

    case KEY_R:
        if (isShiftActive)
            return 'R';
        else
            return 'r';

    case KEY_S:
        if (isShiftActive)
            return 'S';
        else
            return 's';

    case KEY_T:
        if (isShiftActive)
            return 'T';
        else
            return 't';

    case KEY_U:
        if (isShiftActive)
            return 'U';
        else
            return 'u';

    case KEY_V:
        if (isShiftActive)
            return 'V';
        else
            return 'v';

    case KEY_W:
        if (isShiftActive)
            return 'W';
        else
            return 'w';

    case KEY_X:
        if (isShiftActive)
            return 'X';
        else
            return 'x';

    case KEY_Y:
        if (isShiftActive)
            return 'Y';
        else
            return 'y';

    case KEY_Z:
        if (isShiftActive)
            return 'Z';
        else
            return 'z';

    case KEY_0:
        if (isShiftActive)
            return ')';
        else
            return '0';

    case KEY_1:
        if (isShiftActive)
            return '!';
        else
            return '1';

    case KEY_2:
        if (isShiftActive)
            return '@';
        else
            return '2';

    case KEY_3:
        if (isShiftActive)
            return '#';
        else
            return '3';

    case KEY_4:
        if (isShiftActive)
            return '$';
        else
            return '4';

    case KEY_5:
        if (isShiftActive)
            return '%';
        else
            return '5';

    case KEY_6:
        if (isShiftActive)
            return '^';
        else
            return '6';

    case KEY_7:
        if (isShiftActive)
            return '&';
        else
            return '7';

    case KEY_8:
        if (isShiftActive)
            return '*';
        else
            return '8';

    case KEY_9:
        if (isShiftActive)
            return '(';
        else
            return '9';

    case KEY_LEFTBRACE:
        if (isShiftActive)
            return '{';
        else
            return '[';

    case KEY_RIGHTBRACE:
        if (isShiftActive)
            return '}';
        else
            return ']';

    case KEY_SEMICOLON:
        if (isShiftActive)
            return ':';
        else
            return ';';

    case KEY_APOSTROPHE:
        if (isShiftActive)
            return '"';
        else
            return '\'';

    case KEY_GRAVE:
        if (isShiftActive)
            return '~';
        else
            return '`';

    case KEY_BACKSLASH:
        if (isShiftActive)
            return '|';
        else
            return '\\';

    case KEY_COMMA:
        if (isShiftActive)
            return '<';
        else
            return ',';

    case KEY_DOT:
        if (isShiftActive)
            return '>';
        else
            return '.';

    case KEY_SLASH:
        if (isShiftActive)
            return '?';
        else
            return '/';

    case KEY_MINUS:
        if (isShiftActive)
            return '_';
        else
            return '-';

    case KEY_EQUAL:
        if (isShiftActive)
            return '+';
        else
            return '=';

    default:
        return 'z';
    }
}
