#pragma once

#include <StormByte/multimedia/stream/base.hxx>

#include <vector>

/**
 * @namespace Media
 * @brief All the media related classes and functions.
 */
namespace Alchemy::Media {
	using Stream 	= StormByte::Multimedia::Stream::Base;	///< Alias for the base stream class.
	using Streams	= std::vector<Stream::PointerType>;	///< Alias for a vector of shared pointers to streams.
}