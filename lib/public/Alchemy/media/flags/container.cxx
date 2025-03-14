#include <Alchemy/media/flags/container.hxx>

using namespace Alchemy::Media::Flags;

Container::Container(const char* flags):Base(flags) {}

bool Container::DemuxSupported() const {
	return m_flags[0] == 'D';
}

bool Container::MuxSupported() const {
	return m_flags[1] == 'E';
}