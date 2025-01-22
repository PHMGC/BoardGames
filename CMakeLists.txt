cmake_minimum_required(VERSION 3.30)
project(BoardGames)

set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(BoardGames src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)