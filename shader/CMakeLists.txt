# this CMakeLists.txt file uses code from the following website
# https://thatonegamedev.com/cpp/cmake/how-to-compile-shaders-with-cmake/

function(add_shaders TARGET_NAME)
	set(SHADER_SOURCE_FILES ${ARGN})

	list(LENGTH SHADER_SOURCE FILES_COUNT)
	if(FILE_COUNT EQUAL 0)
		message(FATAL_ERROR "No source files exist, cannot create shaders.")
	endif()

	set(SHADER_COMMANDS)
	set(SHADER_PRODUCTS)
	foreach(SHADER_SOURCE IN LISTS SHADER_SOURCE_FILES)
		cmake_path(ABSOLUTE_PATH SHADER_SOURCE NORMALIZE)
		cmake_path(GET SHADER_SOURCE FILENAME SHADER_NAME)

		list(APPEND SHADER_COMMAND COMMAND)
		list(APPEND SHADER_COMMAND Vulkan::glslc)
		list(APPEND SHADER_COMMAND "${SHADER_SOURCE}")
		list(APPEND SHADER_COMMAND "-o")
		list(APPEND SHADER_COMMAND "{CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.spv")

		list(APPEND SHADER_PRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.spv")
	endforeach()

	add_custom_target(${TARGET_NAME} ALL
		${SHADER_COMMANDS}
		COMMENT "Compling Shaders [${TARGET_NAME}]"
		SOURCES ${SHADER_SOURCE_FILES}
		BYPRODUCTS ${SHADER_PRODUCTS}
	)
endfunction()


