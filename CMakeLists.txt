cmake_minimum_required(VERSION 3.30)
project(BoardGames)

set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(BoardGames src/main.cpp
        src/UI/MenuScene.cpp
        src/UI/SignUpScene.cpp
        src/UI/SignInScene.cpp
        src/UI/GameSelectionScene.cpp
        src/UI/TicTacToeScene.cpp
        src/UI/Lig4Scene.cpp
        src/UI/ReversiScene.cpp
        src/UI/SceneManager.cpp
        include/UI/InputContainer.cpp
        include/UI/InputContainer.hpp
)

## Adding SFML project to build
add_subdirectory(SFML)

set(BUILD_SHARED_LIBS OFF)

## SFML library linkage
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-system)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)