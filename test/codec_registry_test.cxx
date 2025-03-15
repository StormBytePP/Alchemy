#include <Alchemy/media/registry.hxx>
#include <StormByte/test_handlers.h>
#include <StormByte/exception.hxx>
#include <StormByte/util/system.hxx>

using namespace Alchemy::Media;

int codec_hevc_test() {
	const auto& hevc_codec = Registry::CodecInfo("hevc");
	if (!hevc_codec) {
		std::cerr << "HEVC not supported and it should!" << std::endl;
		RETURN_TEST("codec_registry_test", 1);
	}
	
	const auto& hevc_codec_info = Registry::CodecInfo(hevc_codec.value()->Name());
	if (!hevc_codec_info) {
		std::cerr << "HEVC not supported and it should!" << std::endl;
		RETURN_TEST("codec_registry_test", 1);
	}

	if (!hevc_codec_info.value()->Flags().EncodeSupported()) {
		std::cerr << "HEVC encode not supported and it should!" << std::endl;
		RETURN_TEST("codec_registry_test", 1);
	}

	std::cout << "HEVC codec (type " << StormByte::Multimedia::Media::TypeToString(hevc_codec_info.value()->Type()) << ") found and encode supported." << std::endl;

	RETURN_TEST("codec_registry_test", 0);
}

int main() {
	int counter = 0;
	try {
		counter += codec_hevc_test();
	}
	catch (...) {
		std::cerr << "ERROR: Unknown exception" << std::endl;
		counter++;
	}
	return counter;
}