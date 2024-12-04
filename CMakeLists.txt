cmake_minimum_required(VERSION 3.29..3.31)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Define the project and specify C++ as the language
project("SCLP" VERSION 0.0.0 LANGUAGES CXX)
set(SCLP_LIBRARY_NAME "sclp")

option(ENABLE_TESTING "Enable building and running tests" ON)
if(ENABLE_TESTING)
	option(ENABLE_CDASH "Enable CDash reporting (requires ENABLE_TESTING)" ON)
endif()
option(ENABLE_DOXYGEN_BUILD "Enable Doxygen build" OFF)
option(ENABLE_CLANG_TIDY "Enable Clang-Tidy" OFF)
option(ENABLE_CPPCHECK "Enable CppCheck" OFF)

#set(BUILD_SHARED_LIBS STATIC)
set(CMAKE_BUILD_PARALLEL_LEVEL 16)
include(CMakeScripts.cmake)
add_subdirectory(src)

if(ENABLE_TESTING)
	if(ENABLE_CDASH)
		include(CTest)
	endif()
	enable_testing()
	add_subdirectory(test)
endif()


# Setup Doxygen
include(CMakeDoxygen.cmake)

# Enable tools: Clang-Tidy and CppCheck
enable_tool("clang-tidy" ENABLE_CLANG_TIDY "clang-tidy"
			"CMAKE_CXX_CLANG_TIDY \"\${CLANG_TIDY_EXE};-checks=*, -clang-analyzer-*\""
			"clang-tidy not found, unable to run clang-tidy")

enable_tool("cppcheck" ENABLE_CPPCHECK "cppcheck"
			"CMAKE_CXX_CPPCHECK \"\${CPPCHECK_EXE};--enable=all\""
			"cppcheck not found, unable to run cppcheck")
