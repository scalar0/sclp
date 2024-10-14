# CMakeList.txt : CMake project for swtor-combatlog-parser, now creating a library.
#
cmake_minimum_required(VERSION 3.29)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Define the project and specify C++ as the language
project("sclp" LANGUAGES CXX)

# Include directories
include_directories("include")

# Add source files to the library (static or shared)
add_executable(${PROJECT_NAME}
  "src/logparser.cpp"
  "src/vector.cpp"
  "src/identifier.cpp"
  "src/entity.cpp"
  "src/health.cpp"
  "src/effect.cpp"
  "src/action.cpp"
  "src/quant.cpp"
  "src/logentry.cpp"
  "src/parsing_utils.cpp"
 "src/main.cpp")

# Set target properties for C++ standard
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)

# Link the nlohmann_json library using the target name variable
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Specify output directories for the library
set_target_properties(${PROJECT_NAME} PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Optional: Add install rules if you want to install the library and headers
install(TARGETS ${PROJECT_NAME}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)
