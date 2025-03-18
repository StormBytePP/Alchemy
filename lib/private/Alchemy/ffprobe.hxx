#pragma once

#include <Alchemy/exception.hxx>
#include <Alchemy/ffmpeg.hxx>
#include <StormByte/expected.hxx>
#include <json/json.h>

#include <filesystem>
#include <string>
#include <vector>

/**
 * @namespace Alchemy
 * @brief All the Alchemy related classes and functions.
 */
namespace Alchemy {
	class ALCHEMY_PRIVATE FFProbe final {
		public:
			/**
			 * @brief Default constructor.
			 * @param path The path to the file.
			 */
			FFProbe(const std::filesystem::path& path) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param other The FFProbe object to copy.
			 */
			FFProbe(const FFProbe& other) 					= default;

			/**
			 * @brief Move constructor.
			 * @param other The FFProbe object to move.
			 */
			FFProbe(FFProbe&& other) noexcept 				= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The FFProbe object to copy.
			 * @return A reference to this object.
			 */
			FFProbe& operator=(const FFProbe& other) 		= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The FFProbe object to move.
			 * @return A reference to this object.
			 */
			FFProbe& operator=(FFProbe&& other) noexcept 	= default;

			/**
			 * @brief Default destructor.
			*/
			~FFProbe() noexcept 							= default;

			/**
			 * @brief Get the path to the FFMpeg executable.
			 * @return The path to the FFMpeg executable.
			 */
			static const std::filesystem::path& 			Executable() noexcept; // Implemented by cmake generated file

			/**
			 * Processes the FFMpeg object.
			 */
			StormByte::Expected<FFMpeg, StreamError>		Process() const;

			/**
			 * @brief Get number of frames of the video stream
			 * @return The number of frames of the video stream.
			 */
			StormByte::Expected<unsigned long, StreamError>	FrameCount() const;

		private:
			const std::filesystem::path m_path;				///< The path to the file.

			/**
			 * @brief Get the list of streams.
			 * @return The list of streams.
			 */
			const Json::Value 								StreamList() const;

			/**
			 * Gets the audio stream json information
			 * @param index The index of the stream.
			 * @return The audio stream json information.
			 */
			const Json::Value 								StreamJson(const unsigned short& index) const;

			/**
			 * Gets the video color json information
			 * @param index The index of the stream.
			 * @return The video color json information.
			 */
			const Json::Value								VideoColorJson(const unsigned short& index) const;

			/**
			 * @brief Execute the FFProbe command.
			 * @param arguments The arguments to pass to the FFProbe command.
			 * @return The result of the FFProbe command as JSon
			 */
			const Json::Value 								Execute(std::vector<std::string>&& arguments, const std::string& root_name) const;

			/**
			 * @brief Parse the stream json information.
			 * @tparam StreamType The stream type.
			 * @param stream_json The stream json information.
			 * @return The stream pointer.
			 */
			template<class StreamType>
			StormByte::Expected<Media::Stream::PointerType, StreamError>	ParseStreamJson(const Json::Value& stream_json) const;

			/**
			 * @brief Parse the tags json information.
			 * @param stream_json The stream json information.
			 * @param stream The stream pointer.
			 */
			void 															ParseTagsJson(const Json::Value& stream_json, Media::Stream::PointerType stream) const;
	};
}