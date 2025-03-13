#pragma once

#include <visibility.h>

#include <regex>
#include <filesystem>

/**
 * @namespace Alchemy
 * @brief The main namespace for the Alchemy library.
 */
namespace Alchemy {
	class ALCHEMY_PUBLIC FFMpeg {
		public:
			/**
			 * @brief Copy constructor.
			 * @param other The FFMpeg object to copy.
			 */
			FFMpeg(const FFMpeg& other)						= default;

			/**
			 * @brief Move constructor.
			 * @param other The FFMpeg object to move.
			 */
			FFMpeg(FFMpeg&& other) noexcept					= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The FFMpeg object to copy.
			 * @return A reference to this object.
			 */
			FFMpeg& operator=(const FFMpeg& other)			= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The FFMpeg object to move.
			 * @return A reference to this object.
			 */
			FFMpeg& operator=(FFMpeg&& other) noexcept		= default;

			/**
			 * @brief Default destructor.
			 */
			~FFMpeg() noexcept 								= default;

		private:
			static const std::filesystem::path 				c_ffmpeg_path;				/**< The path to the FFMpeg executable. */
			static const std::filesystem::path 				c_ffprobe_path;				/**< The path to the FFProbe executable. */
			static const std::regex 						c_supported_codecs_regex;	/**< The regular expression to match the FFMpeg version. */
			
			/**
			 * @brief Default constructor.
			 */
			FFMpeg() noexcept 								= default;
	};
}