#include <Alchemy/ffmpeg.hxx>
#include <Alchemy/media/registry.hxx>
#include <StormByte/exception.hxx>
#include <StormByte/system/process.hxx>
#include <StormByte/util/string.hxx>

#include <format>
#include <json/json.h>
#include <regex>

using namespace Alchemy;

StormByte::Expected<FFMpeg, StreamError> FFMpeg::FromFile(const std::filesystem::path& path) {
	if (!std::filesystem::exists(path)) {
		return StormByte::Unexpected<StreamError>(std::format("File {} does not exist", path.string()));
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

StormByte::Expected<Media::Streams, StreamError> FFMpeg::ParseJSon(const std::string& json) {
	Json::Value root;
	Json::Reader reader;
	// Sanity checks
	if (!reader.parse(json, root)) {
		return StormByte::Unexpected<StreamError>("Failed to parse JSON");
	}
	else if (root.empty()) {
		return StormByte::Unexpected<StreamError>("Empty JSON");
	}
	else if (!root.isObject()) {
		return StormByte::Unexpected<StreamError>("Expected root as Object but got something else");
	}

	// We have data
	Media::Streams streams;
	const Json::Value& streamsArray = root["streams"];
	for (const auto& item : streamsArray) {
		std::cout << "Index: " << item["index"].asUInt() << std::endl;
		const auto& stream_type = item["codec_type"].asString();
		StormByte::Expected<Media::Stream::PointerType, StreamError> expected_stream;
		if (stream_type == "attachment") {
			expected_stream = ParseAttachmentJson(item);
		}
		else if (stream_type == "audio") {
			expected_stream = ParseAudioJson(item);
		}
		else if (stream_type == "image") {
			expected_stream = ParseImageJson(item);
		}
		else if (stream_type == "subtitle") {
			expected_stream = ParseSubtitleJson(item);
		}
		else if (stream_type == "video") {
			expected_stream = ParseVideoJson(item);
		}
		else {
			return StormByte::Unexpected<StreamError>(std::format("Unknown stream type: {}", stream_type));
		}
		if (expected_stream.has_value()) {
			if (!expected_stream.value()) {
				std::cerr << "Stream is null" << std::endl;
			}
			expected_stream.value()->Disposition() 	= ParseTags(item, "disposition");
			expected_stream.value()->Tags() 		= ParseTags(item, "tags");
			streams.push_back(std::move(expected_stream.value()));
		}
		else {
			std::cerr << "Unexpected stream" << std::endl;
			return StormByte::Unexpected(expected_stream.error());
		}
	}
	return streams;
}

StormByte::Expected<Media::Stream::PointerType, StreamError> FFMpeg::ParseAttachmentJson(const Json::Value& /*attachment_json*/) {
	return StormByte::Unexpected<StreamError>("Not implemented");
}

StormByte::Expected<Media::Stream::PointerType, StreamError> FFMpeg::ParseAudioJson(const Json::Value& audio_json) {
	const auto expected_codec = Media::Registry::CodecInfo(audio_json["codec_name"].asString());
	if (!expected_codec) {
		return StormByte::Unexpected<StreamError>(std::format("Failed to get codec info for {}", audio_json["codec_name"].asString()));
	}
	std::shared_ptr<Media::AudioStream> audio_stream = std::static_pointer_cast<Media::AudioStream>(StormByte::Multimedia::Stream::Create(expected_codec.value()->ID()));

	if (audio_json.isMember("profile")) 
		audio_stream->Profile() = audio_json["profile"].asString();
	if (audio_json.isMember("sample_rate"))
		audio_stream->SampleRate() = std::stoul(audio_json["sample_rate"].asString());
	else
		return StormByte::Unexpected<StreamError>("Missing sample rate");		
	if (audio_json.isMember("channels"))
		audio_stream->Channels() = audio_json["channels"].asUInt();
	else
		return StormByte::Unexpected<StreamError>("Missing channels");
	if (audio_json.isMember("channel_layout"))
		audio_stream->ChannelLayout() = audio_json["channel_layout"].asString();
	else
		return StormByte::Unexpected<StreamError>("Missing channel layout");
	if (audio_json.isMember("bit_rate"))
		audio_stream->Bitrate() = std::stoul(audio_json["bit_rate"].asString());
	else
		return StormByte::Unexpected<StreamError>("Missing bit rate");

	return audio_stream;
}

StormByte::Expected<Media::Stream::PointerType, StreamError> FFMpeg::ParseImageJson(const Json::Value& /*image_json*/) {
	return StormByte::Unexpected<StreamError>("Not implemented");
}

StormByte::Expected<Media::Stream::PointerType, StreamError> FFMpeg::ParseVideoJson(const Json::Value& video_json) {
	const auto expected_codec = Media::Registry::CodecInfo(video_json["codec_name"].asString());
	if (!expected_codec) {
		return StormByte::Unexpected<StreamError>(std::format("Failed to get codec info for {}", video_json["codec_name"].asString()));
	}
	std::shared_ptr<Media::VideoStream> video_stream = std::static_pointer_cast<Media::VideoStream>(StormByte::Multimedia::Stream::Create(expected_codec.value()->ID()));

	

	return video_stream;
}

StormByte::Expected<Media::Stream::PointerType, StreamError> FFMpeg::ParseSubtitleJson(const Json::Value& subtitle_json) {
	return StormByte::Unexpected<StreamError>("Not implemented");
}

StormByte::Multimedia::Media::Tags FFMpeg::ParseTags(const Json::Value& tags, const std::string& tag_name) {
	StormByte::Multimedia::Media::Tags tag_list;
	if (!tags.isObject() || !tags.isMember(tag_name))
		return tag_list;
	for (const auto& tag: tags[tag_name].getMemberNames())
		tag_list[tag] = tags[tag_name][tag].asString();
	
	return tag_list;
}
