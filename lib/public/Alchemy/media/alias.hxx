#pragma once

#include <StormByte/multimedia/stream/attachment.hxx>
#include <StormByte/multimedia/stream/audio.hxx>
#include <StormByte/multimedia/stream/subtitle.hxx>
#include <StormByte/multimedia/stream/video.hxx>

#include <memory>
#include <string>
#include <utility>
#include <vector>

/**
 * @namespace Media
 * @brief All the media related classes and functions.
 */
namespace Alchemy::Media {
	using AttachmentStream	= StormByte::Multimedia::Stream::Attachment;		///< Alias for the attachment stream class.
	using AudioStream		= StormByte::Multimedia::Stream::Audio;				///< Alias for the audio stream class.
	using Decoders			= std::vector<std::shared_ptr<const std::string>>;	///< Alias for a vector of encoders.
	using Encoders			= std::vector<std::shared_ptr<const std::string>>;	///< Alias for a vector of encoders.
	using Stream			= StormByte::Multimedia::Stream::Base;				///< Alias for the base stream class.
	using Streams			= std::vector<Stream::PointerType>;					///< Alias for a vector of shared pointers to streams.
	using SubtitleStream	= StormByte::Multimedia::Stream::Subtitle;			///< Alias for the subtitle stream class.
	using VideoStream		= StormByte::Multimedia::Stream::Video;				///< Alias for the video stream class.
}