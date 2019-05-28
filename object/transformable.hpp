#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

class rotatable
{
public:
    virtual ~rotatable() {}
    virtual void rotate() = 0;
};

class movable
{
public:
    virtual ~movable() {}
    virtual void move() = 0;
};

class scalable
{
public:
    virtual ~scalable() {}
    virtual void scale() = 0;
};

class transformable: public rotatable, public movable, public scalable
{
public:
    virtual ~transformable() {}
};

#endif // TRANSFORMABLE_HPP
