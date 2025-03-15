#pragma once

#include <StormByte/alias.hxx>
#include <StormByte/exception.hxx>
#include <StormByte/multimedia/media/codec.hxx>
#include <StormByte/multimedia/media/type.hxx>
#include <Alchemy/media/alias.hxx>
#include <Alchemy/media/flags/codec.hxx>

#include <string>
#include <unordered_map>
#include <vector>

/**
 * @namespace Codec
 * @brief The namespace for all multimedia media codec information.
 */
namespace Alchemy::Media::Codec {
	using Name = StormByte::Multimedia::Media::Codec::Name;	///< Alias for the codec name.
	using Type = StormByte::Multimedia::Media::Type;		///< Alias for the codec type.

	/**
	 * @struct CodecInfo
	 * @brief Holds detailed information about a codec.
	 */
	struct ALCHEMY_PUBLIC Info {
		Name s_name;						///< Name of the codec
		Type s_type;						///< Type of the codec.
		Flags::Codec s_flags;				///< Flags of the codec.
		Encoders s_encoders;				///< List of encoders.
		Decoders s_decoders;				///< List of decoders.
	};

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
		static StormByte::Expected<std::shared_ptr<const Codec::Info>, StormByte::Multimedia::CodecNotFound> Info(const Name& codec);

		/**
		 * @brief Retrieves detailed information about a codec by name.
		 * @param codecName The name of the codec.
		 * @return A reference to the CodecInfo struct for the requested codec.
		 */
		static StormByte::Expected<std::shared_ptr<const Codec::Info>, StormByte::Multimedia::CodecNotFound> Info(const std::string& codecName);

		private:
			static const std::unordered_map<std::string, Name> 							c_codec_name_map;	///< The codec name map.
			static const std::unordered_map<Name, std::shared_ptr<const Codec::Info>>	c_codec_registry; 	///< The codec registry.

			/**
			 * @brief Splits string into a set of words.
			 * @param str The string to split.
			 * @return The set of words.
			 */
			static std::vector<std::string> 																SplitToVector(const std::string& str);
	};
}
