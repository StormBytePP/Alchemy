#pragma once

#include <Alchemy/media/codec.hxx>
#include <StormByte/alias.hxx>
#include <StormByte/multimedia/exception.hxx>
#include <StormByte/multimedia/media/codec.hxx>
#include <StormByte/multimedia/media/type.hxx>

#include <unordered_map>
#include <vector>

/**
 * @namespace Media
 * @brief All the media related classes and functions.
 */
namespace Alchemy::Media {
	/**
	 * @class CodecRegistry
	 * @brief Centralized registry to manage codec-related metadata.
	 */
	struct ALCHEMY_PUBLIC Registry {
		/**
		 * @brief Retrieves detailed information about a codec.
		 * @param codec The codec enum value.
		 * @return A reference to the CodecInfo struct for the requested codec.
		 */
		static StormByte::Expected<Codec::Info::PointerType, StormByte::Multimedia::CodecNotFound> 	CodecInfo(const Codec::Name& codec);

		/**
		 * @brief Retrieves detailed information about a codec by name.
		 * @param codecName The name of the codec.
		 * @return A reference to the CodecInfo struct for the requested codec.
		 */
		static StormByte::Expected<Codec::Info::PointerType, StormByte::Multimedia::CodecNotFound> 	CodecInfo(const std::string& codecName);

		private:
			static const std::vector<Codec::Info::PointerType>										c_codec_registry; 	///< The codec registry.
			static const std::unordered_map<std::string, Codec::Info::PointerType> 					c_codec_name_map;	///< The codec name map.
			
	};
}