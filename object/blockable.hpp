#ifndef BLOCKABLE_HPP
#define BLOCKABLE_HPP

class ray;

class blockable
{
private:
    bool block = true;
protected:
    virtual float intersect(const ray &in) const = 0;
public:
    virtual ~blockable();
    float ray_intersect(const ray &in) const;
    void set_blockable(bool block);
    bool is_block() const;
};

#endif // BLOCKABLE_HPP
