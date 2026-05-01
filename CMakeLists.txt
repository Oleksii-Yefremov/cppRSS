# Sets the minimum version of CMake required
cmake_minimum_required(VERSION 3.15)
project(CPP_RSS LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Avoid meson requirement for libpsl when building cpr on Windows.
set(CPR_CURL_USE_LIBPSL OFF CACHE BOOL "" FORCE)
# Avoid Perl-related warning from curl docs/manpage generation.
set(BUILD_LIBCURL_DOCS OFF CACHE BOOL "" FORCE)
set(ENABLE_CURL_MANUAL OFF CACHE BOOL "" FORCE)
set(BUILD_MISC_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.14.2
)
FetchContent_MakeAvailable(cpr)
if (MSVC AND TARGET cpr)
    target_compile_options(cpr PRIVATE /wd4244)
endif()

add_executable(cppRSS main.cpp)
target_link_libraries(cppRSS PRIVATE cpr::cpr)