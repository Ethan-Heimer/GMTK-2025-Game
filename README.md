# An SDL3 Project template

This is just a simple template top get started with SDL3 projects. 

## Installation

Just Clone this repo! 
```
git clone https://github.com/Ethan-Heimer/SDL3ProjectTemplate
```
## Renaming Your Project

A project config file can be found in `.var/env.txt`, where the `PROJECT_NAME` env variable
represents the name if the project.

## Building a project
There are 2 ways a project can be built with this configuration.

- `./Build.sh`
- The manual way

### Build.sh

`./Build.sh` is a bash script that will automatically configure directories to be linked within the project. run it like a normal bash command. 
the output by default will be built in `./build/bin/`.

Because bash scripts are used to automatically used to generate alot of CMake, the CMakeLists.txt file is not complete, and will not build the project properly.
If you need a fully built `CMakeLists.txt` file, run the following bash scripts:

- `./.bash/appendDirsToCMakeLists.sh`
- `./.bash/generateDirCMakeFiles.sh`

You can find these bash scripts in `./.bash`.

### Adding Extra External Libs From Github

To add any libs from git hub (other SDL3 libs especially), copy this block into the 
root `CMakeLists.txt` file:

```
FetchContent_Declare(
    {LIB NAME HERE}
    GIT_REPOSITORY "{LIB GITHUB URL HERE}"
    GIT_TAG "origin/main"
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/external/{LIB DIR NAME HERE}"
)
```

and append the lib name to `FetchContent_MakeAvailable`.\
finaly the lib should have a cmake target name associated with it. use the target name too 
add the lib to the compiled application with\
`target_link_libraries({PROJECT NAME} PRIVATE {LIB TARGET NAME})`

### Adding a new directory in scr/project/

Unfortunatly, adding a new directory that the project will have to link is not done without some extra configuration.
Every directory that the project must link to must have its own 'CMakeLists.txt' file as well. These files will contain somthing like the followign:
```
target_sources({PROJECT NAME} PRIVATE 
    {SOURCE FILE}.h
    {SOURCE FILE}.cpp
    ...
)
```

Every source file in the directory must be added into the `target_sources` block.

In the root `CMakeLists.txt` file add this line:

```
add_subdirectory("${CMAKE_SOURCE_DIR}/${PROJECT_DIR}/{DIRECTORY PATH}")
```

where `{DIRECTIRY PATH}` should be chnaged to the path of the directory your looking to link

### The .gitignore

By default the git ingore will ingore the `build` directory and the `src/external` directory.

