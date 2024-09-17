cmake_minimum_required(VERSION 3.10)

project(homework2_exe C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

if(APPLE)
   set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")
   set(CMAKE_C_COMPILER "/Library/Developer/CommandLineTools/usr/bin/gcc")
endif()

file(GLOB
     SOURCES
     *.c)

add_executable(homework2_exe ${SOURCES})


