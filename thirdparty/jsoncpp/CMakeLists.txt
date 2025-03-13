option(WITH_SYSTEM_JSONCPP "Use system JsonCpp" OFF)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
if (WITH_SYSTEM_JSONCPP)
	find_package (JsonCpp REQUIRED)
	message(STATUS "Found JsonCpp: ${jsoncpp_VERSION}")
else()
	# Lowercase prefixes are needed by CMake
	set(BUILD_SHARED_LIBS ON)
	set(BUILD_STATIC_LIBS OFF)
	set(BUILD_STATIC_TESTING OFF)
	set(JSONCPP_WITH_TESTS OFF)
	add_subdirectory(src)

	if (WIN32)
		install(TARGETS jsoncpp_lib
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		)
	endif()
	add_library(JsonCpp::JsonCpp ALIAS jsoncpp_lib)

	message(STATUS "Found JsonCpp: bundled")
endif()

