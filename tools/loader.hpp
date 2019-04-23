#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>

class loader
{
private:
    loader();
public:
    static loader instance;
    std::string get(std::string name);
};

#endif // LOADER_HPP
