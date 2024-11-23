cmake_minimum_required(VERSION 3.31.1)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Define the project and specify C++ as the language
project("sclp" LANGUAGES CXX)
set(SCLP_MAIN_ENTRY_POINT_NAME "sclp_main")
set(SCLP_LIBRARY_NAME "sclp")

add_subdirectory(src)
include_directories(include)

add_executable(${SCLP_MAIN_ENTRY_POINT_NAME} "src/main.cpp")

target_link_libraries(${SCLP_MAIN_ENTRY_POINT_NAME} PRIVATE ${SCLP_LIBRARY_NAME})

# Specify output directories for the library
set_target_properties(${SCLP_MAIN_ENTRY_POINT_NAME} PROPERTIES
	CXX_STANDARD 23
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

option(ENABLE_TESTING "Enable building tests" ON)
option(ENABLE_CDASH "Enable CDash reporting" OFF)
if (ENABLE_TESTING)
	if (ENABLE_CDASH)
		include(CTest)
		set(CTEST_DROP_METHOD "http")
		set(CTEST_DROP_SITE "localhost")
		set(CTEST_DROP_LOCATION "/CDash/submit.php?project=YourProjectName")
		set(CTEST_DROP_SITE_CDASH TRUE)
	else()
		enable_testing()
	endif()
	add_subdirectory(test)
endif()


# Optional: Add install rules if you want to install the library and headers
install(TARGETS ${SCLP_MAIN_ENTRY_POINT_NAME}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)
