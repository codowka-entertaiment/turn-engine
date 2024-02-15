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

file(GLOB_RECURSE
        SOURCES
        src/*.hpp
        src/*.cpp
)

file(GLOB_RECURSE
        INCLUDES
        include/*.hpp
        include/*.cpp
)

add_library(TurnEngine STATIC ${SOURCES} ${INCLUDES})

target_sources(TurnEngine PRIVATE ${SOURCES})

set(public_headers include/turn-engine/TurnEngine.hpp)

set_target_properties(TurnEngine PROPERTIES PUBLIC_HEADER "${public_headers}")

include(GNUInstallDirs)

install(TARGETS TurnEngine
        EXPORT "TurnEngineTargets"
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/TurnEngine
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

target_include_directories(TurnEngine
        PRIVATE
        src
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(TurnEngine PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static)

# Math tests

file(GLOB_RECURSE MATH_TESTS_SOURCES
        "tests/MathTests.cpp"
)

add_executable(MathTests ${MATH_TESTS_SOURCES})
target_include_directories(MathTests PUBLIC include)
target_link_libraries(MathTests PRIVATE Catch2::Catch2WithMain)