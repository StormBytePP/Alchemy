#pragma once

#include <Alchemy/media/alias.hxx>
#include <Alchemy/media/flags/codec.hxx>

#include <string>
#include <unordered_map>
#include <vector>

/**
 * @namespace Codec
 * @brief The namespace for all multimedia media codec information.
 */
namespace Alchemy::Media::Codec {
	using Name = StormByte::Multimedia::Media::Codec::Name;	///< Alias for the codec name.
	using Type = StormByte::Multimedia::Media::Type;		///< Alias for the codec type.

	/**
	 * @struct CodecInfo
	 * @brief Holds detailed information about a codec.
	 */
	class ALCHEMY_PUBLIC Info {
		public:
			/**
			 * @brief Constructor.
			 * @param name The name of the codec.
			 * @param type The type of the codec.
			 * @param flags The flags of the codec.
			 * @param encoders The list of encoders.
			 * @param decoders The list of decoders.
			 */
			Info(const Name& name, Type type, const Flags::Codec& flags, const Encoders& encoders = {}, const Decoders& decoders = {});

			/**
			 * @brief Constructor.
			 * @param name The name of the codec.
			 * @param type The type of the codec.
			 * @param flags The flags of the codec.
			 * @param encoders The list of encoders.
			 * @param decoders The list of decoders.
			 */
			Info(Name&& name, Type&& type, Flags::Codec&& flags, Encoders&& encoders = {}, Decoders&& decoders = {});

			/**
			 * @brief Copy constructor.
			 * @param other The Info object to copy.
			 */
			Info(const Info& other) 							= default;

			/**
			 * @brief Move constructor.
			 * @param other The Info object to move.
			 */
			Info(Info&& other) noexcept 						= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The Info object to copy.
			 * @return A reference to this object.
			 */
			Info& operator=(const Info& other)					= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The Info object to move.
			 * @return A reference to this object.
			 */
			Info& operator=(Info&& other) noexcept 				= default;

			/**
			 * @brief Destructor.
			 */
			~Info() noexcept 									= default;

			/**
			 * @brief Retrieves the name of the codec.
			 * @return The name of the codec.
			 */
			const Codec::Name&									Name() const;

			/**
			 * @brief Retrieves the type of the codec.
			 * @return The type of the codec.
			 */
			Codec::Type 										Type() const;

			/**
			 * @brief Retrieves the flags of the codec.
			 * @return The flags of the codec.
			 */
			const Flags::Codec& 								Flags() const;

			/**
			 * @brief Retrieves the list of encoders.
			 * @return The list of encoders.
			 */
			const Media::Encoders& 								Encoders() const;

			/**
			 * @brief Retrieves the list of decoders.
			 * @return The list of decoders.
			 */
			const Media::Decoders& 								Decoders() const;

		private:
			Codec::Name 										m_name;			///< Name of the codec
			Codec::Type 										m_type;			///< Type of the codec.
			Flags::Codec 										m_flags;		///< Flags of the codec.
			Media::Encoders 									m_encoders;		///< List of encoders.
			Media::Decoders 									m_decoders;		///< List of decoders.
	};
}
