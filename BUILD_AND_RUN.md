## Building and Running the Project Locally

This guide provides instructions on how to build and run the Frogger clone project on your local machine.

**1. Prerequisites:**

Before you begin, ensure you have the following software installed:

*   **C++ Compiler:**
    *   **Linux/macOS:** GCC or Clang (usually installed with development tools).
    *   **Windows:** Microsoft Visual C++ (MSVC) (comes with Visual Studio) or MinGW-w64 (for a GCC-like environment).
*   **CMake:**
    *   Download and install CMake from [cmake.org](https://cmake.org/download/). Ensure it's added to your system's PATH.

**2. Build Steps:**

These steps are generally applicable. Specific commands for your build tool (like Make, Ninja, or MSVC) might vary slightly.

*   **Open a Terminal or Command Prompt:**
    *   **Linux/macOS:** Use your preferred terminal application.
    *   **Windows:** Use Command Prompt (`cmd.exe`), PowerShell, or the Developer Command Prompt for Visual Studio.

*   **Navigate to the Project Directory:**
    Change your current directory to the root of the project (where `CMakeLists.txt` is located).
    ```bash
    cd path/to/your/project
    ```

*   **Create a Build Directory:**
    It's good practice to build the project out-of-source.
    ```bash
    mkdir build
    cd build
    ```

*   **Configure with CMake:**
    This step generates the build files for your specific compiler and build system.
    ```bash
    cmake ..
    ```
    *   If you have multiple compilers or want to specify a generator (e.g., for Visual Studio), you can use the `-G` flag. For example:
        ```bash
        cmake -G "Visual Studio 17 2022" .. 
        ```
        Run `cmake --help` to see available generators.

*   **Compile the Project:**
    *   **Linux/macOS (with Makefiles, default for many):**
        ```bash
        make
        ```
    *   **Windows (with MSVC, if generated Visual Studio solution):**
        Open the `.sln` file in the `build` directory with Visual Studio and build from there, or use `msbuild`:
        ```bash
        msbuild project.sln /property:Configuration=Release 
        ```
        (Replace `project.sln` with the actual solution name if different).
    *   **Windows (with MinGW-w64 and Makefiles):**
        ```bash
        mingw32-make 
        ```
    *   **Other build systems (e.g., Ninja):**
        ```bash
        ninja
        ```

**3. Execution:**

After a successful build, the executable will be located in the `build` directory (or a subdirectory like `build/Debug` or `build/Release`, depending on the configuration).

*   **Linux/macOS:**
    ```bash
    ./project 
    ```
    (Assuming the executable is named `project`).

*   **Windows:**
    ```bash
    project.exe
    ```
    (Or, if you built in a specific configuration directory, e.g., `Release\project.exe`).

**4. Cross-Platform Considerations:**

The current version of the game uses some platform-specific features:

*   **Windows-Specific:**
    *   `#include <conio.h>`: Used for non-blocking keyboard input (`kbhit()`, `getch()`).
    *   `system("cls")`: Used to clear the console screen.
*   **POSIX-Specific (Linux/macOS):**
    *   `#include <unistd.h>`: Used for the `usleep()` function to pause game execution.

**To run this project on a platform other than Windows (e.g., Linux or macOS), you will likely need to:**

1.  **Modify Keyboard Input:** Replace `kbhit()` and `getch()` with a POSIX-compatible method for non-blocking terminal input (e.g., using `ncurses` library, or `select` with `stdin`).
2.  **Modify Screen Clearing:** Replace `system("cls")` with its POSIX equivalent, `system("clear")`, or use ANSI escape codes for more control.
3.  **Adapt `usleep`:** While `usleep` is POSIX, ensure your compiler and environment support it. Alternatives like `std::this_thread::sleep_for` from `<thread>` and `<chrono>` (C++11 onwards) are more portable for pauses.

Without these modifications, the game might not compile or run as expected on non-Windows systems due to the direct use of `<conio.h>` and `system("cls")`. Similarly, if compiling on a non-POSIX system (less common for C++ development environments), `unistd.h` might be unavailable. The `CMakeLists.txt` does not currently handle these platform differences.
