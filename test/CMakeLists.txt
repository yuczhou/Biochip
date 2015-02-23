include_directories(${COMMON_INCLUDES} ${LP_SOLVE_SRC_DIR})

#-------------------
# Test
#-------------------
add_definitions(${MSVC_COMPILER_DEFS})
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES} ${PROJECT_LIB_DIR})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest)


if(NOT WIN32)
	target_link_libraries(${PROJECT_TEST_NAME}
		${GTEST_LIBS_DIR}/libgtest.a
		${GTEST_LIBS_DIR}/libgtest_main.a
		pthread
		${PROJECT_LIB_NAME}
		${LP_SOLVE_LIB_DIR}/liblpsolve55.a
		dl
	)
else()

	target_link_libraries(${PROJECT_TEST_NAME}
	       debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
	target_link_libraries(${PROJECT_TEST_NAME}
	       debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
endif()