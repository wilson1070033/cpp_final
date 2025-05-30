## Technologies Used

This project utilizes the following technologies:

*   **Programming Language:**
    *   C++ (Standard: C++20, as specified in `CMakeLists.txt`)

*   **Build System:**
    *   CMake

*   **Standard C++ Libraries:**
    *   `<iostream>`: For input and output operations (e.g., `cout`).
    *   `<string>`: For string manipulation.
    *   `<vector>`: For dynamic arrays / lists (used for `grid` in `Map` and `GOs` in `main`).
    *   `<cstdlib>`: For general utilities, including random number generation (`rand`, `srand`).
    *   `<ctime>`: For time-related functions (used for seeding random number generation with `time(0)`).

*   **Platform-Specific Libraries:**
    *   `<conio.h>`: Used for console input/output, specifically `kbhit()` (to check for key press) and `getch()` (to get a character from console without echoing). This is a Windows-specific library.
    *   `<unistd.h>`: Used for the `usleep()` function, which provides microsecond-level pauses. This is a POSIX-specific library (common on Linux and macOS).

The use of both `<conio.h>` and `<unistd.h>` indicates that the current codebase has parts that are specific to Windows and parts that are specific to POSIX-compliant systems, potentially leading to portability issues if not handled carefully (e.g., with conditional compilation).
