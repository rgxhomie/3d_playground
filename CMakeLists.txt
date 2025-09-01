# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.20)

# Set the project name, version, and language
project(
    "3d_playground"
    VERSION 0.0.1
    LANGUAGES CXX
)

# --------------------------------------------------------------

# add near the top (after project(...))
include(FetchContent)

# fetch GLFW at configure time
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8          # use a specific tag; bump when you want
)
# turn off stuff we don't need from GLFW's own build
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# --------------------------------------------------------------

# Add the executable
add_executable(playground src/main.cpp)

target_compile_features(playground PRIVATE cxx_std_20)

# link it to your app
target_link_libraries(playground PRIVATE glfw)
target_link_libraries(playground PRIVATE glad)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
