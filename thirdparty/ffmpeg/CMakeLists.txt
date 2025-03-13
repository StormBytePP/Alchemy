find_program(FFMPEG_EXECUTABLE ffmpeg)
find_program(FFPROBE_EXECUTABLE ffprobe)
set(FFMPEG_EXECUTABLE_NOW "${FFMPEG_EXECUTABLE}")

if (NOT FFMPEG_EXECUTABLE OR NOT FFPROBE_EXECUTABLE)
	if(WIN32)
		message(STATUS "FFmpeg not found, downloading FFmpeg. This might take a while...")
		include(FetchContent)

		FetchContent_Declare(ffmpeg
		URL https://www.gyan.dev/ffmpeg/builds/ffmpeg-release-full.7z
		DOWNLOAD_EXTRACT_TIMESTAMP false
		)

		FetchContent_MakeAvailable(ffmpeg)

		install(FILES
			"${ffmpeg_SOURCE_DIR}/bin/ffmpeg.exe"
			"${ffmpeg_SOURCE_DIR}/bin/ffprobe.exe"
			DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
		)

		set(FFMPEG_EXECUTABLE "bin" / "ffmpeg.exe")
		set(FFPROBE_EXECUTABLE "bin" / "ffprobe.exe")
		set(FFMPEG_EXECUTABLE_NOW "${ffmpeg_SOURCE_DIR}/bin/ffmpeg.exe")
	else()
		message(FATAL_ERROR "FFmpeg not found and not on Windows, aborting.")
	endif()
else()
	message(STATUS "Found FFmpeg: ${FFMPEG_EXECUTABLE}")
	message(STATUS "Found FFprobe: ${FFPROBE_EXECUTABLE}")
endif()

mark_as_advanced(FFMPEG_EXECUTABLE)
mark_as_advanced(FFPROBE_EXECUTABLE)

# Get ffmpeg's codecs into a string
execute_process(
	COMMAND "${FFMPEG_EXECUTABLE_NOW}" -codecs -hide_banner
	OUTPUT_VARIABLE FFMPEG_CODEC_REGISTRY
)

# Get ffmpeg's formats into a string
execute_process(
	COMMAND "${FFMPEG_EXECUTABLE_NOW}" -formats -hide_banner
	OUTPUT_VARIABLE FFMPEG_FORMAT_REGISTRY
)

# Get ffmpeg's version into a string (can't hide banner in version)
execute_process(
	COMMAND "${FFMPEG_EXECUTABLE_NOW}" -version
	OUTPUT_VARIABLE FFMPEG_VERSION
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
unset(FFMPEG_EXECUTABLE_NOW)

# Convert codec info to string for initialize unordered_map<codec,flags>
# Regex for the whole text do not work (tested already) so we need to split the text into lines
# Split the variable into lines
string(REPLACE "\n" ";" CODEC_LINES "${FFMPEG_CODEC_REGISTRY}")
set(FFMPEG_CODEC_REGISTRY "")
# Loop through each line
foreach(LINE IN LISTS CODEC_LINES)
	set(_FLAGS "")
	set(_CODEC "")
	string(REGEX MATCHALL "^[ ]([A-Z.]+) ([A-Za-z0-9_]+).*$" _MATCHED_CODEC "${LINE}")
	if (NOT _MATCHED_CODEC)
		continue()
	endif()
	set(_FLAGS "${CMAKE_MATCH_1}")
	set(_CODEC "${CMAKE_MATCH_2}")
	set(FFMPEG_CODEC_REGISTRY "${FFMPEG_CODEC_REGISTRY}{\"${_CODEC}\",\"${_FLAGS}\"},")
endforeach()
unset(CODEC_LINES)

# Convert format info to string for initialize unordered_map<codec,flags>
# Regex for the whole text do not work (tested already) so we need to split the text into lines
# Split the variable into lines
string(REPLACE "\n" ";" CODEC_LINES "${FFMPEG_FORMAT_REGISTRY}")
set(FFMPEG_FORMAT_REGISTRY "")
# Loop through each line
foreach(LINE IN LISTS CODEC_LINES)
	set(_FLAGS "")
	set(_FORMAT "")
	string(REGEX MATCHALL "^[ ]([A-Z. ]+) ([A-Za-z0-9_]+).*$" _MATCHED_CODEC "${LINE}")
	if (NOT _MATCHED_CODEC)
		continue()
	endif()
	set(_FLAGS "${CMAKE_MATCH_1}")
	set(_FORMAT "${CMAKE_MATCH_2}")
	set(FFMPEG_FORMAT_REGISTRY "${FFMPEG_FORMAT_REGISTRY}{\"${_FORMAT}\",\"${_FLAGS}\"},")
endforeach()
unset(CODEC_LINES)

# Match the entire "ffmpeg version 7.1" line and capture just the version number
string(REGEX MATCH "^ffmpeg version ([0-9]+\\.[0-9]+(\\.[0-9]+)?)" _MATCHED_VERSION "${FFMPEG_VERSION}")

# Overwrite FFMPEG_VERSION with just the version number
set(FFMPEG_VERSION "${CMAKE_MATCH_1}")

# Autogenerate a file for setting the FFMpeg paths
configure_file(
    ${CMAKE_SOURCE_DIR}/lib/private/ffmpeg_info.cxx.in
    ${CMAKE_BINARY_DIR}/ffmpeg_info.cxx
    @ONLY
)
unset(FFMPEG_CODECS_REGISTRY)
unset(FFMPEG_FORMAT_REGISTRY)
unset(FFMPEG_VERSION)