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
game on execution.

