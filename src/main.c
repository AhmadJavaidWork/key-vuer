#include <raylib.h>
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
#include <pthread.h>
#include <string.h>
#include <dirent.h>

#define BUFFER_SIZE 30
struct pollfd *fds;

#define inputDevDir "/dev/input/by-id"

char displayBuffer[BUFFER_SIZE];
char **files;
int devCount = 0;

void writeKeyToBuffer(char *key, int *nextBufferWritePos) {
    if (!strlen(key))
        return;

    if (*nextBufferWritePos + strlen(key) >= BUFFER_SIZE) {
        int positionsToEmpty = strlen(key) - (BUFFER_SIZE - *nextBufferWritePos);
        int l = 0, r = positionsToEmpty;

        while (r < *nextBufferWritePos && r < BUFFER_SIZE) {
            displayBuffer[l] = displayBuffer[r];
            l++;
            r++;
        }
        *nextBufferWritePos -= positionsToEmpty;
    }
    for (int i = 0; i < strlen(key); ++*nextBufferWritePos, ++i) {
        displayBuffer[*nextBufferWritePos] = key[i];
    }
}

void *InputThread(void *arg) {
    int ret;

    int timeoutMS = 5000;
    bool isCapsLockActive = false;
    bool isShiftActive = false;
    bool isCtrlActive = false;
    int nextBufferWritePos = 0;
    fds = malloc(sizeof(struct pollfd *) * devCount);

    for (int i = 0; i < devCount; ++i) {
        fds[i].fd = open(files[i], O_RDONLY | O_NONBLOCK);
        if (fds[i].fd < 0) {
            printf("unable to open: %s\n", files[i]);
            exit(EXIT_SUCCESS);
        }
        fds[i].events = POLLIN;
    }

    struct input_event ev;

    while (true) {
        ret = poll(fds, devCount, timeoutMS);

        for (int i = 0; i < devCount && ret > 0; ++i) {
            if (fds[i].revents & POLLIN) {
                while (read(fds[i].fd, &ev, sizeof(ev)) > 0) {
                    if (ev.type == EV_KEY) {
                        char *key = prepareKey(ev.code, ev.value, &isShiftActive, &isCtrlActive, &isCapsLockActive);
                        writeKeyToBuffer(key, &nextBufferWritePos);
                    }
                }
            }
        }
    }

    return NULL;
}

void handle_sigint(int sig) {
    printf("\ncaptured Ctrl+c! Flushing buffer and closing file...\n");

    for (int i = 0; i < devCount; ++i) {
        close(fds[i].fd);
    }

    exit(0);
}

int main(int argc, char **argv) {
    signal(SIGINT, handle_sigint);

    DIR *dir;
    struct dirent *entry;

    dir = opendir(inputDevDir);

    if (dir == NULL) {
        printf("could not open %s directory try running it with root priviliges\n", inputDevDir);
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, "kbd") == NULL) {
            continue;
        }

        files = realloc(files, sizeof(char *) * (devCount + 1));

        if (files == NULL) {
            closedir(dir);
            printf("could not create memory for filenames\n");
            return EXIT_FAILURE;
        }

        int len = snprintf(NULL, 0, "%s/%s", inputDevDir, entry->d_name);

        files[devCount] = malloc(len + 1);

        if (files[devCount] == NULL) {
            closedir(dir);
            printf("could not create memory for filename\n");
            return EXIT_FAILURE;
        }

        snprintf(files[devCount], len + 1, "%s/%s", inputDevDir, entry->d_name);

        devCount++;
    }

    printf("total keyboards found: %d\n", devCount);

    for (int i = 0; i < devCount; ++i) {
        printf("device names: %s\n", files[i]);
    }

    closedir(dir);

    pthread_t input_threadId;
    pthread_create(&input_threadId, NULL, InputThread, NULL);

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_MOUSE_PASSTHROUGH | FLAG_WINDOW_TRANSPARENT);

    InitWindow(400, 60, "KeyOverlay");
    SetTargetFPS(60);

    int monitor = GetCurrentMonitor();
    SetWindowPosition(GetMonitorWidth(monitor) - 950, GetMonitorHeight(monitor) - 80);

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLANK);
            DrawRectangleRounded((Rectangle){10, 20, 380, 30}, 0.5, 20, (Color){40, 40, 40, 200});

            int textWidth = MeasureText(displayBuffer, 40);
            DrawText(displayBuffer, 20, 25, 20, RAYWHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
