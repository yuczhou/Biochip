include_directories(${COMMON_INCLUDES} ${LP_SOLVE_SRC_DIR})

file(GLOB SRC_FILES *.cpp)
add_executable(${PROJECT_NAME_STR} ${SRC_FILES})
add_library(${PROJECT_LIB_NAME} ${SRC_FILES})

#lp_solve
target_link_libraries(${PROJECT_NAME_STR}
    ${LP_SOLVE_LIB_DIR}/liblpsolve55.a
    dl)