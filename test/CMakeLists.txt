set(CTEST_PROJECT_NAME ${CMAKE_PROJECT_NAME})
set(CTEST_PARALLEL_LEVEL ${CMAKE_BUILD_PARALLEL_LEVEL})
#set(CTEST_PROGRESS_OUTPUT TRUE)
find_package(GTest REQUIRED)
include(GoogleTest)
include(CTestConfig.cmake)

target_tests("lvl")

add_executable(test_memory test_memory.cpp)
set_target_properties(test_memory
						PROPERTIES
						CXX_STANDARD 23
						LABELS MEMORY_CHECK)
target_link_libraries(test_memory PRIVATE ${SCLP_LIBRARY_NAME})
add_test(NAME "Memory stress test" COMMAND test_memory)

if(${ENABLE_CDASH})
	include(CDashConfig.cmake)
endif()