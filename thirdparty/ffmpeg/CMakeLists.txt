find_program(FFMPEG_EXECUTABLE ffmpeg)
find_program(FFPROBE_EXECUTABLE ffprobe)

if (NOT FFMPEG_EXECUTABLE OR NOT FFPROBE_EXECUTABLE)
	if(WIN32)
		message(STATUS "FFmpeg not found, downloading FFmpeg. This might take a while...")
		include(FetchContent)

		FetchContent_Declare(ffmpeg
		URL https://www.gyan.dev/ffmpeg/builds/ffmpeg-release-full.7z
		DOWNLOAD_EXTRACT_TIMESTAMP false
		)

		FetchContent_MakeAvailable(ffmpeg)

		message(STATUS "FFmpeg downloaded to: ${ffmpeg_SOURCE_DIR}")

		install(FILES
			"${ffmpeg_SOURCE_DIR}/bin/ffmpeg.exe"
			"${ffmpeg_SOURCE_DIR}/bin/ffprobe.exe"
			DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
		)

		set(FFMPEG_EXECUTABLE "\"bin\" / \"ffmpeg.exe\"")
		set(FFPROBE_EXECUTABLE "\"bin\" / \"ffprobe.exe\"")
	else()
		message(FATAL_ERROR "FFmpeg not found and not on Windows, aborting.")
	endif()
else()
	message(STATUS "Found FFmpeg: ${FFMPEG_EXECUTABLE}")
	message(STATUS "Found FFprobe: ${FFPROBE_EXECUTABLE}")
endif()

mark_as_advanced(FFMPEG_EXECUTABLE)
mark_as_advanced(FFPROBE_EXECUTABLE)

configure_file(
    ${CMAKE_SOURCE_DIR}/lib/private/ffmpeg_info.cxx.in
    ${CMAKE_BINARY_DIR}/ffmpeg_info.cxx
    @ONLY
)
configure_file(
    ${CMAKE_SOURCE_DIR}/lib/private/ffprobe_info.cxx.in
    ${CMAKE_BINARY_DIR}/ffprobe_info.cxx
    @ONLY
)