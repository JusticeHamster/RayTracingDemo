#ifndef NOT_IMPLEMENTED_EXCEPTION_HPP
#define NOT_IMPLEMENTED_EXCEPTION_HPP

#include <stdexcept>
#include <string>

class not_implemented_exception: public std::logic_error
{
public:
    not_implemented_exception(const std::string &message);
};

#endif // NOT_IMPLEMENTED_EXCEPTION_HPP
