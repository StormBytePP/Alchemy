#include <Alchemy/media/ffmpeg.hxx>
#include <StormByte/test_handlers.h>

using namespace Alchemy;

int dummy_test() {
	std::cout << FFMpeg::Version() << std::endl;
	RETURN_TEST("dummy_test", 0);
}

int main() {
	return dummy_test();
}