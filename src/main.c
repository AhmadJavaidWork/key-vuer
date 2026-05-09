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

#define BUFFER_SIZE 30
FILE *outputfile;
struct pollfd fds[1];

char displayBuffer[BUFFER_SIZE];
char *filename;
char *outputfilename;

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
    int currentbuffersize = 0;
    int nextBufferWritePos = 0;

    fds[0].fd = open(filename, 0, O_RDONLY);
    if (fds[0].fd < 0) {
        printf("Unable to open: %s\n", filename);
        exit(EXIT_SUCCESS);
    }

    struct input_event ev;
    fds[0].events = POLLIN;

    while (true) {
        ret = poll(fds, 1, timeoutMS);

        if (ret > 0 && (fds[0].revents & POLLIN)) {
            while (read(fds[0].fd, &ev, sizeof(ev)) > 0) {
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
    fflush(outputfile);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Invalid number of arguments\n");
        printf("%s [device input filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    signal(SIGINT, handle_sigint);

    filename = argv[1];
    outputfilename = argv[2];

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
