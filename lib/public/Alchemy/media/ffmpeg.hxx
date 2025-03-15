#pragma once

#include <Alchemy/media/alias.hxx>
#include <Alchemy/media/codec.hxx>
#include <Alchemy/exception.hxx>

#include <StormByte/alias.hxx>

#include <filesystem>
#include <memory>
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
			FFMpeg(const FFMpeg& other)															= default;

			/**
			 * @brief Move constructor.
			 * @param other The FFMpeg object to move.
			 */
			FFMpeg(FFMpeg&& other) noexcept														= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The FFMpeg object to copy.
			 * @return A reference to this object.
			 */
			FFMpeg& operator=(const FFMpeg& other)												= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The FFMpeg object to move.
			 * @return A reference to this object.
			 */
			FFMpeg& operator=(FFMpeg&& other) noexcept											= default;

			/**
			 * @brief Default destructor.
				*/
				~FFMpeg() noexcept 																= default;

			/**
			 * @brief Get codec information
			 * @param name The name of the codec.
			 * @return Codec
			 */
			static std::shared_ptr<const Codec>													Codec(const std::string& name);
			
			/**
			 * @brief Get the version of the FFMpeg library.
			 * @return The version of the FFMpeg library.
			 */
			static const std::string 															Version();

			/**
			 * @brief Get the list of streams.
			 * @param path The path to the file.
¡			 * @return The list of streams.
			 */
			static StormByte::Expected<FFMpeg, Exception>										FromFile(const std::filesystem::path& path);

		private:
			Streams																				m_streams;					///< The list of streams.

			/**
			 * @brief Default constructor.
			 */
			FFMpeg() noexcept 																	= default;

			/**
			 * @brief Path to FFMpeg executable
			 * @return The path to the FFMpeg executable.
			 */
			static const std::filesystem::path													FFMpegPath();

			/**
			 * @brief Path to FFProbe executable
			 * @return The path to the FFProbe executable.
			 */
			static const std::filesystem::path													FFProbePath();

			/**
			 * @brief Get the list of supported codecs.
			 * @return The list of supported codecs.
			 */
			static const std::unordered_map<std::string, std::shared_ptr<const Media::Codec>>	CodecRegistry;

			/**
			 * @brief Splits string into a set of words.
			 * @param str The string to split.
			 * @return The set of words.
			 */
			static std::vector<std::string> 													SplitToVector(const std::string& str);

			/**
			 * @brief Parse JSON string.
			 * @param json The JSON string.
			 * @return The list of streams.
			 */
			static StormByte::Expected<Streams, Exception>										ParseJSon(const std::string& json);
	};
}