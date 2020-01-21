# agsconfig

[![Build Status](https://dev.azure.com/ericoporto/agsconfig/_apis/build/status/ericoporto.agsconfig?branchName=master)](https://dev.azure.com/ericoporto/agsconfig/_build/latest?definitionId=13&branchName=master)

agsconfig tries to give similar functionality to the traditional winsetup.exe of Adventure Game Studio, but cross platform

![](https://user-images.githubusercontent.com/2244442/72697367-8be01e80-3b1e-11ea-84ce-9d6fc45d3fd2.png)

## Using with your game

Place `agsconfig` executable at the same location of your game entry-point (`mygame`) or binary (`mygame.exe`). 
On MacOS, place it at the side of the AGS Engine binary.

Add on the same directory a `.config` file, and add the following content to it:

```
[game]
executable = mygame
```

On MacOS, set the value of the executable to the binary of the AGS Engine and certify the AGS Engine is finding your 
game on execution. For now, it also requires marking it as executable with `chmod +x agsconfig` - or the name you set for this utility.

## Embedded project libraries

This project uses the following libraries that are already supplied in the repository for simplicity

- SDL2-2.0.10
- ImGui
- inipp
- tiny-process-library
- optional-lite
- dirent (Windows compatibility)

## Dependencies

This project uses CMake as a build system, at least version 3.13, so you will have to install it. It should just work with the CMake provided by CLion, so should just load it if editing on it. On Visual Studio, you need to install the CMake tools provided by the Visual Studio installer, and later open this directory through open folder, [more details supplied on it's official docs...](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019#ide-integration). On MacOS you will need XCode installed.

On Linux, you will need additionally the packages `libgl1-mesa-dev` and `mesa-common-dev` (both are available in apt and provide libGL and libdl, needed for linking).

## License

AGS Config is made by Érico Vieira Porto and provided with MIT license, see [`LICENSE`](https://github.com/ericoporto/agsconfig/blob/master/LICENSE).

SDL (Simple DirectMedia Layer) is by Sam Lantinga and provided with it's own license, see [`COPYING.txt`](https://github.com/ericoporto/agsconfig/blob/master/libs/SDL2-2.0.10/COPYING.txt).

Dear ImGui is made by Omar Cornut and provided with MIT license, see [`LICENSE.txt`](https://github.com/ericoporto/agsconfig/blob/master/libs/imgui/LICENSE.txt).

IniPP is made by Matthias C. M. Troffaes and provided with MIT license, see [`LICENSE.txt`](https://github.com/ericoporto/agsconfig/blob/master/libs/inipp/LICENSE.txt).

optional lite is distributed under the Boost Software License, see [`LICENSE.txt`](https://github.com/ericoporto/agsconfig/blob/master/libs/optional-lite/LICENSE.txt).

tiny-process-library is made by Ole Christian Eidheim and provided with MIT license, see [`LICENSE`](https://github.com/ericoporto/agsconfig/blob/master/libs/tiny-process-library/LICENSE).

Dirent Windows interface is made by Toni Ronkko and provided with MIT license, see [`LICENSE`](https://github.com/ericoporto/agsconfig/blob/master/libs/dirent/LICENSE).
