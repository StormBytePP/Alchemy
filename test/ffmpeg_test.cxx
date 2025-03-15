#include <Alchemy/media/ffmpeg.hxx>
#include <StormByte/test_handlers.h>

using namespace Alchemy::Media;

int version_test() {
	int result = 0;
	try {
		const std::string version = FFMpeg::Version();
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

int main() {
	int counter = 0;
	try {
		counter += version_test();
	}
	catch (...) {
		std::cerr << "ERROR: Unknown exception" << std::endl;
		counter++;
	}
	return counter;
}