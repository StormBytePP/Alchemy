#include <Alchemy/process/ffmpeg.hxx>

using namespace Alchemy::Process;

FFMpeg::FFMpeg(const std::vector<std::string>& params) noexcept: StormByte::System::Process(ExecutablePath(), params) {}

FFMpeg::FFMpeg(std::vector<std::string>&& params) noexcept: StormByte::System::Process(ExecutablePath(), std::move(params)) {}