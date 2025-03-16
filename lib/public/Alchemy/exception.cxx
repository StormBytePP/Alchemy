#include <Alchemy/exception.hxx>

using namespace Alchemy;

Exception::Exception(const std::string& message):StormByte::Exception(message) {}

StreamError::StreamError(const std::string& message):Exception(message) {}