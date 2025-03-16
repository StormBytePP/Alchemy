#include <Alchemy/ffmpeg.hxx>
#include <StormByte/test_handlers.h>

using namespace Alchemy;

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

int test_non_existing_file() {
	int result = 0;
	try {
		const std::filesystem::path path = CurrentFileDirectory / "files" / "non_existing_file.mkv";
		auto ffmpeg = FFMpeg::FromFile(path);
		if (ffmpeg) {
			std::cerr << "ffmpeg expected should have no value but got value!" << std::endl;
			result++;
		}
	}
	catch (const StormByte::Exception& ex) {
		std::cerr << "No exception should be thrown but got one: " << ex.what() << std::endl;
		result++;
	}
	catch (const std::exception& ex) {
		std::cerr << "No exception should be thrown but got one: " << ex.what() << std::endl;
		result++;
	}

	RETURN_TEST("test_non_existing_file", result);
}

int test_streams() {
	int result = 0;
	try {
		const std::filesystem::path path = CurrentFileDirectory / "files" / "testHDR.mkv";
		auto ffmpeg = FFMpeg::FromFile(path);
	}
	catch (const StormByte::Exception& ex) {
		std::cerr << "ERROR: " << ex.what() << std::endl;
		result++;
	}
	catch (const std::exception& ex) {
		std::cerr << "ERROR: Unknown exception: " << ex.what() << std::endl;
		result++;
	}

	RETURN_TEST("test_streams", result);
}

int main() {
	int counter = 0;
	try {
		counter += version_test();
		counter += test_non_existing_file();
		counter += test_streams();
	}
	catch (...) {
		std::cerr << "ERROR: Unknown exception" << std::endl;
		counter++;
	}
	return counter;
}