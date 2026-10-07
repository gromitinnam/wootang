I want analog controller input, but I don't wanna be pulled to the level of console babies, so I use WOOTANG.

For now, just close the terminal to end the program.

## Build

In VS Code, run the default build task (`Ctrl+Shift+B`) to build WOOTANG with MSVC. This requires Visual Studio with the **Desktop development with C++** workload installed.

The build uses:

- `wootang.c` for the application source.
- `include/wooting-analog-sdk.h` for the Wooting Analog SDK declarations.
- `lib/wooting_analog_sdk_dist.dll.lib` to link against the 64-bit Wooting SDK DLL.
- The Windows SDK headers and libraries provided by Visual Studio, including `windows.h` and `user32.lib`.

`wooting_analog_sdk_dist.dll` must remain beside `wootang.exe` when running the program. `include/plugin.h` is for SDK plugin development and is not needed by this application. Object files, executables, and PDB files are build outputs, not required source inputs.
