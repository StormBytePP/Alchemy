#include <Alchemy/media/codec.hxx>

using namespace Alchemy::Media;

Codec::Codec(const std::string& name, const std::string& flags):m_name(name), m_flags(flags) {}

Codec::Codec(std::string&& name, std::string&& flags):m_name(std::move(name)), m_flags(std::move(flags)) {}

void Codec::Decoders(const std::vector<std::string>& decoders) {
	m_decoders = decoders;
}

void Codec::Decoders(std::vector<std::string>&& decoders) {
	m_decoders = std::move(decoders);
}

void Codec::Encoders(const std::vector<std::string>& encoders) {
	m_encoders = encoders;
}

void Codec::Encoders(std::vector<std::string>&& encoders) {
	m_encoders = std::move(encoders);
}

const std::string& Codec::Name() const {
	return m_name;
}

const Flags::Codec& Codec::Flags() const {
	return m_flags;
}