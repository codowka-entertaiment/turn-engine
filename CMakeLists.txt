cmake_minimum_required(VERSION 3.27)
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

FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
        SDL2_Image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
        GIT_TAG release-2.8.2
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(SDL2_Image)

set(CMAKE_CXX_STANDARD 23)

add_executable(TurnEngine main.cpp
        include/TurnEngine/TurnEngine.hpp
        include/TurnEngine/wrapper/Window.hpp
        include/TurnEngine/wrapper/Color.hpp
        include/TurnEngine/wrapper/Enums.hpp
        include/TurnEngine/wrapper/Event.hpp
        include/TurnEngine/wrapper/Init.hpp
        include/TurnEngine/wrapper/MessageBox.hpp
        include/TurnEngine/wrapper/Pixel.hpp
        include/TurnEngine/wrapper/Renderer.hpp
        include/TurnEngine/wrapper/Shapes.hpp
        include/TurnEngine/wrapper/Surface.hpp
        include/TurnEngine/wrapper/Texture.hpp
        include/TurnEngine/wrapper/Utils.hpp
        include/TurnEngine/ext/Math.hpp
        src/wrapper/Event.cpp
        src/wrapper/MessageBox.cpp
        src/wrapper/Renderer.cpp
        src/wrapper/Surface.cpp
        src/wrapper/Texture.cpp
        src/wrapper/Window.cpp
        src/core/Object.cpp
        include/TurnEngine/core/Object.hpp
        include/TurnEngine/core/Object2D.hpp
        include/TurnEngine/core/Observer.hpp
        include/TurnEngine/core/Subject.hpp
        src/core/Subject.cpp)

target_link_libraries(TurnEngine PUBLIC SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static)

target_include_directories(TurnEngine PRIVATE src)

target_include_directories(TurnEngine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
