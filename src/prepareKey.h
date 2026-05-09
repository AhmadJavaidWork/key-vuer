#pragma once

#include <linux/input.h>
#include <stdbool.h>

char *prepareKey(__u16 code, __s32 value, bool *isShiftActive, bool *isCtrlActive,
                 bool *isCapsLockActive);
