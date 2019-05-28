#ifndef BLOCKABLE_HPP
#define BLOCKABLE_HPP

class ray;
class intersection;

class blockable
{
public:
    virtual ~blockable() {}
    virtual intersection intersect(ray &in) const = 0;
};

#endif // BLOCKABLE_HPP
