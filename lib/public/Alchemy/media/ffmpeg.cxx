#include <Alchemy/media/ffmpeg.hxx>
#include <StormByte/exception.hxx>
#include <StormByte/system/process.hxx>
#include <StormByte/util/string.hxx>

#include <format>
#include <json/json.h>
#include <regex>

using namespace Alchemy::Media;

StormByte::Expected<FFMpeg, Alchemy::Exception> FFMpeg::FromFile(const std::filesystem::path& path) {
	if (!std::filesystem::exists(path)) {
		return StormByte::Unexpected<Exception>(std::format("File {} does not exist", path.string()));
	}
	FFMpeg ffmpeg;
	StormByte::System::Process process(FFProbePath(), { "-v", "quiet", "-show_streams", "-show_format", "-print_format", "json", path.string() });
	std::string result;
	process >> result;
	process.Wait();
	#ifdef WINDOWS
		// Windows have \r\n as line endings, so we need to remove the \r
		result = StormByte::Util::String::SanitizeNewlines(result);
	#endif

	auto streams = ffmpeg.ParseJSon(result);
	if (streams) {
		ffmpeg.m_streams = std::move(streams.value());
	}
	else {
		return StormByte::Unexpected(streams.error());
	}
	
	return ffmpeg;
}

const std::string FFMpeg::Version() {
	static const std::regex versionRegex(R"(ffmpeg version (\d+\.\d+(?:\.\d+)?))");
	StormByte::System::Process process(FFMpegPath(), {"-version"});
	std::string result;
	process >> result;
	process.Wait();
	std::smatch match;
	if (std::regex_search(result, match, versionRegex)) {
		return match[1];
	}
	return "Unknown";
}

StormByte::Expected<Streams, Alchemy::Exception> FFMpeg::ParseJSon(const std::string& json) {
	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(json, root)) {
		return StormByte::Unexpected<Exception>("Failed to parse JSON");
	}
	Streams streams;
	const Json::Value& streamsArray = root["streams"];
	for (const auto& item : streamsArray) {
		std::cout << "Item!" << std::endl;
	}
	return streams;
}