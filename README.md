# Linux Native Keycaster

A high-performance, low-level key logging and visualization utility for Linux. This tool captures keystrokes directly from the Linux input subsystem and displays them in a sleek, transparent graphical overlay using the Raylib library.

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
You can follow instructions on how to setup raylib on Ubuntu at https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux
