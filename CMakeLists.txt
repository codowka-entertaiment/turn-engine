cmake_minimum_required(VERSION 3.26.4)
project(turn-engine VERSION 0.0.1)

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
        "src/*.cpp"
)

add_library(TurnEngine STATIC ${SOURCES})
target_link_libraries(TurnEngine PUBLIC SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static)

target_include_directories(TurnEngine PRIVATE src)

target_include_directories(TurnEngine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    cmake_minimum_required(VERSION 3.26.4)

    option(TURN_ENGINE_BUILD_PACKAGE "whether or not the package should build" ON)
    option(TURN_ENGINE_ENABLE_INSTALL "whether or not to enable the install rule" ON)

    if (TURN_ENGINE_BUILD_PACKAGE)
        set(PKG_FILES include/ src/ cmake/ CMakeLists.txt)

        add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/TurnEngine-src.zip
                COMMAND ${CMAKE_COMMAND} -E tar c ${CMAKE_CURRENT_BINARY_DIR}/TurnEngine-src.zip --format=zip -- ${PKG_FILES}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                DEPENDS ${PKG_FILES})

        add_custom_target(TURN_ENGINE_PKG DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/TurnEngine-src.zip)
    endif ()

    if (TURN_ENGINE_ENABLE_INSTALL)
        include(CMakePackageConfigHelpers)
        include(GNUInstallDirs)

        install(TARGETS TurnEngine SDL2main SDL2-static SDL2_image
                EXPORT ${PROJECT_NAME}Targets
                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

        install(EXPORT ${PROJECT_NAME}Targets
                NAMESPACE codowka::
                DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

        configure_package_config_file(
                cmake/TurnEngineConfig.cmake.in
                "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

        install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

        # YYYY.MM.N1 is compatible with YYYY.MM.N2.
        write_basic_package_version_file(
                "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
                COMPATIBILITY SameMinorVersion)

        install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
                DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

        install(DIRECTORY include
                DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                FILES_MATCHING
                PATTERN "*.hpp")
    endif ()
endif ()

# Geometry tests

add_executable(Geo2dTests "tests/Geo2dTests.cpp")
target_link_libraries(Geo2dTests PRIVATE Catch2::Catch2WithMain)

# SDL Graphics wrapper test

add_executable(SdlGraphicsTest "tests_ui/SdlGraphicsTest.cpp")
target_link_libraries(SdlGraphicsTest PRIVATE TurnEngine)
