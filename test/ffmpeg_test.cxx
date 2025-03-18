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

int test_HDR() {
	int result = 0;
	try {
		const std::filesystem::path path = CurrentFileDirectory / "files" / "testHDR.mkv";
		auto ffmpeg = FFMpeg::FromFile(path);
		if (!ffmpeg) {
			std::cerr << "ffmpeg not created because of: " << ffmpeg.error()->what() << std::endl;
			result++;
		}
		else {
			auto video_stream = std::static_pointer_cast<Media::VideoStream>(ffmpeg.value().Streams()[0]);
			bool hdr_status = video_stream->Color()->IsHDR10();
			ASSERT_TRUE("test_HDR", hdr_status);
			auto color_hdr = std::static_pointer_cast<const StormByte::Multimedia::Media::Property::Video::HDR10>(video_stream->Color());
			ASSERT_FALSE("test_HDR", color_hdr->IsHDR10Plus());
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

	RETURN_TEST("test_HDR", result);
}

int test_HDR_plus() {
	int result = 0;
	try {
		const std::filesystem::path path = CurrentFileDirectory / "files" / "testHDR+.mkv";
		auto ffmpeg = FFMpeg::FromFile(path);
		if (!ffmpeg) {
			std::cerr << "ffmpeg not created because of: " << ffmpeg.error()->what() << std::endl;
			result++;
		}
		else {
			auto video_stream = std::static_pointer_cast<Media::VideoStream>(ffmpeg.value().Streams()[0]);
			bool hdr_status = video_stream->Color()->IsHDR10();
			ASSERT_TRUE("test_HDR", hdr_status);
			auto color_hdr = std::static_pointer_cast<const StormByte::Multimedia::Media::Property::Video::HDR10>(video_stream->Color());
			ASSERT_TRUE("test_HDR", color_hdr->IsHDR10Plus());
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

	RETURN_TEST("test_HDR", result);
}

int main() {
	int counter = 0;
	try {
		counter += version_test();
		counter += test_non_existing_file();
		counter += test_HDR();
		counter += test_HDR_plus();
	}
	catch (...) {
		std::cerr << "ERROR: Unknown exception" << std::endl;
		counter++;
	}
	return counter;
}