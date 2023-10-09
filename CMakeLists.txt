cmake_minimum_required(VERSION 3.26)
set(CMAKE_WIN32_EXECUTABLE true)

project(hw32)

# include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(beat ${SOURCES})
