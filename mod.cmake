# Macro to set up testing
macro(setup_testing TEST_OPTION CDASH_OPTION)
	if(${TEST_OPTION})
		if(${CDASH_OPTION})
			include(CTest)
			set(CTEST_DROP_METHOD "http")
			set(CTEST_DROP_SITE "localhost")
			set(CTEST_DROP_LOCATION "/CDash/submit.php?project=YourProjectName")
			set(CTEST_DROP_SITE_CDASH TRUE)
		else()
			enable_testing()
		endif()
		add_subdirectory(test)
		set(CTEST_PROGRESS_OUTPUT TRUE)
	endif()
endmacro()

# Function to target tests from a specific level
function(TARGET_TESTS_OF LEVEL_FOLDER)
	file(GLOB TEST_SOURCES "${LEVEL_FOLDER}/*.cpp")
	foreach(S ${TEST_SOURCES})
		get_filename_component(T ${S} NAME_WE)
		add_executable(${T} ${S})
		set_target_properties(${T} PROPERTIES CXX_STANDARD 23 LABELS ${LEVEL_FOLDER})
		target_link_libraries(${T} PRIVATE GTest::gtest GTest::gtest_main ${SCLP_LIBRARY_NAME})
		gtest_discover_tests(${T})
	endforeach()
endfunction()

# Function to target tests from all levels
function(TARGET_TESTS LEVEL_PREFIX)
	file(GLOB TEST_LEVELS "${CMAKE_CURRENT_LIST_DIR}/${LEVEL_PREFIX}_*")
		set(DIR_LEVELS "")
		foreach(LEVEL_FOLDER ${TEST_LEVELS})
			if(IS_DIRECTORY ${LEVEL_FOLDER})
				list(APPEND DIR_LEVELS ${LEVEL_FOLDER})
			endif()
		endforeach()
	set(TEST_LEVELS ${DIR_LEVELS})

	# Add tests
	foreach(LEVEL_FOLDER ${TEST_LEVELS})
		TARGET_TESTS_OF(${LEVEL_FOLDER})
	endforeach()
endfunction()

# Function to set up Doxygen
function(setup_doxygen DOXYGEN_OPTION)
	if(${DOXYGEN_OPTION})
		find_package(Doxygen REQUIRED)
		if(DOXYGEN_FOUND)
			set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
			set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

			configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

			add_custom_target(doc_doxygen ALL
				COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
				WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
				COMMENT "Generating API documentation with Doxygen"
				VERBATIM
			)
		else()
			message(WARNING "Doxygen not found, unable to generate documentation")
		endif()
	endif()
endfunction()

# Macro to add a tool
macro(enable_tool TOOL_NAME TOOL_OPTION TOOL_FIND_COMMAND TOOL_SET_COMMAND WARNING_MESSAGE)
	if(${TOOL_OPTION})
		find_program(${TOOL_NAME}_EXE NAMES "${TOOL_FIND_COMMAND}")
		if(${TOOL_NAME}_EXE)
			set(${TOOL_SET_COMMAND})
		else()
			message(WARNING "${WARNING_MESSAGE}")
		endif()
	endif()
endmacro()