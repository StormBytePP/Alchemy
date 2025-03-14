#pragma once

#include <Alchemy/media/flags/base.hxx>

/**
 * @namespace Flags
 * @brief The namespace for media flags.
 */
namespace Alchemy::Media::Flags {
	class ALCHEMY_PUBLIC Container final: public Base<3> {
		public:
			/**
			 * @brief Constructor.
			 * @param flags The flags.
			 */
			Container(const char* flags);

			/**
			 * @brief Copy constructor.
			 * @param other The Container object to copy.
			 */
			Container(const Container& other)									= default;

			/**
			 * @brief Move constructor.
			 * @param other The Container object to move.
			 */
			Container(Container&& other) noexcept								= default;

			/**
			 * @brief Copy assignment operator.
			 * @param other The Container object to copy.
			 * @return A reference to this object.
			 */
			Container& operator=(const Container& other)						= default;

			/**
			 * @brief Move assignment operator.
			 * @param other The Container object to move.
			 * @return A reference to this object.
			 */
			Container& operator=(Container&& other) noexcept					= default;

			/**
			 * @brief Default destructor.
			 */
			~Container() noexcept 												= default;

			/**
			 * @brief Checks if the container supports muxing.
			 * @return True if the container supports muxing, false otherwise.
			 */
			bool 																MuxSupported() const;

			/**
			 * @brief Checks if the container supports demuxing.
			 * @return True if the container supports demuxing, false otherwise.
			 */
			bool 																DemuxSupported() const;
	};
}