cmake_minimum_required(VERSION 3.10)
project(Cpp_Minigame_Collection)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
    message("Building on Windows")
elseif(APPLE)
    message("Building on macOS")
elseif(UNIX)
    message("Building on Linux")
endif()

# Include the "include" directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the source files
add_executable(minigames        #We have defined the executable with all the required program files
    src/main.cpp
    games/NumberGuessingGame.cpp
)

