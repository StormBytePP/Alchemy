#pragma once

#include <Alchemy/visibility.h>
#include <StormByte/exception.hxx>

#include <filesystem>

/**
 * @namespace Alchemy
 * @brief All the classes and functions of the Alchemy library.
 */
namespace Alchemy {
	/**
	 * @class Exception
	 * @brief The base exception class for the Alchemy library.
	 */
	class ALCHEMY_PUBLIC Exception:public StormByte::Exception {
		public:
			/**
			 * @brief Constructor.
			 * @param message The message of the exception.
			 */
			Exception(const std::string& message);

			/**
			 * @brief Copy constructor.
			 * @param other The Exception object to copy.
			 */
			Exception(const Exception& other) 						= default;

			/**
			 * @brief Move constructor.
			 * @param other The Exception object to move.
			 */
			Exception(Exception&& other) noexcept 					= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The Exception object to copy.
			 * @return A reference to this object.
			 */
			Exception& operator=(const Exception& other) 			= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The Exception object to move.
			 * @return A reference to this object.
			 */
			Exception& operator=(Exception&& other) noexcept 		= default;

			/**
			 * @brief Destructor.
			 */
			virtual ~Exception() noexcept 							= default;
	};
}