#pragma once

#include <Alchemy/media/flags/codec.hxx>
#include <Alchemy/media/flags/container.hxx>

#include <regex>
#include <filesystem>
#include <string>
#include <unordered_map>

/**
 * @namespace Alchemy
 * @brief The main namespace for the Alchemy library.
 */
namespace Alchemy::Media {
	class ALCHEMY_PUBLIC FFMpeg {
		public:
			static const char* 												Version;					///< The path to the FFMpeg executable.

			/**
			 * @brief Copy constructor.
			 * @param other The FFMpeg object to copy.
			 */
			FFMpeg(const FFMpeg& other)										= default;

			/**
			 * @brief Move constructor.
			 * @param other The FFMpeg object to move.
			 */
			FFMpeg(FFMpeg&& other) noexcept									= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The FFMpeg object to copy.
			 * @return A reference to this object.
			 */
			FFMpeg& operator=(const FFMpeg& other)							= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The FFMpeg object to move.
			 * @return A reference to this object.
			 */
			FFMpeg& operator=(FFMpeg&& other) noexcept						= default;

			/**
			 * @brief Default destructor.
			 */
			~FFMpeg() noexcept 												= default;

		private:
			static const char* 												c_ffmpeg_path;				///< The path to the FFMpeg executable.
			static const char* 												c_ffprobe_path;				///< The path to the FFProbe executable.
			static const std::unordered_map<const char*, Flags::Codec>		c_codec_registry;			///< The list of supported codecs.
			static const std::unordered_map<const char*, Flags::Container>	c_format_registry;			///< The list of supported formats.
			
			/**
			 * @brief Default constructor.
			 */
			FFMpeg() noexcept 												= default;
	};
}