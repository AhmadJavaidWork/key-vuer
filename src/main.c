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
#include <stdatomic.h>

#define INPUT_DEV_DIR "/dev/input/by-id"

#define BUFFER_SIZE 30
#define WIDTH 350
#define HEIGHT 80
#define FONT_SIZE 20
#define Y_INSET 20
#define X_INSET 20
#define ROUNDNESS 0.25
#define SEGMENTS 20
#define R 30
#define G 30
#define B 46
#define A 200
#define X_PADDING 20
#define FONT_SPACING 0

volatile atomic_bool keepRunning = true;

struct pollfd *fds = NULL;

char displayBuffer[BUFFER_SIZE];
char **devFiles;
int devCount = 0;

void freeMemory() {
    printf("freeing memory\n");
    if (devFiles) {
        for (int i = 0; i < devCount; ++i) {
            free(devFiles[i]);
        }
        free(devFiles);
        devFiles = NULL;
    }

    if (fds) {
        for (int i = 0; i < devCount; ++i) {
            if (fds[i].fd >= 0)
                close(fds[i].fd);
        }
        free(fds);
        fds = NULL;
    }
}

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
    fds = malloc(sizeof(struct pollfd) * devCount);

    for (int i = 0; i < devCount; ++i) {
        fds[i].fd = open(devFiles[i], O_RDONLY | O_NONBLOCK);
        if (fds[i].fd < 0) {
            printf("INFO: Unable to open: %s\n", devFiles[i]);
            keepRunning = false;
            return NULL;
        }
        fds[i].events = POLLIN;
    }

    struct input_event ev;

    while (atomic_load(&keepRunning)) {
        ret = poll(fds, devCount, timeoutMS);

        for (int i = 0; i < devCount && ret > 0; ++i) {
            while (read(fds[i].fd, &ev, sizeof(ev)) > 0) {
                if (ev.type == EV_KEY) {
                    char *key = prepareKey(ev.code, ev.value, &isShiftActive, &isCtrlActive, &isCapsLockActive);
                    writeKeyToBuffer(key, &nextBufferWritePos);
                }
            }
        }
    }

    return NULL;
}

void handle_sigint(int sig) {
    printf("\nINFO: Captured Ctrl+c!\n");
    keepRunning = false;
}

int main() {
    signal(SIGINT, handle_sigint);

    DIR *dir;
    struct dirent *entry;

    dir = opendir(INPUT_DEV_DIR);

    if (dir == NULL) {
        printf("ERROR: Could not open %s directory try running it with root priviliges\n", INPUT_DEV_DIR);
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, "kbd") == NULL) {
            continue;
        }

        devFiles = realloc(devFiles, sizeof(char *) * (devCount + 1));

        if (devFiles == NULL) {
            closedir(dir);
            freeMemory();
            printf("ERROR: Could not create memory for filenames\n");
            return EXIT_FAILURE;
        }

        int len = snprintf(NULL, 0, "%s/%s", INPUT_DEV_DIR, entry->d_name);

        devFiles[devCount] = malloc(len + 1);

        if (devFiles[devCount] == NULL) {
            closedir(dir);
            freeMemory();
            printf("ERROR: Could not create memory for filename\n");
            return EXIT_FAILURE;
        }

        snprintf(devFiles[devCount], len + 1, "%s/%s", INPUT_DEV_DIR, entry->d_name);

        devCount++;
    }

    printf("INFO: Keyboard devices found: %d\n", devCount);

    for (int i = 0; i < devCount; ++i) {
        printf("INFO: Device names: %s\n", devFiles[i]);
    }

    closedir(dir);

    pthread_t input_threadId;
    pthread_create(&input_threadId, NULL, InputThread, NULL);

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_MOUSE_PASSTHROUGH | FLAG_WINDOW_TRANSPARENT);

    InitWindow(WIDTH, HEIGHT, "KeyOverlay");
    Font font = LoadFontEx("src/assets/fonts/JetBrainsMonoNerdFont-Regular.ttf", FONT_SIZE, NULL, 0);
    SetTargetFPS(60);

    int monitor = GetCurrentMonitor();
    SetWindowPosition(GetMonitorWidth(monitor) - WIDTH - X_INSET, GetMonitorHeight(monitor) - HEIGHT - Y_INSET);

    while (atomic_load(&keepRunning) && !WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLANK);
            DrawRectangleRounded((Rectangle){5, 5, WIDTH - 10, HEIGHT - 10}, ROUNDNESS, SEGMENTS, (Color){R, G, B, A});

            DrawTextEx(font, displayBuffer, (Vector2){X_PADDING, HEIGHT / 2.0 - FONT_SIZE / 2.0}, FONT_SIZE, 0, RAYWHITE);
        }

        EndDrawing();
    }

    atomic_store(&keepRunning, false);
    pthread_join(input_threadId, NULL);

    CloseWindow();
    freeMemory();
    UnloadFont(font);
    return 0;
}
