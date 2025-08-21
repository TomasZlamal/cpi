cmake_minimum_required(VERSION 3.15)
project(cpi VERSION 0.1)

add_executable(cpi main.cc src/setup.cc src/initcpi.cc src/cclass.cc src/cpi_toml.cc)

option(BUILD_WITH_RANG "Build with Rang" ON)
if (BUILD_WITH_RANG)
  target_compile_definitions(cpi PRIVATE CPI_COMPILE_WITH_RANG)
endif()

include(FetchContent)
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)
target_link_libraries(cpi tomlplusplus::tomlplusplus)
