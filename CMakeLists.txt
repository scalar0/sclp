cmake_minimum_required(VERSION 3.31.1)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Define the project and specify C++ as the language
project("SCLP" LANGUAGES CXX VERSION 0.0.0)
set(SCLP_LIBRARY_NAME "sclp")

include(mod.cmake)
add_subdirectory(src)
include_directories(include)

option(ENABLE_TESTING "Enable building tests" ON)
option(ENABLE_CDASH "Enable CDash reporting" OFF)
option(ENABLE_DOXYGEN_BUILD "Enable Doxygen build" OFF)
option(ENABLE_CLANG_TIDY "Enable Clang-Tidy" OFF)
option(ENABLE_CPPCHECK "Enable CppCheck" OFF)

# Setup testing and CDash
setup_testing(ENABLE_TESTING ENABLE_CDASH)

# Setup Doxygen
setup_doxygen(ENABLE_DOXYGEN_BUILD)

# Enable tools: Clang-Tidy and CppCheck
enable_tool("clang-tidy" ENABLE_CLANG_TIDY "clang-tidy" 
			"CMAKE_CXX_CLANG_TIDY \"\${CLANG_TIDY_EXE};-checks=*, -clang-analyzer-*\""
			"clang-tidy not found, unable to run clang-tidy")

enable_tool("cppcheck" ENABLE_CPPCHECK "cppcheck" 
			"CMAKE_CXX_CPPCHECK \"\${CPPCHECK_EXE};--enable=all\""
			"cppcheck not found, unable to run cppcheck")
