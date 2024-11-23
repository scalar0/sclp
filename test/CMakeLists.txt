find_package(GTest REQUIRED)
include(GoogleTest)

# Define test levels
file(GLOB TEST_LEVELS "${CMAKE_CURRENT_LIST_DIR}/lvl_*")
set(DIR_LEVELS "")
foreach(L ${TEST_LEVELS})
	if(IS_DIRECTORY ${L})
	list(APPEND DIR_LEVELS ${L})
	endif()
endforeach()
set(TEST_LEVELS ${DIR_LEVELS})

# Function to add tests from a specific level
function(add_tests_from_level L)
	file(GLOB TEST_SOURCES "${L}/*.cpp")
	foreach(S ${TEST_SOURCES})
		get_filename_component(T ${S} NAME_WE)
		add_executable(${T} ${S})
		set_target_properties(${T} PROPERTIES CXX_STANDARD 23 LABELS ${L})
	
		# Link necessary libraries
		target_link_libraries(${T} PRIVATE GTest::gtest GTest::gtest_main ${SCLP_LIBRARY_NAME})

		# Register the test with CTest
		gtest_discover_tests(${T})
	endforeach()
endfunction()

# Add tests for each level
foreach(L ${TEST_LEVELS})
	add_tests_from_level(${L})
endforeach()
