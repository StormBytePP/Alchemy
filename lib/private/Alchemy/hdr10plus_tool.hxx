#pragma once

#include <Alchemy/exception.hxx>
#include <StormByte/expected.hxx>

#include <filesystem>

/**
 * @namespace Alchemy
 * @brief All the Alchemy related classes and functions.
 */
namespace Alchemy {
	/**
	 * @class HDR10PlusTool
	 * @brief The HDR10+ tool class.
	 */
	class ALCHEMY_PRIVATE HDR10PlusTool {
		public:
			/**
			 * @brief Default constructor.
			 * @param path The path to the HDR10+ tool.
			 */
			HDR10PlusTool(const std::filesystem::path& path) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param other The HDR10PlusTool object to copy.
			 */
			HDR10PlusTool(const HDR10PlusTool& other) 							= default;

			/**
			 * @brief Move constructor.
			 * @param other The HDR10PlusTool object to move.
			 */
			HDR10PlusTool(HDR10PlusTool&& other) noexcept 						= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The HDR10PlusTool object to copy.
			 * @return A reference to this object.
			 */
			HDR10PlusTool& operator=(const HDR10PlusTool& other) 				= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The HDR10PlusTool object to move.
			 * @return A reference to this object.
			 */
			HDR10PlusTool& operator=(HDR10PlusTool&& other) noexcept 			= default;

			/**
			 * @brief Default destructor.
			*/
			~HDR10PlusTool() noexcept 											= default;

			/**
			 * @brief Checks if the file is HDR10+.
			 * @param path The path to the file.
			 * @return True if the file is HDR10+, false otherwise.
			 */
			bool 																IsHDRPlus() const;

			/**
			 * @brief Extracts the metadata from the file.
			 * @return The path to the metadata file.
			 */
			StormByte::Expected<std::filesystem::path, Exception> 				ExtractMetadata() const;

		private:
			std::filesystem::path m_path;	///< The path to the file
	};
}