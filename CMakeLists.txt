cmake_minimum_required(VERSION 3.10)
project(IntersectionCoordination VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(coordination_engine ${SOURCES})
target_include_directories(coordination_engine PRIVATE ${PROJECT_SOURCE_DIR}/include)