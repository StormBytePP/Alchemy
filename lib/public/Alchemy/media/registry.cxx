#include <Alchemy/media/registry.hxx>
#include <Alchemy/ffmpeg.hxx>
#include <StormByte/system/process.hxx>
#include <StormByte/util/string.hxx>

#include <ranges>
#include <regex>

using namespace Alchemy::Media;

const std::vector<Codec::PointerType>& Registry::CodecRegistry() {
	static const std::vector<Codec::PointerType> c_codec_registry = []() -> std::vector<Codec::PointerType> {
		// Since we can't know the initialization order we need to initialize from ffmpeg's output also
		static const std::regex codecRegex(R"(^ ([A-Z.]{6}) ([A-Za-z0-9_]+)\s+(.+?)(?:\s*\(decoders: ([^)]+)\))?(?:\s*\(encoders: ([^)]+)\))?$)");
	
		StormByte::System::Process process(Alchemy::FFMpeg::Executable(), {"-codecs", "-hide_banner"});
		std::string result;
		process >> result;
		#ifdef WINDOWS
			// Windows have \r\n as line endings, so we need to remove the \r
			result = StormByte::Util::String::SanitizeNewlines(result);
		#endif
		process.Wait();
		std::vector<Codec::PointerType> codec_registry;
		std::smatch match;
		std::istringstream stream(result);
		std::string line;
		while (std::getline(stream, line)) {
			if (std::regex_search(line, match, codecRegex)) {
				std::string flags = match[1];
				std::string name = match[2];
				std::string long_name = match[3];
				
				Decoders decoders;
				if (match[4].matched) {
					decoders = Split(match[4]);
				}
				Encoders encoders;
				if (match[5].matched) {
					encoders = Split(match[5]);
				}
				
				Codec codec {
					std::move(name),
					std::move(long_name),
					std::move(flags),
					std::move(decoders),
					std::move(encoders)
				};
	
				codec_registry.push_back(std::make_shared<Codec>(std::move(codec)));
			}
		}
		return codec_registry;
	}();
	return c_codec_registry;
}

const std::unordered_map<std::string, Codec::PointerType>& Registry::NameMapRegistry() {
	static const std::unordered_map<std::string, Codec::PointerType> c_codec_name_map = []() -> std::unordered_map<std::string, Codec::PointerType> {
		std::unordered_map<std::string, Codec::PointerType> codec_name_map;
		for (auto& codec: CodecRegistry()) {
			codec_name_map[StormByte::Util::String::ToLower(codec->Name())] = codec;
		}
		return codec_name_map;
	}();
	return c_codec_name_map;
}

StormByte::Expected<Codec::PointerType, StormByte::Multimedia::CodecNotFound> Registry::CodecInfo(const std::string& name) {
	const auto& info = NameMapRegistry().find(StormByte::Util::String::ToLower(name));
	if (info != NameMapRegistry().end()) {
		return info->second;
	}
	else
		return StormByte::Unexpected<StormByte::Multimedia::CodecNotFound>(name);
}

std::vector<std::shared_ptr<const std::string>> Registry::Split(const std::string& str) {
	std::vector<std::shared_ptr<const std::string>> split;
	for (const auto& item : StormByte::Util::String::Split(str)) {
		split.push_back(std::make_shared<const std::string>(item));
	}
	return split;
}