#pragma once

#include <StormByte/multimedia/stream/base.hxx>

#include <string>
#include <utility>
#include <vector>

/**
 * @namespace Media
 * @brief All the media related classes and functions.
 */
namespace Alchemy::Media {
	using Decoders	= std::vector<std::string>;												///< Alias for a vector of encoders.
	using Encoders	= std::vector<std::string>;												///< Alias for a vector of encoders.
	using Stream 	= StormByte::Multimedia::Stream::Base;									///< Alias for the base stream class.
	using Streams	= std::vector<Stream::PointerType>;										///< Alias for a vector of shared pointers to streams.
}