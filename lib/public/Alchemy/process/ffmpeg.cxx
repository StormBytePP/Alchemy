#include <Alchemy/process/ffmpeg.hxx>
#include <StormByte/util/string.hxx>

#include <regex>

using namespace Alchemy::Process;

FFMpeg::FFMpeg(const std::vector<std::string>& params) noexcept: StormByte::System::Process(ExecutablePath(), params) {}

FFMpeg::FFMpeg(std::vector<std::string>&& params) noexcept: StormByte::System::Process(ExecutablePath(), std::move(params)) {}

unsigned long FFMpeg::CurrentFrame() const {
	static std::regex pattern(R"(frame=([^\n\r]*))");
	std::string output;
	*this >> output;
	std::sregex_iterator begin(output.begin(), output.end(), pattern);
	std::sregex_iterator end;

	std::optional<std::string> last_value;
	for (std::sregex_iterator it = begin; it != end; ++it) {
		last_value = (*it)[1].str(); // Capture group 1 (the value after '=')
	}

	if (!last_value || !StormByte::Util::String::IsNumeric(last_value.value()))
		return 0;
	else
		return std::stoul(last_value.value());
}