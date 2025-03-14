#pragma once

#include <Alchemy/visibility.h>

#include <array>
#include <string>

/**
 * @namespace Flags
 * @brief The namespace for media flags.
 */
namespace Alchemy::Media::Flags {
	/**
	 * @brief Base class for flag objects.
	 * @tparam N The number of flags.
	 */
	template<std::size_t N>
	class ALCHEMY_PUBLIC Base {
		public:
			/**
			 * @brief Constructor.
			 * @param flags The flags.
			 */
			Base(const std::string& flags) {
				// Safe initialization
				m_flags.fill('.');
				const auto length = flags.length();
				for (auto i = 0; i < N && i < length; ++i) {
					if (std::isalpha(flags[i])) m_flags[i] = flags[i];
				}
			}

			/**
			 * @brief Copy constructor.
			 * @param other The Base object to copy.
			 */
			Base(const Base& other)									= default;

			/**
			 * @brief Move constructor.
			 * @param other The Base object to move.
			 */
			Base(Base&& other) noexcept								= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The Base object to copy.
			 * @return A reference to this object.
			 */
			Base& operator=(const Base& other)						= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The Base object to move.
			 * @return A reference to this object.
			 */
			Base& operator=(Base&& other) noexcept					= default;

			/**
			 * @brief Default destructor.
			 */
			virtual ~Base() noexcept 								= default;

			std::string 											ToString() const {
				return std::string(m_flags.data(), N);
			}

		protected:
			std::array<char, N> 									m_flags;		///< The flags.
	};	
}