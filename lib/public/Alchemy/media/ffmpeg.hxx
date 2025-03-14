#pragma once

#include <Alchemy/media/codec.hxx>

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @namespace Media
 * @brief All the media related classes and functions.
 */
namespace Alchemy::Media {
	class ALCHEMY_PUBLIC FFMpeg {
		public:
			/**
			 * @brief Copy constructor.
			 * @param other The FFMpeg object to copy.
			 */
			FFMpeg(const FFMpeg& other)														= default;

			/**
			 * @brief Move constructor.
			 * @param other The FFMpeg object to move.
			 */
			FFMpeg(FFMpeg&& other) noexcept													= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The FFMpeg object to copy.
			 * @return A reference to this object.
			 */
			FFMpeg& operator=(const FFMpeg& other)											= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The FFMpeg object to move.
			 * @return A reference to this object.
			 */
			FFMpeg& operator=(FFMpeg&& other) noexcept										= default;

			/**
			 * @brief Default destructor.
			 */
			~FFMpeg() noexcept 																= default;

			/**
			 * @brief Get the list of supported codecs.
			 * @return The list of supported codecs.
			 */
			static const std::unordered_map<std::string, std::shared_ptr<const Codec>>		CodecRegistry();
			
			/**
			 * @brief Get the version of the FFMpeg library.
			 * @return The version of the FFMpeg library.
			 */
			static const std::string 														Version();

		private:
			/* The following needs to be const char* to be accessed for other static initializators */
			static const std::filesystem::path												FFMpegPath();				///< The path to the FFMpeg executable.
			static const std::filesystem::path												FFProbePath();				///< The path to the FFProbe executable.
			
			/**
			 * @brief Default constructor.
			 */
			FFMpeg() noexcept 																= default;

			/**
			 * @brief Splits string into a set of words.
			 * @param str The string to split.
			 * @return The set of words.
			 */
			static std::vector<std::string> SplitToVector(const std::string& str);
	};
}