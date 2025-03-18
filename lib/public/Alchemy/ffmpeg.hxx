#pragma once

#include <Alchemy/exception.hxx>
#include <Alchemy/media/alias.hxx>
#include <StormByte/alias.hxx>
#include <StormByte/multimedia/media/property/tags.hxx>

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Forward declarations
namespace Json { class Value; }

/**
 * @namespace Alchemy
 * @brief All the Alchemy related classes and functions.
 */
namespace Alchemy {
	/**
	 * @class FFMpeg
	 * @brief The FFMpeg class.
	 */
	class ALCHEMY_PUBLIC FFMpeg {
		friend class FFProbe;
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
			 * @brief Get the path to the FFMpeg executable.
			 * @return The path to the FFMpeg executable.
			 */
			static const std::filesystem::path& 												Executable() noexcept;

			/**
			 * @brief Processes the file and creates a FFMpeg object.
			 * @param path The path to the file.
			 * @return The FFMpeg object.
			 */
			static StormByte::Expected<FFMpeg, StreamError> 									FromFile(const std::filesystem::path& path);

			static bool 																		IsHDRPlus(const std::filesystem::path& path);

			/**
			 * @brief Gets the streams
			 * @return The streams.
			 */
			Media::Streams& 																	Streams() noexcept;

			/**
			 * @brief Gets the streams
			 * @return The streams.
			 */
			const Media::Streams& 																Streams() const noexcept;

			/**
			 * @brief Get the path to the file.
			 * @return The path to the file.
			 */
			const std::filesystem::path& 														Path() const noexcept;

			/**
			 * @brief Get the version of the FFMpeg library.
			 * @return The version of the FFMpeg library.
			 */
			static const std::string 															Version();

		protected:
			std::filesystem::path																m_path;						///< The path to the file.
			Media::Streams																		m_streams;					///< The list of streams.
			static const std::filesystem::path 													c_path;						///< The path to the FFMpeg executable.

			/**
			 * @brief Default constructor.
			 */
			FFMpeg(const std::filesystem::path& path) noexcept;
	};
}