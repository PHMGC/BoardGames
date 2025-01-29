cmake_minimum_required(VERSION 3.30)
project(BoardGames)

set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/include")
set(CMAKE_OBJECT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")

add_executable(BoardGames src/main.cpp
        src/Board.cpp
        src/Game.cpp
        src/GameManager.cpp
        src/Lig4.cpp
        src/Piece.cpp
        src/Reversi.cpp
        src/SaveManager.cpp
        src/TicTacToe.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)