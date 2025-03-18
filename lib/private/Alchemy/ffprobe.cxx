#include <Alchemy/ffprobe.hxx>
#include <Alchemy/hdr10plus_tool.hxx>
#include <Alchemy/media/registry.hxx>
#include <StormByte/expected.hxx>
#include <StormByte/multimedia/media/property/video/color.hxx>
#include <StormByte/multimedia/media/property/tags.hxx>
#include <StormByte/multimedia/stream/audio.hxx>
#include <StormByte/system/process.hxx>

#include <format>

using namespace Alchemy;

FFProbe::FFProbe(const std::filesystem::path& path) noexcept: m_path(path) {}

template<>
StormByte::Expected<Media::Stream::PointerType, StreamError> FFProbe::ParseStreamJson<StormByte::Multimedia::Stream::Audio>(const Json::Value& stream_json) const {
	const Json::Value audio_json = stream_json[0];
	const auto expected_codec = Media::Registry::CodecInfo(audio_json["codec_name"].asString());
	if (!expected_codec) {
		return StormByte::Unexpected<StreamError>(std::format("Unsupported codec {}", audio_json["codec_name"].asString()));
	}
	std::shared_ptr<Media::AudioStream> audio_stream = std::static_pointer_cast<Media::AudioStream>(StormByte::Multimedia::Stream::Create(expected_codec.value()));

	if (audio_json.isMember("profile")) {
		auto profile = std::make_shared<const std::string>(audio_json["profile"].asString());
		audio_stream->Profile() = std::move(profile);
	}
	if (audio_json.isMember("sample_fmt") && audio_json.isMember("sample_rate")) {
		auto sample = std::make_shared<const StormByte::Multimedia::Media::Property::Audio::Sample>(audio_json["sample_rate"].asString(), static_cast<unsigned short>(std::stoul(audio_json["sample_rate"].asString())));
		audio_stream->Sample() = std::move(sample);
	}
	else
		return StormByte::Unexpected<StreamError>("Missing sample information");		
	if (audio_json.isMember("channels") && audio_json.isMember("channel_layout")) {
		auto channels = std::make_shared<const StormByte::Multimedia::Media::Property::Audio::Channels>(static_cast<unsigned short>(audio_json["channels"].asUInt()), audio_json["channel_layout"].asString());
		audio_stream->Channels() = std::move(channels);
	}
	else
		return StormByte::Unexpected<StreamError>("Missing channel information");
	if (audio_json.isMember("bit_rate")) {
		auto bitrate = std::make_shared<const unsigned int>(std::stoul(audio_json["bit_rate"].asString()));
		audio_stream->Bitrate() = std::move(bitrate);
	}

	ParseTagsJson(audio_json, audio_stream);

	return audio_stream;
}

template<>
StormByte::Expected<Media::Stream::PointerType, StreamError> FFProbe::ParseStreamJson<StormByte::Multimedia::Stream::Video>(const Json::Value& stream_json) const {
	const Json::Value video_json = stream_json[0];
	const auto expected_codec = Media::Registry::CodecInfo(video_json["codec_name"].asString());
	if (!expected_codec) {
		return StormByte::Unexpected<StreamError>(std::format("Unsupported codec {}", video_json["codec_name"].asString()));
	}
	std::shared_ptr<Media::VideoStream> video_stream = std::static_pointer_cast<Media::VideoStream>(StormByte::Multimedia::Stream::Create(expected_codec.value()));

	if (video_json.isMember("profile")) {
		auto profile = std::make_shared<const std::string>(video_json["profile"].asString());
		video_stream->Profile() = std::move(profile);
	}
	if (video_json.isMember("width") && video_json.isMember("height")) {
		auto resolution = std::make_shared<const StormByte::Multimedia::Media::Property::Resolution>(static_cast<unsigned short>(video_json["width"].asUInt()), static_cast<unsigned short>(video_json["height"].asUInt()));
		video_stream->Resolution() = std::move(resolution);
	}
	else
		return StormByte::Unexpected<StreamError>("Missing resolution information");
	const Json::Value color_json = VideoColorJson(static_cast<unsigned short>(video_json["index"].asUInt()))[0];
	if (color_json.isMember("pix_fmt") && color_json.isMember("color_range") && color_json.isMember("color_space")) {
		std::shared_ptr<const StormByte::Multimedia::Media::Property::Video::Color> color;
		std::string pix_fmt = color_json["pix_fmt"].asString();
		std::string color_range = color_json["color_range"].asString();
		std::string color_space = color_json["color_space"].asString();
		// Now that we have the "normal" color modes, we check if we also have HDR color information
		if (color_json.isMember("color_primaries") && color_json.isMember("color_transfer")) {
			// We are in HDR mode! let's check if we have all required data
			std::string color_primaries = color_json["color_primaries"].asString();
			std::string color_transfer	= color_json["color_transfer"].asString();
			if (color_json.isMember("side_data_list")) {
				// We are in full HDR mode
				std::string blue_x, blue_y, green_x, green_y, red_x, red_y, white_point_x, white_point_y, min_luminance, max_luminance;
				std::optional<unsigned int> max_average, max_content;
				const Json::Value side_data_list = color_json["side_data_list"];
				for (Json::Value::ArrayIndex i = 0; i < side_data_list.size(); i++) {
					const Json::Value side_data = side_data_list[i];
					if (side_data["side_data_type"].asString() == "Mastering display metadata") {
						if (side_data.isMember("blue_x")) blue_x = side_data["blue_x"].asString();
						if (side_data.isMember("blue_y")) blue_y = side_data["blue_y"].asString();
						if (side_data.isMember("green_x")) green_x = side_data["green_x"].asString();
						if (side_data.isMember("green_y")) green_y = side_data["green_y"].asString();
						if (side_data.isMember("red_x")) red_x = side_data["red_x"].asString();
						if (side_data.isMember("red_y")) red_y = side_data["red_y"].asString();
						if (side_data.isMember("white_point_x")) white_point_x = side_data["white_point_x"].asString();
						if (side_data.isMember("white_point_y")) white_point_y = side_data["white_point_y"].asString();
						if (side_data.isMember("min_luminance")) min_luminance = side_data["min_luminance"].asString();
						if (side_data.isMember("max_luminance")) max_luminance = side_data["max_luminance"].asString();
					}
					else if (side_data["side_data_type"].asString() == "Content light level metadata") {
						if (side_data.isMember("max_content")) max_content = side_data["max_content"].asUInt();
						if (side_data.isMember("max_average")) max_average = side_data["max_average"].asUInt();
					}
					else continue;
				}

				// Converting fractions
				auto expected_blue = StormByte::Multimedia::Media::Property::Video::HDR10::ColorPoint(blue_x, blue_y);
				auto expected_green = StormByte::Multimedia::Media::Property::Video::HDR10::ColorPoint(green_x, green_y);
				auto expected_red = StormByte::Multimedia::Media::Property::Video::HDR10::ColorPoint(red_x, red_y);
				auto expected_white_point = StormByte::Multimedia::Media::Property::Video::HDR10::ColorPoint(white_point_x, white_point_y);
				auto expected_luminance = StormByte::Multimedia::Media::Property::Video::HDR10::ColorPoint(min_luminance, max_luminance);
				std::optional<StormByte::Multimedia::Media::Property::Video::Color::Point> light_level = 
					(max_average && max_content) ? 
						std::make_optional(StormByte::Multimedia::Media::Property::Video::Color::Point(*max_average, *max_content)) : std::nullopt;

				// Now we need to check which data we have and which data we take from default HDR color information
				if (expected_blue && expected_green && expected_red && expected_white_point && expected_luminance) {
					HDR10PlusTool hdr10plus_tool(m_path);
					StormByte::Multimedia::Media::Property::Video::HDR10 _color(
						std::move(pix_fmt), std::move(color_range), std::move(color_space), std::move(color_primaries), std::move(color_transfer),
						expected_red.value(),
						expected_green.value(),
						expected_blue.value(),
						expected_white_point.value(),
						expected_luminance.value(),
						std::move(light_level)
					);
					_color.HDR10Plus(HDR10PlusTool(m_path).IsHDRPlus());
					// We have all the data for a full HDR10 color information
					color = std::make_shared<const StormByte::Multimedia::Media::Property::Video::HDR10>(std::move(_color));
				}
				else {
					// We don't have the full HDR Metadata, we will use the default HDR10 color information
					HDR10PlusTool hdr10plus_tool(m_path);
					StormByte::Multimedia::Media::Property::Video::HDR10 _color(
						std::move(pix_fmt),
						std::move(color_range),
						std::move(color_space),
						std::move(color_primaries),
						std::move(color_transfer)
					);
					_color.HDR10Plus(HDR10PlusTool(m_path).IsHDRPlus());
					color = std::make_shared<const StormByte::Multimedia::Media::Property::Video::HDR10>(std::move(_color));
				}
			}
			else {
				// We don't have the full HDR Metadata, we will use the default HDR10 color information
				color = std::make_shared<const StormByte::Multimedia::Media::Property::Video::HDR10>(std::move(pix_fmt), std::move(color_range), std::move(color_space), std::move(color_primaries), std::move(color_transfer));
			}
			video_stream->Color() = color;
		}
		else {
			// We don't have HDR so we will use the "normal" color mode
			color = std::make_shared<const StormByte::Multimedia::Media::Property::Video::Color>(pix_fmt, color_range, color_space);
		}
	}
	else
		return StormByte::Unexpected<StreamError>("Missing color information");

	return video_stream;
}

template<>
StormByte::Expected<Media::Stream::PointerType, StreamError> FFProbe::ParseStreamJson<StormByte::Multimedia::Stream::Subtitle>(const Json::Value& stream_json) const {
	const Json::Value subtitle_json = stream_json[0];
	const auto expected_codec = Media::Registry::CodecInfo(subtitle_json["codec_name"].asString());
	if (!expected_codec) {
		return StormByte::Unexpected<StreamError>(std::format("Unsupported codec {}", subtitle_json["codec_name"].asString()));
	}
	std::shared_ptr<Media::SubtitleStream> subtitle_stream = std::static_pointer_cast<Media::SubtitleStream>(StormByte::Multimedia::Stream::Create(expected_codec.value()));

	ParseTagsJson(subtitle_json, subtitle_stream);

	return subtitle_stream;
}

StormByte::Expected<FFMpeg, StreamError> FFProbe::Process() const {
	FFMpeg ffmpeg(m_path);

	Media::Streams streams;
	const Json::Value streams_json = StreamList();

	for (const auto& stream_type_json: streams_json) {
		const unsigned short index = static_cast<unsigned short>(stream_type_json["index"].asUInt());
		const std::string codec_type = stream_type_json["codec_type"].asString();
		const Json::Value stream_data_json = StreamJson(index);
		StormByte::Expected<Media::Stream::PointerType, StreamError> expected_stream;

		if (codec_type == "audio" ) {
			expected_stream = ParseStreamJson<StormByte::Multimedia::Stream::Audio>(stream_data_json);
		}
		else if (codec_type == "video") {
			expected_stream = ParseStreamJson<StormByte::Multimedia::Stream::Video>(stream_data_json);
		}
		else if (codec_type == "subtitle") {
			expected_stream = ParseStreamJson<StormByte::Multimedia::Stream::Subtitle>(stream_data_json);
		}

		if (expected_stream)
			streams.push_back(expected_stream.value());
		else
			return StormByte::Unexpected(expected_stream.error());
	}
	ffmpeg.Streams() = std::move(streams);

	return ffmpeg;
}

const Json::Value FFProbe::StreamList() const {
	return Execute({ "-v", "quiet", "-print_format", "json", "-show_entries", "stream=index,codec_type", "-i", m_path.string() }, "streams");
}

const Json::Value FFProbe::StreamJson(const unsigned short& index) const {
	return Execute({ "-v", "quiet", "-print_format", "json", "-show_streams", "-select_streams", std::to_string(index), "-i", m_path.string() }, "streams");
}

const Json::Value FFProbe::VideoColorJson(const unsigned short& index) const {
	return Execute({ "-v", "quiet", "-print_format", "json", "-show_frames", "-read_intervals", "%+#2", "-select_streams", std::to_string(index), "-show_entries", "frame=pix_fmt,color_range,color_space,color_primaries,color_transfer,side_data_list", "-i", m_path.string() }, "frames");
}

const Json::Value FFProbe::Execute(std::vector<std::string>&& arguments, const std::string& root_name) const {
	std::ostringstream oss;
    for (size_t i = 0; i < arguments.size(); ++i) {
        if (i > 0) oss << " ";  // Add a space between strings (but not before the first one).
        oss << arguments[i];
    }
    const std::string params = oss.str();

	StormByte::System::Process process(Executable(), std::move(arguments));
	std::string result;
	std::string err;
	process >> result;
	process.Wait();
	
	Json::Reader reader;
	Json::Value root;

	if (!reader.parse(result, root))
		return {};
	if (!root.isObject() || !root.isMember(root_name))
		return {};

	return root[root_name];
}

void FFProbe::ParseTagsJson(const Json::Value& stream_json, Media::Stream::PointerType stream) const {
	if (stream_json.isMember("tags")) {
		const Json::Value tags = stream_json["tags"];
		StormByte::Multimedia::Media::Property::Tags<std::string> stream_tags;
		for (Json::Value::const_iterator it = tags.begin(); it != tags.end(); it++) {
			stream_tags[it.key().asString()] = it->asString();
		}
		stream->Tags() = stream_tags;
	}
	if (stream_json.isMember("disposition")) {
		const Json::Value disposition = stream_json["disposition"];
		StormByte::Multimedia::Media::Property::Tags<bool> stream_disposition;
		for (Json::Value::const_iterator it = disposition.begin(); it != disposition.end(); it++) {
			stream_disposition[it.key().asString()] = it->asBool();
		}
		stream->Disposition() = stream_disposition;
	}
}