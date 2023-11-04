cmake_minimum_required(VERSION 3.16)
project(game)

include(FetchContent)

# SDL
FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.28.x
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(SDL)

add_executable(game WIN32 main.cpp)
target_link_libraries(game PRIVATE SDL2::SDL2 SDL2::SDL2main)
