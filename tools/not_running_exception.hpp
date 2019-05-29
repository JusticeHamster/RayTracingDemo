#ifndef NOT_RUNNING_EXCEPTION_HPP
#define NOT_RUNNING_EXCEPTION_HPP

#include <stdexcept>
#include <string>

class not_running_exception: public std::runtime_error
{
public:
    not_running_exception(std::string message);
};

#endif // NOT_RUNNING_EXCEPTION_HPP
