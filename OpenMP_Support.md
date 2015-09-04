## OpenMP Support <img src="https://s.tylingsoft.com/emoji-icons/rocket.png" width="18"/>
:rocket:
with llvm und clang
http://clang.llvm.org/get_started.html

linked from http://clang-omp.github.io
coming from this http://stackoverflow.com/questions/25990296/how-to-include-omp-h-in-os-x

Update *CmakeLists.txt* with the following lines:
```find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()```


------------------------------
##### Following instractions copyed from http://clang.llvm.org/get_started.html
-------------------------------
If you would like to check out and build Clang, the current procedure is as follows:

1. Get the required tools.
 See Getting Started with the LLVM System - Requirements. http://llvm.org/docs/GettingStarted.html#requirements
- Note also that Python is needed for running the test suite. Get it at: http://www.python.org/download
- Standard build process uses CMake. Get it at: http://www.cmake.org/download
2. Checkout LLVM:
- Change directory to where you want the llvm directory placed.
- ```svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm```
3. Checkout Clang:
- ```cd llvm/tools```
- ```svn co http://llvm.org/svn/llvm-project/cfe/trunk clang```
- ```cd ../..```
4. Checkout extra Clang Tools: (optional)
- ```cd llvm/tools/clang/tools```
- ```svn co http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra```
- ```cd ../../../..```
5. Checkout Compiler-RT:
- ```cd llvm/projects```
- ```svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt```
- ```cd ../..```
6. Build LLVM and Clang:
- ```mkdir build``` (in-tree build is not supported)
- ```cd build```
- ```cmake -G "Unix Makefiles" ../llvm```
- ```make```
- This builds both LLVM and Clang for debug mode.
- Note: For subsequent Clang development, you can just run make clang.
- CMake allows you to generate project files for several IDEs: Xcode, Eclipse CDT4, CodeBlocks, Qt-Creator (use the CodeBlocks generator), KDevelop3. For more details see Building LLVM with CMake page.
- You can also build Clang with autotools, but some features may be unavailable there.
7. If you intend to use Clang's C++ support, you may need to tell it how to find your C++ standard library headers. In general, Clang will detect the best version of libstdc++ headers available and use them - it will look both for system installations of libstdc++ as well as installations adjacent to Clang itself. If your configuration fits neither of these scenarios, you can use the ```--with-gcc-toolchain``` configure option to tell Clang where the gcc containing the desired libstdc++ is installed.
8. Try it out (assuming you add llvm/Debug+Asserts/bin to your path):
- ```clang --help```
- ```clang file.c -fsyntax-only``` (check for correctness)
- ```clang file.c -S -emit-llvm -o -``` (print out unoptimized llvm code)
- ```clang file.c -S -emit-llvm -o - -O3```
- ```clang file.c -S -O3 -o -``` (output native machine code)
Note that the C front-end uses LLVM, but does not depend on llvm-gcc. If you encounter problems with building Clang, make sure you have the latest SVN version of LLVM. LLVM contains support libraries for Clang that will be updated as well as development on Clang progresses.



### Using the newlie installes compiler
```export PATH=/install/prefix/bin:$PATH
export C_INCLUDE_PATH=/install/prefix/include:<OpenMP include path>:$C_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=/install/prefix/include:<OpenMP include path>:$CPLUS_INCLUDE_PATH
export LIBRARY_PATH=/install/prefix/lib:<OpenMP library path>:$LIBRARY_PATH
export LD_LIBRARY_PATH=/install/prefix/lib:<OpenMP library path>:$LD_LIBRARY_PATH```

On Mac OS replace - LD_LIBRARY_PATH with DYLD_LIBRARY_PATH so it is the following: 
```export PATH=/install/prefix/bin:$PATH
export C_INCLUDE_PATH=/install/prefix/include:/usr/local/Cellar/clang-omp/2015-04-01/libexec/include:$C_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=/install/prefix/include:/usr/local/Cellar/clang-omp/2015-04-01/libexec/include:$CPLUS_INCLUDE_PATH
export LIBRARY_PATH=/install/prefix/lib:/install/prefix/lib:/usr/local/Cellar/libiomp/20150401/include/:$LIBRARY_PATH
export DYLD_LIBRARY_PATH=/install/prefix/lib:/usr/local/Cellar/libiomp/20150401/include/libiomp/:$DYLD_LIBRARY_PATH```

http://stackoverflow.com/questions/30670733/installing-openmp-mac-os-x-10-10
```/usr/local/Cellar/clang-omp/2015-04-01/libexec/include```
```/install/prefix/lib:/usr/local/Cellar/libiomp/20150401/include/```

### Using clang-omp with Xcode
Instructions are provided by Sebastian Stenzel. https://github.com/totalvoidness
1. Install clang-omp using *homebrew*: ```brew install clang-omp``.
2. Create a new Xcode project.
3. Under Build Settings
4. Add a new user-defined setting CC with the value ```/usr/local/bin/clang-omp```
5. Add ```-fopenmp``` to Other C Flags
6. Add ```/usr/local/include``` to Header Search Paths
7. Set Enable Modules (C and Objective-C) to No.
8. Under Build Phases
9. Add ```/usr/local/lib/libiomp5.dylib``` to Link Binary With Libraries
1. Done. You can now ```#include <libiomp/omp.h>``` and start using ```#pragma omp``` ... in your source code.

Testing the installed Brew version.
```$ export PATH=/usr/local/bin/:$PATH
$  which pkg-config
/usr/local/bin//pkg-config
$ brew test clang-omp
Testing clang-omp
==> /usr/local/Cellar/clang-omp/2015-04-01/bin/clang-omp -liomp5 -fopenmp test.c
==> ./test
$ ````


Now *I am ending* with ```brew install gcc --without-multilib```
Some suggestions was about to install gcc over the mac ports collection like ```sudo port install gcc47```. But hmmm. I dont know... At the moment over brew i`ll get the version 5.2 not 4.7 (2.3.2013 - http://stackoverflow.com/questions/15142725/os-x-10-8-llvm-openmp-with-cmake)


New symlinks for gcc
```  cd /usr/bin
  rm cc gcc c++ g++
  ln -s /usr/local/bin/gcc-5 cc
  ln -s /usr/local/bin/gcc-5 gcc
  ln -s /usr/local/bin/c++-5 c++
  ln -s /usr/local/bin/g++-5 g++ ``