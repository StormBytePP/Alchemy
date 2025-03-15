#pragma once

#include <Alchemy/media/codec.hxx>
#include <StormByte/alias.hxx>
#include <StormByte/exception.hxx>
#include <StormByte/multimedia/media/codec.hxx>
#include <StormByte/multimedia/media/type.hxx>

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
		static StormByte::Expected<std::shared_ptr<const Codec::Info>, StormByte::Multimedia::CodecNotFound> CodecInfo(const Codec::Name& codec);

		/**
		 * @brief Retrieves detailed information about a codec by name.
		 * @param codecName The name of the codec.
		 * @return A reference to the CodecInfo struct for the requested codec.
		 */
		static StormByte::Expected<std::shared_ptr<const Codec::Info>, StormByte::Multimedia::CodecNotFound> CodecInfo(const std::string& codecName);

		private:
			static const std::unordered_map<std::string, Codec::Name> 							c_codec_name_map;	///< The codec name map.
			static const std::unordered_map<Codec::Name, std::shared_ptr<const Codec::Info>>	c_codec_registry; 	///< The codec registry.
	};
}