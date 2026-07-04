cmake_minimum_required(VERSION 3.20)

project(PARCIAL_SO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PARCIAL_SO
        main.cpp
        Process.cpp
        Queue.cpp
        Scheduler.cpp
        FileManager.cpp
)