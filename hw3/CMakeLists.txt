cmake_minimum_required(VERSION 3.16)

project(Advanced_programming LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
Include(FetchContent)

FetchContent_Declare(
 Catch2
 GIT_REPOSITORY https://github.com/catchorg/Catch2.git
 GIT_TAG v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(Advanced_programming main.cpp)
target_link_libraries(Advanced_programming Catch2::Catch2WithMain)
include(GNUInstallDirs)
install(TARGETS Advanced_programming
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
