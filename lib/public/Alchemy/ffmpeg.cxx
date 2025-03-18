#include <Alchemy/ffmpeg.hxx>
#include <Alchemy/ffprobe.hxx>
#include <Alchemy/media/registry.hxx>
#include <StormByte/exception.hxx>
#include <StormByte/system/process.hxx>
#include <StormByte/util/string.hxx>

#include <format>
#include <json/json.h>
#include <regex>

using namespace Alchemy;

FFMpeg::FFMpeg(const std::filesystem::path& path) noexcept: m_path(path) {}

const std::filesystem::path& FFMpeg::Executable() noexcept {
	return c_path;
}

Media::Streams& FFMpeg::Streams() noexcept {
	return m_streams;
}

const Media::Streams& FFMpeg::Streams() const noexcept {
	return m_streams;
}

const std::filesystem::path& FFMpeg::Path() const noexcept {
	return m_path;
}

StormByte::Expected<FFMpeg, StreamError> FFMpeg::FromFile(const std::filesystem::path& path) {
	if (!std::filesystem::exists(path)) {
		return StormByte::Unexpected<StreamError>(std::format("File {} does not exist", path.string()));
	}
	FFProbe ffprobe(path);
	return ffprobe.Process();
}

bool FFMpeg::IsHDRPlus(const std::filesystem::path& path) {
	// ffmpeg -hide_banner -loglevel panic -i FILE -c:v copy -bsf:v hevc_mp4toannexb -f hevc - | hdr10plus_tool --verify extract -
	StormByte::System::Process ffmpeg(c_path, {"hide_banner", "-loglevel", "panic", "-c:v", "copy", "-bsf:v", "hevc_mp4toannexb", "-f", "hevc", "-i", path.string(), "-"});
}

const std::string FFMpeg::Version() {
	static const std::regex versionRegex(R"(ffmpeg version (\d+\.\d+(?:\.\d+)?))");
	StormByte::System::Process process(c_path, {"-version"});
	std::string result;
	process >> result;
	process.Wait();
	std::smatch match;
	if (std::regex_search(result, match, versionRegex)) {
		return match[1];
	}
	return "Unknown";
}
