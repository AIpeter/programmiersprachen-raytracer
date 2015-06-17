#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

class Shape
{
  public:
    virtual float area() const = 0; // pure virtual
    virtual float volume() const = 0; // pure virual

};

#endif // BUW_SHAPE_HPP