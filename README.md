[![Build Status](https://travis-ci.org/Mizux/cmake-external.svg?branch=master)](https://travis-ci.org/Mizux/cmake-external)
[![Build status](https://ci.appveyor.com/api/projects/status/j569d0cnv2fktecn/branch/master?svg=true)](https://ci.appveyor.com/project/Mizux/cmake-external/branch/master)

# Introduction

This is an example of how to create a Modern [CMake](https://cmake.org/) C++ Project using
 [ExternalProject](https://cmake.org/cmake/help/latest/module/ExternalProject.html) module to include dependency(ies) as subproject(s).

This project should run on Linux, Mac and Windows.

# CMake Dependencies Tree
To complexify a little, the CMake project is composed of one executable (FooApp)
with the following dependencies:  
```sh
gflags:
glog: gflags
zlib:
protobuf: zlib
FooApp: gflags glog zlib protobuf Cbc
```
note 1:All dependencies are built in static to have one standalone executable.  
note 2: Cbc is prebuilt (using autotools) then wrapped as Imported Target since it doesn't provide CMake support.
note 3: Cbc is not available on Windows since github coin have broken vcproj (git repo add one directory level)
## Project directory layout
Thus the project layout is as follow:
```
 CMakeLists.txt // meta CMake doing the orchestration and python packaging
 cmake
 ├── CMakeLists.txt
 ├── gflags.CMakeLists.txt
 ├── glog.CMakeLists.txt
 ├── zlib.CMakeLists.txt
 ├── protobuf.CMakeLists.txt
 └── Cbc.cmake
 FooApp
 ├── CMakeLists.txt
 └── src
     └── main.cpp
```

# C++ Project Build
To build the C++ project, as usual:
```sh
cmake -H. -Bbuild
cmake --build build
```
## Build directory layout
Since we want to use the [CMAKE_BINARY_DIR](https://cmake.org/cmake/help/latest/variable/CMAKE_BINARY_DIR.html) to generate the binary package.  
We want this layout (tree build --prune -P "*.py|*.so"):
```
 FooApp
 ├── test
 |   └── FooApp_UT
 └── FooApp
```

# Contributing

The [CONTRIBUTING.md](./CONTRIBUTING.md) file contains instructions on how to
file the Contributor License Agreement before sending any pull requests (PRs).
Of course, if you're new to the project, it's usually best to discuss any
proposals and reach consensus before sending your first PR.

# License

Apache 2. See the LICENSE file for details.

# Disclaimer

This is not an official Google product, it is just code that happens to be
owned by Google.
