#pragma once

#include <Alchemy/media/flags/base.hxx>
#include <StormByte/multimedia/media/type.hxx>

#include <array>

/**
 * @namespace Flags
 * @brief The namespace for media flags.
 */
namespace Alchemy::Media::Flags {
	/**
	 * @brief The flags for the codec.
	 */
	class ALCHEMY_PUBLIC Codec final: public Base<5> {
		public:
			/**
			 * @brief Constructor.
			 * @param flags The flags.
			 */
			Codec(const std::string& flags);

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
			 * @brief Checks if the codec supports encoding.
			 * @return True if the codec supports encoding, false otherwise.
			 */
			bool 														EncodeSupported() const;

			/**
			 * @brief Checks if the codec supports decoding.
			 * @return True if the codec supports decoding, false otherwise.
			 */
			bool 														DecodeSupported() const;

			/**
			 * @brief Checks if the codec supports lossy encoding.
			 * @return True if the codec supports lossy encoding, false otherwise.
			 */
			bool 														LossySupported() const;

			/**
			 * @brief Checks if the codec supports lossless encoding.
			 * @return True if the codec supports lossless encoding, false otherwise.
			 */
			 bool 														LosslessSupported() const;

			/**
			 * @brief Gets the codec type.
			 * @return The codec type.
			 */
			StormByte::Multimedia::Media::Type 							Type() const;
	};	
}