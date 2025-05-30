## How to Play

**Objective:**
The goal of the game is to guide the frog ('F') from the starting safe zone at the bottom of the screen, across multiple lanes of traffic, to reach any safe zone. Be careful, as vehicles move quickly!

**Controls:**
- Use the **Arrow Keys** on your keyboard to move the frog:
    - **Up Arrow:** Move frog one step up.
    - **Down Arrow:** Move frog one step down.
    - **Left Arrow:** Move frog one step left.
    - **Right Arrow:** Move frog one step right.

**Gameplay:**
- Navigate the frog across the road, avoiding cars ('C') and motorcycles ('M').
- If the frog is hit by a vehicle, the game is over.
- Each successful move to a new tile increases your score.
- There are some safe zones (rows marked with '=') where the frog will not be hit by vehicles.
- Obstacles ('O') also appear on the map and will block the frog's movement.

## How to Run

This project is built using C++ and CMake.

**Prerequisites:**
1.  **C++ Compiler:** You'll need a C++ compiler that supports C++20 (e.g., GCC, Clang, MSVC).
2.  **CMake:** Ensure CMake is installed and added to your system's PATH. You can download it from [cmake.org](https://cmake.org).

**Build Steps:**
1.  Open your terminal or command prompt.
2.  Navigate to the root directory of this project.
3.  Create a build directory and change into it:
    ```bash
    mkdir build
    cd build
    ```
4.  Run CMake to generate the build files (e.g., Makefiles or Visual Studio solution):
    ```bash
    cmake ..
    ```
5.  Compile the project:
    *   If Makefiles were generated (common on Linux/macOS or with MinGW): `make`
    *   If a Visual Studio solution (`.sln`) was generated: Open it with Visual Studio and build, or use `msbuild YOUR_PROJECT_NAME.sln /property:Configuration=Release` from a developer command prompt.
    *   If Ninja files were generated: `ninja`

**Execute the Game:**
- After a successful build, the executable (e.g., `project.exe` on Windows, or `project` on Linux/macOS) will be located in the `build` directory (or a subdirectory like `build/Release` or `build/Debug`).
- Run it from your terminal:
    *   Windows: `project.exe`
    *   Linux/macOS: `./project`

**Important Note on Compatibility:**
The current version of the game uses Windows-specific libraries (`conio.h` for keyboard input and `system("cls")` for clearing the screen). To run it on other operating systems like Linux or macOS, you would need to modify the source code to use platform-appropriate equivalents (e.g., ncurses for input, `system("clear")` for screen clearing, and `std::this_thread::sleep_for` for delays).
