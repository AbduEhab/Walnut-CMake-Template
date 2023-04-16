# Cmake-Template Repo

This Repo is for those who want to use `The Cherno`'s library but would rather use good old CMake (with maybe VS Code) than the full fat version of Visual Studio that he set up the project to use. 

> NOW SUPPORTS GCC!

I'm looking into Linux compatibility.

# Requirements
- [CMake](https://cmake.org/)
- x64 Compiler (DOES NOT WORK WITH x86 COMPILERS!!!) (Currently tested `only` with [Visual Studio 22 Build Tools](https://visualstudio.microsoft.com/downloads/) and [MinGW GCC](https://github.com/niXman/mingw-builds-binaries/releases))
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home#windows)

> linux users may follow [This Guide](https://linuxconfig.org/install-and-test-vulkan-on-linux)

## Profiling

You can use https://ui.perfetto.dev/ to view the profiling data. The data is stored in `profiling/` and is named `perfetto_trace.json`.
