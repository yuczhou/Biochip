include_directories(${COMMON_INCLUDES})

file(GLOB SRC_FILES *.cpp)
add_executable(${PROJECT_NAME_STR} ${SRC_FILES})

add_library(${PROJECT_LIB_NAME} ${SRC_FILES})