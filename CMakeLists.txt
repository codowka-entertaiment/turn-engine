cmake_minimum_required(VERSION 3.26.4)
project(turn-engine)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
set(BUILD_SHARED_LIBS FALSE)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
)

FetchContent_MakeAvailable(Catch2)

# Engine static target

set(SOURCES
        src/Engine.cpp
        src/Engine.hpp
        src/math/Vector.hpp)

add_library(TurnEngine STATIC ${SOURCES})

target_include_directories(TurnEngine PRIVATE src)
target_link_libraries(TurnEngine PRIVATE SDL2::SDL2main SDL2::SDL2-static)

# Math tests

set(MATH_TESTS_SOURCES
        src/math/Vector.hpp
        tests/MathTests.cpp
)

add_executable(MathTests ${MATH_TESTS_SOURCES})
target_link_libraries(MathTests PRIVATE Catch2::Catch2WithMain)