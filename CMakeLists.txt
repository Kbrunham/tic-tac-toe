cmake_minimum_required(VERSION 3.20)

project(cmake_example
        VERSION 1.0
        DESCRIPTION "cmake example"
        LANGUAGES CXX
        )

# Set the minimum required C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include build common macros
message("INFO: Including CMake bcommon")
include("${CMAKE_CURRENT_SOURCE_DIR}/extern/cmake_helpers/bcommon.cmake")

# Set folder support for use with IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Enable testing
include(CTest)

# Include 3rd party libraries from source tree

# Add Backward
set (Backward_DIR "${PROJECT_SOURCE_DIR}/extern/backward-cpp")
find_package(Backward)
message(STATUS "Backward include dir: ${BACKWARD_INCLUDE_DIRS}")

# Add boost
# Set default boost root as /boost in the project source directory
if (NOT BOOST_ROOT)
    set(BOOST_ROOT "${PROJECT_SOURCE_DIR}/boost")
endif ()
find_package(Boost 1.86 REQUIRED)
message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost library dir: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")

# Add Google Test
include(GoogleTest)
# Disable installing googletest
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
# Prevent Google Test from modifying compiler/linker options (https://crascit.com/2015/07/25/cmake-gtest/)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Force building GoogleTest as static, but then leave BUILD_SHARED_LIBS to control
# defaults for the rest of the project`
set(__TEMP_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
set(BUILD_SHARED_LIBS ${__TEMP_BUILD_SHARED_LIBS} CACHE BOOL "" FORCE)

# Add cxxopts
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/cxxopts" "extern/cxxopts" EXCLUDE_FROM_ALL)

# Add plog
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/plog" "extern/plog" EXCLUDE_FROM_ALL)

# Add source to this project's executable.
add_executable(main)
target_include_directories(main PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(main PUBLIC Backward::Backward)
target_link_libraries(main PUBLIC Boost::headers)
target_link_libraries(main PUBLIC cxxopts)
target_link_libraries(main PUBLIC plog)

set(MAIN_TARGET_SOURCES
        "${PROJECT_SOURCE_DIR}/extern/backward-cpp/backward.cpp"
        "src/game_board.cpp"
        "src/game_board_utils.cpp"
        "src/game_env.cpp"
        "src/game_move.cpp"
)

target_sources(main PRIVATE ${MAIN_TARGET_SOURCES})
target_sources(main PRIVATE "main.cpp")

project_add_test(
        # Exe name
        main_test1

        # Source files. Semicolon separated
        "test/test_game_board.cpp"

        # Libs. Semicolon separated
        "Boost::headers;cxxopts;plog"
)
target_include_directories(main_test1 PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_sources(main_test1 PRIVATE ${MAIN_TARGET_SOURCES})
