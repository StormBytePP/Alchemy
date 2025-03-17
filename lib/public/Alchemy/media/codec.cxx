#include <Alchemy/media/codec.hxx>

using namespace Alchemy::Media;

Codec::Info::Info(const Codec::Name& name, const std::string& long_name, Codec::Type type, const Flags::Codec& flags, const Media::Encoders& encoders, const Media::Decoders& decoders):
m_name(name), m_long_name(long_name), m_type(type), m_flags(flags), m_encoders(encoders), m_decoders(decoders) {}

Codec::Info::Info(Codec::Name&& name, std::string&& long_name, Codec::Type&& type, Flags::Codec&& flags, Media::Encoders&& encoders, Media::Decoders&& decoders):
m_name(std::move(name)), m_long_name(std::move(long_name)), m_type(std::move(type)), m_flags(std::move(flags)), m_encoders(std::move(encoders)), m_decoders(std::move(decoders)) {}

const Codec::Name& Codec::Info::Name() const {
	return m_name;
}

Codec::Type Codec::Info::Type() const {
	return m_type;
}

const Flags::Codec& Codec::Info::Flags() const {
	return m_flags;
}

const Alchemy::Media::Decoders& Codec::Info::Decoders() const {
	return m_decoders;
}

const Alchemy::Media::Encoders& Codec::Info::Encoders() const {
	return m_encoders;
}