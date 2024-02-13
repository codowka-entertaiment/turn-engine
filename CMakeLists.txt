cmake_minimum_required(VERSION 3.26.4)
project(turn-engine)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
set(BUILD_SHARED_LIBS FALSE)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.5
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
        SDL2_Image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
        GIT_TAG release-2.8.2
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(SDL2_Image)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
)

FetchContent_MakeAvailable(Catch2)

# Engine static target

file(GLOB_RECURSE SOURCES
        "src/*.hpp"
        "src/*.cpp"
)

add_library(TurnEngine STATIC ${SOURCES}
        src/sdl/SDL.hpp
        src/sdl/Window.cpp
        src/sdl/Window.hpp
        src/sdl/Renderer.cpp
        src/sdl/Renderer.hpp
        src/sdl/Surface.cpp
        src/sdl/Surface.hpp
        src/sdl/Texture.cpp
        src/sdl/Texture.hpp)

target_include_directories(TurnEngine PRIVATE src)
target_link_libraries(TurnEngine PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static)

# Math tests

file(GLOB_RECURSE MATH_TESTS_SOURCES
        "src/math/*.hpp"
        "src/math/*.cpp"
        "tests/MathTests.cpp"
)

add_executable(MathTests ${MATH_TESTS_SOURCES})
target_link_libraries(MathTests PRIVATE Catch2::Catch2WithMain)