#include <dummy.hxx>
#include <json/json.h>

#include "test_handlers.h"

int dummy_test() {
	std::cout << Alchemy::Dummy::dummy() << std::endl;
	RETURN_TEST("dummy_test", 0);
}

int main() {
	return dummy_test();
}