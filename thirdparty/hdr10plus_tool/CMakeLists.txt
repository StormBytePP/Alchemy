find_program(HDR10PLUS_TOOL_EXECUTABLE hdr10plus_tool)

if (NOT HDR10PLUS_TOOL_EXECUTABLE)
	if(WIN32)
		message(STATUS "hdr10plus_tool not found, will be compiled from sources")
		add_custom_target(hdr10plus_tool ALL
		cargo install -q --root "${CMAKE_BINARY_DIR}" --path "${CMAKE_CURRENT_LIST_DIR}/src"
		BYPRODUCTS "${CMAKE_BINARY_DIR}/bin/thirdparty/hdr10plus_tool"
		)
		install(FILES "${CMAKE_BINARY_DIR}/bin/hdr10plus_tool.exe" DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/thirdparty")
		set(HDR10PLUS_TOOL_EXECUTABLE "thirdparty\\\\hdr10plus_tool.exe")
	else()
		message(FATAL_ERROR "hdr10plus_tool not found and not on Windows, aborting.")
	endif()
else()
	message(STATUS "Found hdr10plus_tool: ${HDR10PLUS_TOOL_EXECUTABLE}")
endif()

mark_as_advanced(HDR10PLUS_TOOL_EXECUTABLE)

# Autogenerate a file for setting the FFMpeg paths
configure_file(
    ${CMAKE_SOURCE_DIR}/lib/private/hdr10plus_tool_info.cxx.in
    ${CMAKE_BINARY_DIR}/hdr10plus_tool_info.cxx
    @ONLY
)