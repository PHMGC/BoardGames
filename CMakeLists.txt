cmake_minimum_required(VERSION 3.30)
project(BoardGames2)

set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(BoardGames2 src/main.cpp
        include/Game.hpp
        include/Board.hpp
        include/TicTacToe.hpp
        include/GameManager.hpp
        include/Piece.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)