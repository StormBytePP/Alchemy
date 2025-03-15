#include <Alchemy/media/registry.hxx>
#include <Alchemy/media/ffmpeg.hxx>
#include <StormByte/multimedia/media/registry.hxx>
#include <StormByte/system/process.hxx>
#include <StormByte/util/string.hxx>

#include <regex>

using namespace Alchemy::Media;

const std::unordered_map<std::string, Codec::Name> Registry::c_codec_name_map = []() -> std::unordered_map<std::string, Codec::Name> {
    static const std::regex codecRegex(R"(^ ([A-Z.]{6}) ([A-Za-z0-9_]+) (.+)$)");
	StormByte::System::Process process(FFMpeg::FFMpegPath(), {"-codecs", "-hide_banner"});
	std::string result;
	process >> result;
	#ifdef WINDOWS
		// Windows have \r\n as line endings, so we need to remove the \r
		result = StormByte::Util::String::SanitizeNewlines(result);
	#endif
	process.Wait();
	std::unordered_map<std::string, Codec::Name> codec_name_map;
	std::smatch match;
	std::istringstream stream(result);
	std::string line;
	while (std::getline(stream, line)) {
		if (std::regex_search(line, match, codecRegex)) {
			const std::string& name = match[2];
			// Looking at StormByte Multimedia implemented codecs
			auto codec_name = StormByte::Multimedia::Media::Registry::CodecInfo(name);
			if (codec_name) {
				codec_name_map.insert({ name, std::move(codec_name.value()) });
			}
		}
	}
	return codec_name_map;
}();

const std::unordered_map<Codec::Name, std::shared_ptr<const Codec::Info>> Registry::c_codec_registry = []() -> std::unordered_map<Codec::Name, std::shared_ptr<const Codec::Info>> {
	// Since we can't know the initialization order we need to initialize from ffmpeg's output also
    static const std::regex codecRegex(R"(^ ([A-Z.]{6}) ([A-Za-z0-9_]+) (.+)$)");
	StormByte::System::Process process(FFMpeg::FFMpegPath(), {"-codecs", "-hide_banner"});
	std::string result;
	process >> result;
	#ifdef WINDOWS
		// Windows have \r\n as line endings, so we need to remove the \r
		result = StormByte::Util::String::SanitizeNewlines(result);
	#endif
	process.Wait();
	std::unordered_map<Codec::Name, std::shared_ptr<const Codec::Info>> codec_registry;
	std::smatch match;
	std::istringstream stream(result);
	std::string line;
	while (std::getline(stream, line)) {
		if (std::regex_search(line, match, codecRegex)) {
			std::string name = match[2];
			auto codec_name = StormByte::Multimedia::Media::Registry::CodecInfo(name);
			if (!codec_name)
				continue;
			auto codec_info = StormByte::Multimedia::Media::Registry::CodecInfo(codec_name.value());
			
			std::string flags = match[1];
			Decoders decoders;
			Encoders encoders;
			if (match[3].matched) {
				static const std::regex decodersRegex(R"(\(decoders:\s+([^)]+)\))");
    			static const std::regex encodersRegex(R"(\(encoders:\s+([^)]+)\))");
				const std::string& rest = match[3];
				std::smatch match_sub;
				if (std::regex_search(rest, match_sub, decodersRegex)) {
					decoders = StormByte::Util::String::Split(match_sub[1]);
				}
				if (std::regex_search(rest, match_sub, encodersRegex)) {
					encoders = StormByte::Util::String::Split(match_sub[1]);
				}
			}
			Codec::Info codec_i {
				codec_name.value(),
				codec_info.Type(),
				std::move(flags),
				std::move(decoders),
				std::move(encoders)
			};

			codec_registry.insert({ std::move(codec_name.value()), std::make_shared<const Codec::Info>(std::move(codec_i)) });
		}
	}
	return codec_registry;
}();

StormByte::Expected<std::shared_ptr<const Codec::Info>, StormByte::Multimedia::CodecNotFound> Registry::CodecInfo(const Codec::Name& codec) {
	const auto& info = c_codec_registry.find(codec);
	if (info != c_codec_registry.end())
		return info->second;
	else
		return StormByte::Unexpected<StormByte::Multimedia::CodecNotFound>(StormByte::Multimedia::Media::Registry::CodecInfo(codec).Name());
}

StormByte::Expected<std::shared_ptr<const Codec::Info>, StormByte::Multimedia::CodecNotFound> Registry::CodecInfo(const std::string& name) {
	const auto& it = c_codec_name_map.find(StormByte::Util::String::ToLower(name));
	if (it != c_codec_name_map.end()) {
		const auto& it2 = c_codec_registry.find(it->second);
		return it2->second;
	}
	else
		return StormByte::Unexpected<StormByte::Multimedia::CodecNotFound>(name);
}

