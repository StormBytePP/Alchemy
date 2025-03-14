#pragma once

#include <Alchemy/media/flags/codec.hxx>

#include <string>
#include <span>
#include <vector>

/**
 * @namespace Media
 * @brief All the media related classes and functions.
 */
namespace Alchemy::Media {
	/**
	 * @brief The codec structure.
	 */
	class ALCHEMY_PUBLIC Codec {
		public:
		/**
		 * @brief Constructor.
		 * @param name The name of the codec.
		 * @param flags The flags of the codec.
		 */
		Codec(const std::string& name, const std::string& flags);

		/**
		 * @brief Constructor.
		 * @param name The name of the codec.
		 * @param flags The flags of the codec.
		 */
		Codec(std::string&& name, std::string&& flags);

		/**
		 * @brief Copy constructor.
		 * @param other The Codec object to copy.
		 */
		Codec(const Codec& other)									= default;

		/**
		 * @brief Move constructor.
		 * @param other The Codec object to move.
		 */
		Codec(Codec&& other) noexcept								= default;

		/**
		 * @brief Copy assignment operator.
		 * @param other The Codec object to copy.
		 * @return A reference to this object.
		 */
		Codec& operator=(const Codec& other)						= default;

		/**
		 * @brief Move assignment operator.
		 * @param other The Codec object to move.
		 * @return A reference to this object.
		 */
		Codec& operator=(Codec&& other) noexcept					= default;

		/**
		 * @brief Default destructor.
		 */
		~Codec() noexcept 											= default;

		/**
		 * @brief Get the name of the codec.
		 * @return The name of the codec.
		 */
		const std::string& 											Name() const;

		/**
		 * @brief Get the flags of the codec.
		 * @return The flags of the codec.
		 */
		const Flags::Codec& 										Flags() const;

		/**
		 * @brief Get the encoders supported by the codec.
		 * @return The encoders supported by the codec.
		 */
		constexpr std::span<const std::string> 						Encoders() const {
			return {m_encoders.data(), m_encoders.size()};
		}

		/**
		 * @brief Set the encoders supported by the codec.
		 * @param encoders The encoders supported by the codec.
		 */
		void 														Encoders(const std::vector<std::string>& encoders);
		/**
		 * @brief Set the encoders supported by the codec.
		 * @param encoders The encoders supported by the codec.
		 */
		void 														Encoders(std::vector<std::string>&& encoders);

		/**
		 * @brief Get the decoders supported by the codec.
		 * @return The decoders supported by the codec.
		 */
		constexpr std::span<const std::string> 						Decoders() const {
			return {m_decoders.data(), m_decoders.size()};
		}

		/**
		 * @brief Set the decoders supported by the codec.
		 * @param decoders The decoders supported by the codec.
		 */
		void 														Decoders(const std::vector<std::string>& decoders);

		/**
		 * @brief Set the decoders supported by the codec.
		 * @param decoders The decoders supported by the codec.
		 */
		void 														Decoders(std::vector<std::string>&& decoders);

	private:
		std::string m_name; 						///< The name of the codec.
		Flags::Codec m_flags; 						///< The flags of the codec.
		std::vector<std::string> m_encoders; 		///< The encoders supported by the codec.
		std::vector<std::string> m_decoders; 		///< The decoders supported by the codec.
	};
}