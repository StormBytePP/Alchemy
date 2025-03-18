#pragma once

#include <Alchemy/media/alias.hxx>
#include <Alchemy/media/flags/codec.hxx>
#include <StormByte/multimedia/codec.hxx>

#include <memory>

/**
 * @namespace Media
 * @brief All the media related classes and functions.
 */
namespace Alchemy::Media {
	/**
	 * @class Codec
	 * @brief The codec class.
	 */
	class ALCHEMY_PUBLIC Codec: public StormByte::Multimedia::Codec {
		public:
			using PointerType 		= std::shared_ptr<const Codec>;		///< The pointer type.

			/**
			 * @brief Constructor.
			 * @param id The codec ID.
			 * @param name The codec name.
			 * @param long_name The codec long name.
			 * @param flags The codec flags.
			 * @param decoders The decoders.
			 * @param encoders The encoders.
			 */
			Codec(const std::string& name, const std::string& long_name, const Flags::Codec& flags, const Decoders& decoders, const Encoders& encoders);

			/**
			 * @brief Constructor.
			 * @param name The codec name.
			 * @param long_name The codec long name.
			 * @param flags The codec flags.
			 * @param decoders The decoders.
			 * @param encoders The encoders.
			 */
			Codec(std::string&& name, std::string&& long_name, Flags::Codec&& flags, Decoders&& decoders, Encoders&& encoders);

			/**
			 * @brief Copy constructor.
			 * @param other The Codec object to copy.
			 */
			Codec(const Codec& other)											= default;

			/**
			 * @brief Move constructor.
			 * @param other The Codec object to move.
			 */
			Codec(Codec&& other) noexcept										= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The Codec object to copy.
			 * @return A reference to this object.
			 */
			Codec& operator=(const Codec& other)								= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The Codec object to move.
			 * @return A reference to this object.
			 */
			Codec& operator=(Codec&& other) noexcept							= default;

			/**
			 * @brief Default destructor.
			 */
			~Codec() noexcept override 											= default;

			/**
			 * @brief Gets the codec flags.
			 * @return The codec flags.
			 */
			const Flags::Codec* 												Flags() const noexcept override;

			/**
			 * @brief Gets the codec type
			 * @return Gets type
			 */
			StormByte::Multimedia::Media::Type 									Type() const noexcept override;

			/**
			 * @brief Gets the decoders.
			 * @return The decoders.
			 */
			Media::Decoders& 													Decoders() noexcept;

			/**
			 * @brief Gets the decoders.
			 * @return The decoders.
			 */
			const Media::Decoders& 												Decoders() const noexcept;

			/**
			 * @brief Gets the encoders.
			 * @return The encoders.
			 */
			Media::Encoders& 													Encoders() noexcept;

			/**
			 * @brief Gets the encoders.
			 * @return The encoders.
			 */
			const Media::Encoders& 												Encoders() const noexcept;

		private:
			Media::Decoders m_decoders;											///< The decoders.
			Media::Encoders m_encoders;											///< The encoders.
	};
}