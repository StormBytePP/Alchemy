#include <Alchemy/media/ffmpeg.hxx>
#include <StormByte/system/process.hxx>
#include <StormByte/util/string.hxx>

#include <regex>

using namespace Alchemy::Media;

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

const std::unordered_map<std::string, std::shared_ptr<const Codec>> FFMpeg::CodecRegistry() {
	static const std::regex codecRegex(R"(^ ([A-Z.]{6}) ([A-Za-z0-9_]+) (.+)$)");
	StormByte::System::Process process(FFMpegPath(), {"-codecs", "-hide_banner"});
	std::string result;
	process >> result;
#ifdef WINDOWS
	// Windows have \r\n as line endings, so we need to remove the \r
	result = StormByte::Util::String::SanitizeNewlines(result);
#endif
	process.Wait();
	std::unordered_map<std::string, std::shared_ptr<const Codec>> codec_registry;
	std::smatch match;
	std::istringstream stream(result);
	std::string line;
	while (std::getline(stream, line)) {
		if (std::regex_search(line, match, codecRegex)) {
			const std::string& name = match[2];
			const std::string& flags = match[1];
			Codec codec { name, flags };
			if (match[3].matched) {
				static const std::regex decodersRegex(R"(\(decoders:\s+([^)]+)\))");
    			static const std::regex encodersRegex(R"(\(encoders:\s+([^)]+)\))");
				const std::string& rest = match[3];
				std::smatch match_sub;
				if (std::regex_search(rest, match_sub, decodersRegex)) {
					codec.Decoders(SplitToVector(match_sub[1]));
				}
				if (std::regex_search(rest, match_sub, encodersRegex)) {
					codec.Encoders(SplitToVector(match_sub[1]));
				}
			}
			codec_registry.insert({ name, std::make_shared<const Codec>(std::move(codec)) });
		}
	}
	return codec_registry;
}

std::vector<std::string> FFMpeg::SplitToVector(const std::string& str) {
    std::istringstream iss(str);
    std::vector<std::string> result;
    std::string word;
    while (iss >> word) {
        result.push_back(word); // Insert each word into the vector
    }
    return result;
}