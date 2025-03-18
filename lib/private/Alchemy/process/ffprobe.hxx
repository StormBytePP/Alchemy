#pragma once

#include <Alchemy/visibility.h>
#include <StormByte/system/process.hxx>

/**
 * @namespace Process
 * @brief All the Alchemy related processes
 */
namespace Alchemy::Process {
	class ALCHEMY_PRIVATE FFProbe final: public StormByte::System::Process {
		public:
			/**
			 * @brief Default constructor.
			 * @param params The parameters to pass to the FFProbe executable.
			 */
			FFProbe(const std::vector<std::string>& params) noexcept;

			/**
			 * @brief Default constructor.
			 * @param params The parameters to pass to the FFProbe executable.
			 */
			FFProbe(std::vector<std::string>&& params) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param other The FFProbe object to copy.
			 */
			FFProbe(const FFProbe& other) 							= default;

			/**
			 * @brief Move constructor.
			 * @param other The FFProbe object to move.
			 */
			FFProbe(FFProbe&& other) noexcept 						= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The FFProbe object to copy.
			 * @return A reference to this object.
			 */
			FFProbe& operator=(const FFProbe& other) 				= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The FFProbe object to move.
			 * @return A reference to this object.
			 */
			FFProbe& operator=(FFProbe&& other) noexcept 			= default;

			/**
			 * @brief Default destructor.
			*/
			~FFProbe() noexcept override 							= default;

			/**
			 * @brief Get the path to the FFProbe executable.
			 * @return The path to the FFProbe executable.
			 */
			static const std::filesystem::path& 					ExecutablePath() noexcept; // Implemented by cmake generated file
	};
}
