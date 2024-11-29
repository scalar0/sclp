find_package(GTest REQUIRED)
include(GoogleTest)

TARGET_TESTS("lvl")

add_executable(test_memory test_memory.cpp)
set_target_properties(test_memory PROPERTIES CXX_STANDARD 23 LABELS MEMORY_CHECK)
target_link_libraries(test_memory PRIVATE ${SCLP_LIBRARY_NAME})
