cmake_minimum_required(VERSION 3.27)
set(CMAKE_OSX_ARCHITECTURES x86_64)
set(CMAKE_CXX_STANDARD 23)
project(TurnEngine)

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

FetchContent_Declare(
        SDL2_Image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
        GIT_TAG release-2.8.2
        GIT_PROGRESS TRUE
)

FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
        GIT_TAG release-2.20.2
        GIT_PROGRESS TRUE
)

FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
        GIT_TAG release-2.8.0
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(SDL2 SDL2_Image SDL2_ttf SDL2_mixer)

file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "src/*.hpp"
)

file(GLOB_RECURSE INCLUDES
        "include/*.hpp"
)

add_executable(TurnEngine example/main.cpp ${SOURCES} ${INCLUDES})

target_link_libraries(
        TurnEngine PUBLIC
        SDL2::SDL2main
        SDL2::SDL2-static
        SDL2_image
        SDL2_ttf
        SDL2_mixer
)

target_include_directories(TurnEngine PRIVATE src)

target_include_directories(TurnEngine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
