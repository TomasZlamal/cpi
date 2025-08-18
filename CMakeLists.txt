cmake_minimum_required(VERSION 3.15)
project(cpi VERSION 0.1)

add_executable(cpi main.cc src/setup.cc src/initcpi.cc)
include(FetchContent)
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)
target_link_libraries(cpi tomlplusplus::tomlplusplus)
