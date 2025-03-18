#include <Alchemy/process/hdr10plus_tool.hxx>

using namespace Alchemy::Process;

HDR10PlusTool::HDR10PlusTool(const std::vector<std::string>& params) noexcept: StormByte::System::Process(ExecutablePath(), params) {}

HDR10PlusTool::HDR10PlusTool(std::vector<std::string>&& params) noexcept: StormByte::System::Process(ExecutablePath(), std::move(params)) {}