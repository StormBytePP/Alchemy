#include <Alchemy/media/codec.hxx>

using namespace Alchemy::Media;

Codec::Codec(const std::string& name, const std::string& long_name, const Flags::Codec& flags, const Media::Decoders& decoders, const Media::Encoders& encoders):
StormByte::Multimedia::Codec(name, long_name, flags), m_decoders(decoders), m_encoders(encoders) {}

Codec::Codec(std::string&& name, std::string&& long_name, Flags::Codec&& flags, Media::Decoders&& decoders, Media::Encoders&& encoders):
StormByte::Multimedia::Codec(std::move(name), std::move(long_name), std::move(flags)), m_decoders(std::move(decoders)), m_encoders(std::move(encoders)) {}

Alchemy::Media::Decoders& Codec::Decoders() noexcept {
	return m_decoders;
}

const Alchemy::Media::Decoders& Codec::Decoders() const noexcept {
	return m_decoders;
}

Alchemy::Media::Encoders& Codec::Encoders() noexcept {
	return m_encoders;
}

const Alchemy::Media::Encoders& Codec::Encoders() const noexcept {
	return m_encoders;
}

const Flags::Codec* Codec::Flags() const noexcept {
	return std::static_pointer_cast<const Flags::Codec>(m_flags).get();
}

StormByte::Multimedia::Media::Type Codec::Type() const noexcept {
	return Flags()->Type();
}