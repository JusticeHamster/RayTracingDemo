#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

class rotatable
{
protected:
    virtual ~rotatable() {}
public:
    virtual void rotate() = 0;
};

class movable
{
protected:
    virtual ~movable() {}
public:
    virtual void move() = 0;
};

class scalable
{
protected:
    virtual ~scalable() {}
public:
    virtual void scale() = 0;
};

class transformable: public rotatable, public movable, public scalable
{
protected:
    virtual ~transformable() {}
};

#endif // TRANSFORMABLE_HPP
