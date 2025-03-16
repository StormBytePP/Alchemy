#pragma once

#include <Alchemy/exception.hxx>
#include <Alchemy/media/alias.hxx>
#include <StormByte/alias.hxx>
#include <StormByte/multimedia/media/tags.hxx>

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Forward declarations
namespace Json { class Value; }

/**
 * @namespace Media
 * @brief All the media related classes and functions.
 */
namespace Alchemy {
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
			virtual ~FFMpeg() noexcept 															= default;

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
			 * @brief Get the list of streams.
			 * @param path The path to the file.
¡			 * @return The list of streams.
			 */
			static StormByte::Expected<FFMpeg, StreamError>										FromFile(const std::filesystem::path& path);

			/**
			 * @brief Get the version of the FFMpeg library.
			 * @return The version of the FFMpeg library.
			 */
			static const std::string 															Version();

		protected:
			Media::Streams																		m_streams;					///< The list of streams.

			/**
			 * @brief Default constructor.
			 */
			FFMpeg() noexcept 																	= default;

		private:

			/**
			 * @brief Parse JSON string.
			 * @param json The JSON string.
			 * @return The list of streams.
			 */
			static StormByte::Expected<Media::Streams, StreamError>								ParseJSon(const std::string& json);

			/**
			 * @brief Parse Attachment.
			 * @param root The JSON value.
			 * @return The list of streams.
			 */
			static StormByte::Expected<Media::Stream::PointerType, StreamError>					ParseAttachmentJson(const Json::Value& audio_json);

			/**
			 * @brief Parse Audio.
			 * @param root The JSON value.
			 * @return The list of streams.
			 */
			static StormByte::Expected<Media::Stream::PointerType, StreamError>					ParseAudioJson(const Json::Value& audio_json);

			/**
			 * @brief Parse Image.
			 * @param root The JSON value.
			 * @return The list of streams.
			 */
			static StormByte::Expected<Media::Stream::PointerType, StreamError>					ParseImageJson(const Json::Value& audio_json);

			/**
			 * @brief Parse Video.
			 * @param root The JSON value.
			 * @return The list of streams.
			 */
			static StormByte::Expected<Media::Stream::PointerType, StreamError>					ParseVideoJson(const Json::Value& audio_json);

			/**
			 * @brief Parse Subtitle.
			 * @param root The JSON value.
			 * @return The list of streams.
			 */
			static StormByte::Expected<Media::Stream::PointerType, StreamError>					ParseSubtitleJson(const Json::Value& audio_json);

			/**
			 * @brief Parse tags.
			 * @param tags The JSON value.
			 * @param tag_name The name of the tag.
			 * @return The list of streams.
			 */
			static StormByte::Multimedia::Media::Tags											ParseTags(const Json::Value& tags, const std::string& tag_name);
	};
}