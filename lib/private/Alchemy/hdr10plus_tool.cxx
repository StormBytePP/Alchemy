#include <Alchemy/hdr10plus_tool.hxx>
#include <Alchemy/process/hdr10plus_tool.hxx>
#include <Alchemy/process/ffmpeg.hxx>
#include <StormByte/util/system.hxx>
#include <StormByte/system/process.hxx>

using namespace Alchemy;

HDR10PlusTool::HDR10PlusTool(const std::filesystem::path& path) noexcept: m_path(path) {}

bool HDR10PlusTool::IsHDRPlus() const {
	if (!std::filesystem::exists(m_path)) {
		return false;
	}

	Process::FFMpeg ffmpeg({"-hide_banner", "-loglevel", "panic", "-i", m_path.string(), "-c:v", "copy", "-bsf:v", "hevc_mp4toannexb", "-f", "hevc", "-"});
	Process::HDR10PlusTool hdr10plus_tool({"--verify", "extract", "-"});
	ffmpeg >> hdr10plus_tool;

	ffmpeg.Wait();
	int status = hdr10plus_tool.Wait();

	return status == 0;
}

StormByte::Expected<std::filesystem::path, Exception> HDR10PlusTool::ExtractMetadata() const {
	if (!std::filesystem::exists(m_path)) {
		return StormByte::Unexpected<Exception>("File does not exist");
	}

	std::filesystem::path metadata_path = StormByte::Util::System::TempFileName();

	Process::FFMpeg ffmpeg({"-hide_banner", "-loglevel", "panic", "-i", m_path.string(), "-c:v", "copy", "-bsf:v", "hevc_mp4toannexb", "-f", "hevc", "-"});
	Process::HDR10PlusTool hdr10plus_tool({"extract", "-o", metadata_path.string(), "-"});
	ffmpeg >> hdr10plus_tool;
	ffmpeg.Wait();
	int status = hdr10plus_tool.Wait();

	if (status != 0)
		return StormByte::Unexpected<Exception>(Exception("Failed to extract metadata"));

	return metadata_path;
}