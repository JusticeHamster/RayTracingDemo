#include "not_implemented_exception.hpp"

not_implemented_exception::not_implemented_exception(const std::string &message): std::logic_error(message)
{

}
