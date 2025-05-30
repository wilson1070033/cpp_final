## Potential Problems and Bugs

This document outlines potential problems, bugs, and areas for improvement identified in the codebase.

### 1. Cross-Platform Compatibility Issues

The codebase uses several non-standard or platform-specific features, which will cause issues when compiling or running on different operating systems.

*   **`conio.h` for Input (Windows-specific):**
    *   **Files:** `main.cpp`
    *   **Issue:** The library `<conio.h>` and its functions `kbhit()` (to check for keyboard input without blocking) and `getch()` (to read a character without echoing, and for special key handling) are specific to Windows and some DOS compilers.
    *   **Impact:** Fails to compile on POSIX systems (Linux, macOS).
    *   **Suggestion:** Use a cross-platform library for terminal input (e.g., ncurses) or implement platform-specific input handling using conditional compilation (`#ifdef _WIN32 ... #else ... #endif`).

*   **`unistd.h` for `usleep` (POSIX-specific):**
    *   **Files:** `main.cpp`
    *   **Issue:** The header `<unistd.h>` and the function `usleep()` for microsecond delays are POSIX-specific (Linux, macOS).
    *   **Impact:** Fails to compile on Windows unless a POSIX compatibility layer (like MinGW with appropriate headers) is used. Standard Windows API uses `Sleep()` (uppercase 'S') from `<windows.h>` for millisecond delays.
    *   **Suggestion:** Use `std::this_thread::sleep_for` from `<thread>` and `<chrono>` (C++11 and later) for a portable solution, or use conditional compilation for `Sleep()` vs `usleep()`.

*   **`system("cls")` / `system("clear")` for Screen Clearing:**
    *   **Files:** `main.cpp`
    *   **Issue:** `system("cls")` is a Windows command to clear the console. POSIX systems use `system("clear")`.
    *   **Impact:** Screen clearing will not work as intended on non-Windows platforms if `cls` is hardcoded, or vice-versa.
    *   **Suggestion:** Use conditional compilation to select the correct command or use ANSI escape sequences for clearing, which are more portable across modern terminals.

### 2. Game Logic/Gameplay Issues

*   **Random Obstacle Placement:**
    *   **Files:** `main.cpp` (in `main()` function)
    *   **Issue:** Obstacles (`'O'`) are placed randomly on the map (`GOs.push_back(new Obstacle(randBtw(0, W - 1), randBtw(0, H - 1)));`). This can lead to:
        *   Obstacles blocking the frog's starting area.
        *   Obstacles completely blocking essential paths or safe zones.
        *   Obstacles placed on top of each other (inefficient, though not visually different).
    *   **Suggestion:** Implement more controlled obstacle placement, ensuring critical paths remain open, or ensure obstacles are only placed on road lanes.

*   **No Variation in Vehicle Spawning Beyond Initial Setup:**
    *   **Files:** `main.cpp` (in `main()` function)
    *   **Issue:** Vehicles are only created once at the start of the game. There's no continuous spawning, change in vehicle types, or speed variations as the game progresses.
    *   **Suggestion:** Implement a system for dynamically spawning vehicles during gameplay to increase challenge and replayability.

*   **Scoring Parameter `i` in `Map::addScore(int i)` is Unused:**
    *   **Files:** `main.cpp` (class `Map`)
    *   **Issue:** The method `void Map::addScore(int i)` is defined, but the score is always incremented by a fixed `1` (`score += 1;`) regardless of the value of `i`. The frog's movement always calls `map->addScore(1)`.
    *   **Suggestion:** Change `score += 1;` to `score += i;` if variable score increments are ever intended. If not, change the method signature to `void Map::addScore()`.

*   **No Explicit Win Condition:**
    *   **Files:** `main.cpp`
    *   **Issue:** The game currently ends only when the frog collides with a vehicle. There is no defined "win" state, such as reaching the top safe zone a certain number of times or clearing levels.
    *   **Suggestion:** Implement a win condition (e.g., reaching the top safe zone, then perhaps resetting the frog and increasing difficulty, or moving to a new level).

*   **Hardcoded Vehicle Speed & Integer Division for Motorcycle:**
    *   **Files:** `main.cpp` (class `Moto`, `Car`, and `main()` function)
    *   **Issue:** Vehicle speeds are hardcoded (e.g., `d = 2` or `d = -2`). The motorcycle speed is `d/2`. If `d` was ever set to an odd number (e.g., 1), the motorcycle's speed would become 0 due to integer division, causing it to not move.
    *   **Suggestion:** Define speeds using named constants. For motorcycle speed, ensure `d` is always even or use floating-point division if fractional speeds are desired (though this would complicate grid movement).

### 3. Code Structure/Readability Issues

*   **Use of Magic Numbers:**
    *   **Files:** `main.cpp`
    *   **Issue:** Various numeric literals are used directly in the code without explanation.
        *   Map dimensions: `H = 10`, `W = 40` in `main()`, and related boundary checks like `y < 9`, `x < 39`.
        *   Keyboard arrow key codes: `UP = 72`, `DOWN = 80`, `LEFT = 75`, `RIGHT = 77`, and the special key prefix `-32`.
        *   Vehicle speeds: `d = 2`, `d = -2`.
        *   Game loop delay: `usleep(300 * 1000)`.
    *   **Suggestion:** Replace magic numbers with named constants (`const int` or `constexpr`) for better readability and maintainability.

*   **`GameObject::setXY` as Mainly a Passthrough:**
    *   **Files:** `main.cpp` (class `GameObject`)
    *   **Issue:** `GameObject::setXY` mostly delegates to `Map::setXY`. While it connects the `GameObject` to the `Map`'s state, its role could be clearer or integrated differently.
    *   **Suggestion:** Evaluate if this method is necessary in `GameObject` or if objects should interact with the map more directly or through a different abstraction. This is a minor structural point.

*   **Reliance on a Global Static `Map* GameObject::map`:**
    *   **Files:** `main.cpp` (class `GameObject`)
    *   **Issue:** All `GameObject` instances share a single `Map` instance through a static pointer. This creates a global state, which can make the code harder to test in isolation and less flexible if multiple maps were ever considered.
    *   **Suggestion:** For a small game like this, it's often acceptable. For larger projects, consider dependency injection (passing map reference to objects).

*   **Unused Parameter `P` in `Map` Class:**
    *   **Files:** `main.cpp` (class `Map`)
    *   **Issue:** The `Map` class has a private member `const int P = 2;` that is never used.
    *   **Suggestion:** Remove the unused parameter.

### 4. Input Handling

*   **`getch()` Behavior for Special Keys:**
    *   **Files:** `main.cpp` (class `Frog`, method `move()`)
    *   **Issue:** The code assumes that arrow keys are read as two `char` values, with the first being `-32` (on Windows with `conio.h`). This behavior is highly platform-dependent and specific to `conio.h`.
    *   **Impact:** Input will not work correctly on systems without `conio.h` or with different terminal emulators.
    *   **Suggestion:** This is part of the larger cross-platform input issue. A dedicated input library or platform-specific handlers would be needed to correctly interpret special keys like arrows.

This list should provide a good starting point for addressing issues and improving the codebase.
