#ifndef BLOCKABLE_HPP
#define BLOCKABLE_HPP

class ray;

class blockable
{
private:
    bool block = true;
protected:
    virtual float intersect(ray &in) const = 0;
public:
    virtual ~blockable();
    float ray_intersect(ray &in) const;
    void set_blockable(bool block);
};

#endif // BLOCKABLE_HPP
