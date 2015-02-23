cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR Biochip)
project(${PROJECT_NAME_STR} C CXX)

if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-g -Wall -Werror -ansi -Wno-deprecated -pedantic -pedantic-errors -Wextra -pthread -std=c++11)
endif()

if(MSVC)
#vc 2012 fix for vararg templates
    set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif()

#-------------------
# set common include folder for module
#-------------------
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}Lib)
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}Test)

# lp solve
set(LP_SOLVE_LIB_DIR ${EXT_PROJECTS_DIR}/lp_solve_5.5/lpsolve55/bin/ux64)
set(LP_SOLVE_SRC_DIR ${EXT_PROJECTS_DIR}/lp_solve_5.5)

#-------------------
# Sub directories
#-------------------
add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)

#-------------------
# Testing
#-------------------
enable_testing()
add_test(${PROJECT_TEST_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_TEST_NAME})
