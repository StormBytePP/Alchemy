#include <Alchemy/media/registry.hxx>
#include <StormByte/test_handlers.h>
#include <StormByte/multimedia/stream.hxx>

using namespace Alchemy::Media;

int stream_video_test() {
	int result = 0;
	auto expected_codec = Registry::CodecInfo("hevc");
	auto stream = StormByte::Multimedia::Stream::Create(expected_codec.value());
	if (!stream) {
		std::cerr << "Stream not created correctly" << std::endl;
		result++;
	}

	std::cout << "Stream: " << stream->Codec()->Name() << " (" << StormByte::Multimedia::Media::TypeToString(stream->Codec()->Type()) << ") " << stream->Codec()->Description() << std::endl;

	RETURN_TEST("stream_video_test", result);
}

int stream_audio_test() {
	int result = 0;
	auto expected_codec = Registry::CodecInfo("ac3");
	auto stream = StormByte::Multimedia::Stream::Create(expected_codec.value());
	if (!stream) {
		std::cerr << "Stream not created correctly" << std::endl;
		result++;
	}

	std::cout << "Stream: " << stream->Codec()->Name() << " (" << StormByte::Multimedia::Media::TypeToString(stream->Codec()->Type()) << ") " << stream->Codec()->Description() << std::endl;

	RETURN_TEST("stream_video_test", result);
}

int stream_subtitle_test() {
	int result = 0;
	auto expected_codec = Registry::CodecInfo("subrip");
	auto stream = StormByte::Multimedia::Stream::Create(expected_codec.value());
	if (!stream) {
		std::cerr << "Stream not created correctly" << std::endl;
		result++;
	}

	std::cout << "Stream: " << stream->Codec()->Name() << " (" << StormByte::Multimedia::Media::TypeToString(stream->Codec()->Type()) << ") " << stream->Codec()->Description() << std::endl;

	RETURN_TEST("stream_video_test", result);
}

int main() {
	int counter = 0;
	try {
		counter += stream_video_test();
		counter += stream_audio_test();
		counter += stream_subtitle_test();
	}
	catch (...) {
		std::cerr << "ERROR: Unknown exception" << std::endl;
		counter++;
	}
	return counter;
}