file(GLOB SRC_FILES "*.cpp")
add_library(${SCLP_LIBRARY_NAME} ${SRC_FILES})
set_target_properties(${SCLP_LIBRARY_NAME} PROPERTIES
	CXX_STANDARD 23
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${SCLP_LIBRARY_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(${SCLP_LIBRARY_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

option(ENABLE_INSTALL "Enable installing targets" OFF)
if(ENABLE_INSTALL)
	# Optional: Add install rules if you want to install the library and headers
	install(TARGETS ${SCLP_LIBRARY_NAME}
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib
		RUNTIME DESTINATION bin
	)

	install(DIRECTORY include/ DESTINATION include)
endif()