#ifndef BLOCKABLE_HPP
#define BLOCKABLE_HPP

class ray;

class blockable
{
public:
    virtual ~blockable();
    virtual float intersect(ray &in) const = 0;
};

#endif // BLOCKABLE_HPP
