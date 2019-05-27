#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

class rotatable
{
public:
    virtual void rotate() = 0;
};

class movable
{
public:
    virtual void move() = 0;
};

class scalable
{
public:
    virtual void scale() = 0;
};

class transformable: public rotatable, public movable, public scalable
{

};

#endif // TRANSFORMABLE_HPP
