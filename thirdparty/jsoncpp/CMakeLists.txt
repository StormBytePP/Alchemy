option(WITH_SYSTEM_JSONCPP "Use system JsonCpp" OFF)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
if (WITH_SYSTEM_JSONCPP)
	find_package (JsonCpp REQUIRED)
	message(STATUS "Found JsonCpp: ${jsoncpp_VERSION}")
else()
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	add_library(JsonCpp SHARED
		jsoncpp.cpp
		json/json.h
		json/json-forwards.h
	)
	add_library(JsonCpp::JsonCpp ALIAS JsonCpp)
	target_include_directories(JsonCpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

	if (WIN32)
		install(TARGETS JsonCpp
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		)
	endif()

	message(STATUS "Found JsonCpp: bundled")
endif()

