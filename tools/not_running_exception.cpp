#include "not_running_exception.hpp"

not_running_exception::not_running_exception(std::string message): std::runtime_error(message)
{

}
