cmake_minimum_required(VERSION 3.15.0)
project(simplediff VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Setup directories ============================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# Build executables ============================================================
add_subdirectory(flags)
add_executable(simplediff main.cpp)
target_link_libraries(simplediff PRIVATE flags)

# Add tests ====================================================================
option(BUILD_SIMPLEDIFF_TESTS "Enable Testing for simplediff" OFF)
if (BUILD_SIMPLEDIFF_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
