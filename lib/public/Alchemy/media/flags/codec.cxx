#include <Alchemy/media/flags/codec.hxx>

#include <cstring>

using namespace Alchemy::Media::Flags;

Codec::Codec(const char* flags):Base(flags) {}

bool Codec::DecodeSupported() const {
	return m_flags[0] == 'D';
}

bool Codec::EncodeSupported() const {
	return m_flags[1] == 'E';
}

bool Codec::LossySupported() const {
	return m_flags[4] == 'L';
}

bool Codec::LosslessSupported() const {
	return m_flags[5] == 'S';
}

StormByte::Multimedia::Media::Type Codec::Type() const {
	switch (m_flags[2]) {
		case 'A':
			return StormByte::Multimedia::Media::Type::Audio;
		case 'V':
			return StormByte::Multimedia::Media::Type::Video;
		case 'S':
			return StormByte::Multimedia::Media::Type::Subtitle;
		case 'T':
			return StormByte::Multimedia::Media::Type::Attachment;
		default:
			return StormByte::Multimedia::Media::Type::Unknown;
	}
}