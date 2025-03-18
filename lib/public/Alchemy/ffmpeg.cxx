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

const std::string FFMpeg::Version() {
	static const std::regex versionRegex(R"(ffmpeg version (\d+\.\d+(?:\.\d+)?))");
	StormByte::System::Process process(Executable(), {"-version"});
	std::string result;
	process >> result;
	process.Wait();
	std::smatch match;
	if (std::regex_search(result, match, versionRegex)) {
		return match[1];
	}
	return "Unknown";
}
