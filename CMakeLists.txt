cmake_minimum_required(VERSION 3.16)
project(simple_linear_regression)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_library(simple_linear_regression src/slr.cpp)
add_executable(test
        main.cpp)
target_link_libraries(test simple_linear_regression)
install(TARGETS simple_linear_regression DESTINATION /usr/local/lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION /usr/local/include/
        FILES_MATCHING PATTERN "*.h")