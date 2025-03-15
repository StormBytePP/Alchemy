#include <Alchemy/media/ffmpeg.hxx>
#include <Alchemy/media/codec.hxx>
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

int codec_hevc_test() {
	const auto& hevc_codec = Media::Codec::Registry::Info("hevc");
	if (!hevc_codec) {
		std::cerr << "HEVC not supported and it should!" << std::endl;
		RETURN_TEST("codec_registry_test", 1);
	}
	
	const auto& hevc_codec_info = Media::Codec::Registry::Info(Media::Codec::Name::H265);
	if (!hevc_codec_info) {
		std::cerr << "HEVC not supported and it should!" << std::endl;
		RETURN_TEST("codec_registry_test", 1);
	}

	if (!hevc_codec_info.value()->s_flags.EncodeSupported()) {
		std::cerr << "HEVC encode not supported and it should!" << std::endl;
		RETURN_TEST("codec_registry_test", 1);
	}

	std::cout << "HEVC codec (type " << StormByte::Multimedia::Media::TypeToString(hevc_codec_info.value()->s_type) << ") found and encode supported." << std::endl;

	RETURN_TEST("codec_registry_test", 0);
}

int main() {
	int counter = 0;
	try {
		counter += version_test();
		counter += codec_hevc_test();
	}
	catch (...) {
		std::cerr << "ERROR: Unknown exception" << std::endl;
		counter++;
	}
	return counter;
}