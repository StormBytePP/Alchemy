#include <Alchemy/process/ffprobe.hxx>

using namespace Alchemy::Process;

FFProbe::FFProbe(const std::vector<std::string>& params) noexcept: StormByte::System::Process(ExecutablePath(), params) {}

FFProbe::FFProbe(std::vector<std::string>&& params) noexcept: StormByte::System::Process(ExecutablePath(), std::move(params)) {}