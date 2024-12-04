if(ENABLE_DOXYGEN_BUILD)
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