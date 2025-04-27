
cmake_minimum_required(VERSION 3.8)

project("DirrDiff")

add_executable(${PROJECT_NAME} "DiffResults.hpp" "DiffResults.cpp" "Calculator.hpp" "Calculator.cpp" "Main.cpp")

if(CMAKE_VERSION VERSION_GREATER 3.12)
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "dir_diff")
