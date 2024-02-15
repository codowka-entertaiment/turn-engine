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

add_library(TurnEngine ${SOURCES} ${INCLUDES})
add_library(TurnEngine::TurnEngine ALIAS TurnEngine)

set(package_files include/ src/ CMakeLists.txt LICENSE)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/TurnEngine-src.zip
        COMMAND ${CMAKE_COMMAND} -E tar c ${CMAKE_CURRENT_BINARY_DIR}/TurnEngine-src.zip --format=zip -- ${package_files}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${package_files})

add_custom_target(TurnEngine_package DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/TurnEngine-src.zip)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(TARGETS TurnEngine SDL2main SDL2-static SDL2_image
        EXPORT TurnEngineTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(EXPORT TurnEngineTargets
        NAMESPACE TurnEngine::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/TurnEngine")

configure_package_config_file(
        cmake/TurnEngineConfig.cmake.in
        "${PROJECT_BINARY_DIR}/TurnEngineConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/TurnEngine")

install(FILES "${PROJECT_BINARY_DIR}/TurnEngineConfig.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/TurnEngine")

install(FILES "${PROJECT_BINARY_DIR}/TurnEngineConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/TurnEngine")

install(DIRECTORY include/turn-engine
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING
        PATTERN "*.hpp")

target_link_libraries(TurnEngine PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static)

# Math tests

file(GLOB_RECURSE MATH_TESTS_SOURCES
        "tests/MathTests.cpp"
)

add_executable(MathTests ${MATH_TESTS_SOURCES})
target_include_directories(MathTests PUBLIC include)
target_link_libraries(MathTests PRIVATE Catch2::Catch2WithMain)