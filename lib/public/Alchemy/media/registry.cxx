#include <Alchemy/media/registry.hxx>
#include <Alchemy/ffmpeg.hxx>
#include <StormByte/multimedia/media/registry.hxx>
#include <StormByte/system/process.hxx>
#include <StormByte/util/string.hxx>

#include <ranges>
#include <regex>

using namespace Alchemy::Media;

const std::vector<Codec::Info::PointerType> Registry::c_codec_registry = []() -> std::vector<Codec::Info::PointerType> {
	// Since we can't know the initialization order we need to initialize from ffmpeg's output also
	static const std::regex codecRegex(R"(^ ([A-Z.]{6}) ([A-Za-z0-9_]+)\s+(.+?)(?:\s*\(decoders: ([^)]+)\))?(?:\s*\(encoders: ([^)]+)\))?$)");

	StormByte::System::Process process(Alchemy::FFMpeg::FFMpegPath(), {"-codecs", "-hide_banner"});
	std::string result;
	process >> result;
	#ifdef WINDOWS
		// Windows have \r\n as line endings, so we need to remove the \r
		result = StormByte::Util::String::SanitizeNewlines(result);
	#endif
	process.Wait();
	std::vector<Codec::Info::PointerType> codec_registry;
	std::smatch match;
	std::istringstream stream(result);
	std::string line;
	while (std::getline(stream, line)) {
		if (std::regex_search(line, match, codecRegex)) {
			std::string flags = match[1];
			std::string name = match[2];
			std::string long_name = match[3];

			auto expected_codec_info = StormByte::Multimedia::Media::Registry::CodecInfo(name);
			if (!expected_codec_info)
				continue;
			
			Decoders decoders;
			if (match[4].matched) {
				decoders = StormByte::Util::String::Split(match[4]);
			}
			Encoders encoders;
			if (match[5].matched) {
				encoders = StormByte::Util::String::Split(match[5]);
			}
			
			Codec::Info codec_info {
				expected_codec_info.value()->ID(),
				expected_codec_info.value()->Name(),
				std::move(long_name),
				expected_codec_info.value()->Type(),
				std::move(flags),
				std::move(decoders),
				std::move(encoders)
			};

			codec_registry.push_back(std::make_shared<const Codec::Info>(std::move(codec_info)));
		}
	}
	return codec_registry;
}();

const std::unordered_map<Codec::ID, Codec::Info::PointerType> Registry::c_codec_id_map = []() -> std::unordered_map<Codec::ID, Codec::Info::PointerType> {
	std::unordered_map<Codec::ID, Codec::Info::PointerType> codec_id_map;
	for (auto& codec: c_codec_registry) {
		codec_id_map[codec->ID()] = codec;
	}
	return codec_id_map;
}();

const std::unordered_map<std::string, Codec::Info::PointerType> Registry::c_codec_name_map = []() -> std::unordered_map<std::string, Codec::Info::PointerType> {
	std::unordered_map<std::string, Codec::Info::PointerType> codec_name_map;
	for (auto& codec: c_codec_registry) {
		codec_name_map[StormByte::Util::String::ToLower(StormByte::Multimedia::Media::Registry::CodecInfo(codec->ID())->Name())] = codec;
	}
	return codec_name_map;
}();

StormByte::Expected<std::shared_ptr<const Codec::Info>, StormByte::Multimedia::CodecNotFound> Registry::CodecInfo(const Codec::ID& codec) {
	const auto& info = c_codec_id_map.find(codec);
	if (info != c_codec_id_map.end())
		return info->second;
	else
		return StormByte::Unexpected<StormByte::Multimedia::CodecNotFound>(StormByte::Multimedia::Media::Registry::CodecInfo(codec)->Name());
}

StormByte::Expected<std::shared_ptr<const Codec::Info>, StormByte::Multimedia::CodecNotFound> Registry::CodecInfo(const std::string& name) {
	const auto& info = c_codec_name_map.find(StormByte::Util::String::ToLower(name));
	if (info != c_codec_name_map.end()) {
		return info->second;
	}
	else
		return StormByte::Unexpected<StormByte::Multimedia::CodecNotFound>(name);
}

