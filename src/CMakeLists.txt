add_library(${SCLP_LIBRARY_NAME} "action.cpp" "effect.cpp" "entity.cpp" "health.cpp" "identifier.cpp" "logentry.cpp" "logparser.cpp" "parsing_utils.cpp" "quant.cpp" "vector.cpp")
set_target_properties(${SCLP_LIBRARY_NAME} PROPERTIES CXX_STANDARD 23)

target_include_directories(${SCLP_LIBRARY_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link the nlohmann_json library using the target name variable
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${SCLP_LIBRARY_NAME} PRIVATE nlohmann_json::nlohmann_json)