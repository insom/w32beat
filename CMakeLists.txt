cmake_minimum_required(VERSION 3.26)
set(CMAKE_WIN32_EXECUTABLE true)

project(w32beat)

# include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(beat ${SOURCES})
