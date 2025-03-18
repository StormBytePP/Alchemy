#pragma once

#include <Alchemy/visibility.h>
#include <StormByte/system/process.hxx>

/**
 * @namespace Process
 * @brief All the Alchemy related processes
 */
namespace Alchemy::Process {
	class ALCHEMY_PRIVATE HDR10PlusTool final: public StormByte::System::Process {
		public:
			/**
			 * @brief Default constructor.
			 * @param params The parameters to pass to the HDR10PlusTool executable.
			 */
			HDR10PlusTool(const std::vector<std::string>& params) noexcept;

			/**
			 * @brief Default constructor.
			 * @param params The parameters to pass to the HDR10PlusTool executable.
			 */
			HDR10PlusTool(std::vector<std::string>&& params) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param other The HDR10PlusTool object to copy.
			 */
			HDR10PlusTool(const HDR10PlusTool& other) 						= default;

			/**
			 * @brief Move constructor.
			 * @param other The HDR10PlusTool object to move.
			 */
			HDR10PlusTool(HDR10PlusTool&& other) noexcept 					= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The HDR10PlusTool object to copy.
			 * @return A reference to this object.
			 */
			HDR10PlusTool& operator=(const HDR10PlusTool& other) 			= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The HDR10PlusTool object to move.
			 * @return A reference to this object.
			 */
			HDR10PlusTool& operator=(HDR10PlusTool&& other) noexcept 		= default;

			/**
			 * @brief Default destructor.
			*/
			~HDR10PlusTool() noexcept override 								= default;

			/**
			 * @brief Get the path to the HDR10PlusTool executable.
			 * @return The path to the HDR10PlusTool executable.
			 */
			static const std::filesystem::path& 							ExecutablePath() noexcept; // Implemented by cmake generated file
	};
}
