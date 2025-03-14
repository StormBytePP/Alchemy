#include <Alchemy/media/ffmpeg.hxx>
#include <StormByte/test_handlers.h>
#include <StormByte/exception.hxx>
#include <StormByte/util/system.hxx>

using namespace Alchemy;

int version_test() {
	int result = 0;
	try {
		const std::string version = Media::FFMpeg::Version();
		std::cout << "FFMpeg version: \"" << version << "\"" << std::endl;
		
		ASSERT_FALSE("version_test", version.empty());
	}
	catch (const StormByte::Exception& ex) {
		std::cerr << "ERROR: " << ex.what() << std::endl;
		result++;
	}
	catch (const std::exception& ex) {
		std::cerr << "ERROR: Unknown exception: " << ex.what() << std::endl;
		result++;
	}

	RETURN_TEST("version_test", result);
}

int codec_registry_test() {
	int result = 0;
	try {
		const auto& codec_registry = Media::FFMpeg::CodecRegistry();
		const auto& hevc_codec = codec_registry.at("hevc");

		std::cout << "Can encode HEVC: " << std::boolalpha << hevc_codec->Flags().EncodeSupported() << std::endl;

		ASSERT_TRUE("codec_registry_test", hevc_codec->Flags().EncodeSupported());
	}
	catch (const StormByte::Exception& ex) {
		std::cerr << "ERROR: " << ex.what() << std::endl;
		result++;
	}
	catch (const std::exception& ex) {
		std::cerr << "ERROR: Unknown exception: " << ex.what() << std::endl;
		result++;
	}

	RETURN_TEST("codec_registry_test", result);
}

int main() {
	int counter = 0;
	try {
		counter += version_test();
		counter += codec_registry_test();
	}
	catch (...) {
		std::cerr << "ERROR: Unknown exception" << std::endl;
		counter++;
	}
	return counter;
}