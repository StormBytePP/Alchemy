#pragma once

#include <Alchemy/visibility.h>
#include <StormByte/system/process.hxx>

/**
 * @namespace Process
 * @brief All the Alchemy related processes
 */
namespace Alchemy::Process {
	class ALCHEMY_PUBLIC FFMpeg final: public StormByte::System::Process {
		public:
			/**
			 * @brief Default constructor.
			 * @param params The parameters to pass to the FFMpeg executable.
			 */
			FFMpeg(const std::vector<std::string>& params) noexcept;

			/**
			 * @brief Default constructor.
			 * @param params The parameters to pass to the FFMpeg executable.
			 */
			FFMpeg(std::vector<std::string>&& params) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param other The FFProbe object to copy.
			 */
			FFMpeg(const FFMpeg& other) 							= default;

			/**
			 * @brief Move constructor.
			 * @param other The FFProbe object to move.
			 */
			FFMpeg(FFMpeg&& other) noexcept 						= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The FFProbe object to copy.
			 * @return A reference to this object.
			 */
			FFMpeg& operator=(const FFMpeg& other) 					= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The FFProbe object to move.
			 * @return A reference to this object.
			 */
			FFMpeg& operator=(FFMpeg&& other) noexcept 				= default;

			/**
			 * @brief Default destructor.
			*/
			~FFMpeg() noexcept override 							= default;

			/**
			 * @brief Get the path to the FFMpeg executable.
			 * @return The path to the FFMpeg executable.
			 */
			static const std::filesystem::path& 					ExecutablePath() noexcept; // Implemented by cmake generated file

			/**
			 * @brief Get the current frame.
			 * @return The current frame.
			 */
			unsigned long 											CurrentFrame() const;
	};
}
