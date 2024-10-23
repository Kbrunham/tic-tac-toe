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

# Add boost
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

# Add source to this project's executable.
add_executable(main "main.cpp" "main.h")
target_link_libraries(main Boost::headers)
target_link_libraries(main cxxopts)

project_add_test(
        # Exe name
        main_test1

        # Source files. Semicolon separated
        "test_main.cpp"

        # Libs. Space separated
        Boost::headers
)
