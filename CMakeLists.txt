# CMakeList.txt : CMake project for swtor-combatlog-parser, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.26)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Define the project and specify C++ as the language
project("sclp" LANGUAGES CXX)

# Set a variable for the target name
set(TARGET_NAME sclp)

# Include directories
include_directories("include")

# Add source to this project's executable using the variable
add_executable(${TARGET_NAME}
  "src/parser.cpp"
  "src/vector.cpp"
  "src/identifier.cpp"
  "src/entity.cpp"
  "src/health.cpp"
  "src/effect.cpp"
  "src/action.cpp"
  "src/quant.cpp"
  "src/logentry.cpp"
  "src/parsing_utils.cpp"
)

# Set target properties for C++ standard and linker language using the variable
set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 23)
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Link the nlohmann_json library using the target name variable
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)

# TODO: Add tests and install targets if needed.
