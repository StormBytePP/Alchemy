#pragma once

#include <Alchemy/media/codec.hxx>
#include <StormByte/alias.hxx>
#include <StormByte/multimedia/exception.hxx>

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
		 * @brief Retrieves detailed information about a codec by name.
		 * @param codecName The name of the codec.
		 * @return A reference to the CodecInfo struct for the requested codec.
		 */
		static StormByte::Expected<Codec::PointerType, StormByte::Multimedia::CodecNotFound> 	CodecInfo(const std::string& codecName);

		private:
			/**
			 * @brief Gets Codec registry initialized from FFMpeg's output.
			 * @return The codec registry.
			 */
			static const std::vector<Codec::PointerType>&											CodecRegistry(); 	///< The codec registry.

			/**
			 * @brief Gets Codec name map registry.
			 * @return The codec name map.
			 */
			static const std::unordered_map<std::string, Codec::PointerType>& 						NameMapRegistry();	///< The codec name map.

			/**
			 * @brief Splits a string into a vector of shared pointers to strings.
			 * @param str The string to split.
			 * @return A vector of shared pointers to strings.
			 */
			static std::vector<std::shared_ptr<const std::string>>									Split(const std::string& str);
	};
}