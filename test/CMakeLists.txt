option(ENABLE_TEST "Enable Unit Tests" OFF)
if(ENABLE_TEST AND NOT STORMBYTE_AS_DEPENDENCY)
	add_executable(CodecRegistryTests codec_registry_test.cxx)
	target_link_libraries(CodecRegistryTests Alchemy)
	add_test(NAME CodecRegistryTests COMMAND CodecRegistryTests)

	add_executable(StreamTests stream_test.cxx)
	target_link_libraries(StreamTests Alchemy)
	add_test(NAME StreamTests COMMAND StreamTests)

	add_executable(FFMpegTests ffmpeg_test.cxx)
	target_link_libraries(FFMpegTests Alchemy)
	add_test(NAME FFMpegTests COMMAND FFMpegTests)
endif()