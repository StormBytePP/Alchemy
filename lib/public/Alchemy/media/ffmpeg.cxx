#include <Alchemy/media/ffmpeg.hxx>

const std::regex Alchemy::FFMpeg::c_supported_codecs_regex = std::regex(R"(^ (.{6}) (.{16}) (.+)$)");