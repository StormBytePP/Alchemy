#include <Alchemy/hdr10plus_tool.hxx>
#include <Alchemy/ffmpeg.hxx>
#include <StormByte/util/system.hxx>
#include <StormByte/system/process.hxx>

using namespace Alchemy;

HDR10PlusTool::HDR10PlusTool(const std::filesystem::path& path) noexcept: m_path(path) {}

bool HDR10PlusTool::IsHDRPlus() const {
	if (!std::filesystem::exists(m_path)) {
		return false;
	}

	StormByte::System::Process ffmpeg(FFMpeg::Executable(), {"-hide_banner", "-loglevel", "panic", "-i", m_path.string(), "-c:v", "copy", "-bsf:v", "hevc_mp4toannexb", "-f", "hevc", "-"});
	StormByte::System::Process hdr10plus_tool(Executable(), {"--verify", "extract", "-"});
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

	StormByte::System::Process ffmpeg(FFMpeg::Executable(), {"-hide_banner", "-loglevel", "panic", "-i", m_path.string(), "-c:v", "copy", "-bsf:v", "hevc_mp4toannexb", "-f", "hevc", "-"});
	StormByte::System::Process hdr10plus_tool(Executable(), {"extract", "-o", metadata_path.string()});
	ffmpeg >> hdr10plus_tool;

	ffmpeg.Wait();
	int status = hdr10plus_tool.Wait();

	if (status != 0)
		return StormByte::Unexpected<Exception>(Exception("Failed to extract metadata"));

	return metadata_path;
}