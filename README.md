# Linux Native Keycaster

A high-performance, low-level key logging and visualization utility for Linux. This tool captures keystrokes directly from the Linux input subsystem and displays them in a sleek, transparent graphical overlay using the Raylib library.

<img width="420" height="98" alt="image" src="https://github.com/user-attachments/assets/0c06e438-44f3-4235-9a1e-82d75ec7912c" />


## Features
*   **Direct Input Capture:** Reads directly from `linux/input.h` for low-latency event processing.
*   **Native Performance:** Written in pure C with zero dependency on heavy web-based frameworks or VMs.
*   **Transparent Overlay:** Uses a hardware-accelerated transparent window to show keystrokes over any active application.
*   **Minimalist Design:** Focused on a clean "native feel" without bloat.

## Tech Stack
*   **Language:** C
*   **Graphics:** [Raylib](https://www.raylib.com/)
*   **OS:** Linux (Ubuntu tested)
*   **Input:** Evdev (`/dev/input/event*`)

## Prerequisites

Ensure you have the necessary development libraries installed:

### Raylib
You can follow instructions on how to setup raylib on GNU Linux at https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux

## Usage

```bash
git clone git@github.com:AhmadJavaidWork/key-vuer.git
cd key-vuer
make && sudo ./key-veur.o
```

## Customize options

You can configure following options in src/main.c

| Option | Description |
| -------- | -------- |
| INPUT_DEV_DIR | Directory that contains the linux input events e.g; `/dev/input/by-id` |
| BUFFER_SIZE | Width of the text to be kept track on the keyvuer |
| WIDTH | Width of the overlay |
| HEIGHT | Height of the overlay |
| FONT_SIZE | Font size |
| Y_INSET | y padding for the window |
| X_INSET | x padding for the window |
| ROUNDNESS | Border radius of the rectangle |
| SEGMENTS | No idea about that 😅 |
| R | Red value for the background |
| G | Green value for the background |
| B | Blue value for the background |
| A | Transparency |
| X_PADDING | Padding inside the rectangle |

