#pragma once

#include <Alchemy/media/alias.hxx>
#include <Alchemy/media/flags/codec.hxx>

#include <string>

/**
 * @namespace Codec
 * @brief The namespace for all multimedia media codec information.
 */
namespace Alchemy::Media::Codec {
	using ID = StormByte::Multimedia::Media::Codec::ID;	///< Alias for the codec name.
	using Type = StormByte::Multimedia::Media::Type;		///< Alias for the codec type.

	/**
	 * @struct CodecInfo
	 * @brief Holds detailed information about a codec.
	 */
	class ALCHEMY_PUBLIC Info {
		public:
			using PointerType 		= std::shared_ptr<const Info>;		///< Alias for the shared pointer to the codec info.
			
			/**
			 * @brief Constructor.
			 * @param id The ID of the codec.
			 * @param name The name of the codec.
			 * @param long_name The long name of the codec.
			 * @param type The type of the codec.
			 * @param flags The flags of the codec.
			 * @param decoders The list of decoders.
			 * @param encoders The list of encoders.
			 */
			Info(const ID& id, const std::string& name, const std::string& long_name, Type type, const Flags::Codec& flags, const Decoders& decoders, const Encoders& encoders);

			/**
			 * @brief Constructor.
			 * @param id The ID of the codec.
			 * @param name The name of the codec.
			 * @param type The type of the codec.
			 * @param type The type of the codec.
			 * @param flags The flags of the codec.
			 * @param decoders The list of decoders.
			 * @param encoders The list of encoders.
			 */
			Info(ID&& id, std::string&& name, std::string&& long_name, Type&& type, Flags::Codec&& flags, Decoders&& decoders, Encoders&& encoders);

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
			const Codec::ID&									ID() const;

			/**
			 * @brief Retrieves the long name of the codec.
			 * @return The long name of the codec.
			 */
			const std::string&									Name() const;

			/**
			 * @brief Retrieves the long name of the codec.
			 * @return The long name of the codec.
			 */
			const std::string&									LongName() const;

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
			 * @brief Retrieves the list of decoders.
			 * @return The list of decoders.
			 */
			const Media::Decoders& 								Decoders() const;

			/**
			 * @brief Retrieves the list of encoders.
			 * @return The list of encoders.
			 */
			const Media::Encoders& 								Encoders() const;

		private:
			Codec::ID 											m_id;			///< Name of the codec
			std::string											m_name;			///< Long name of the codec.
			std::string											m_long_name;	///< Long name of the codec.
			Codec::Type 										m_type;			///< Type of the codec.
			Flags::Codec 										m_flags;		///< Flags of the codec.
			Media::Encoders 									m_encoders;		///< List of encoders.
			Media::Decoders 									m_decoders;		///< List of decoders.
	};
}
