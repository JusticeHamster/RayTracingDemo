#ifndef HELLOABLE_HPP
#define HELLOABLE_HPP

#include <QDebug>

class helloable
{
public:
    virtual ~helloable();
    virtual void hello() const = 0;
};

#endif // HELLOABLE_HPP
