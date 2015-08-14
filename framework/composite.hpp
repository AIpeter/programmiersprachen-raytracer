#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP
#include "sphere.hpp"
#include "box.hpp"
#include <vector>

class Composite : public Shape
{
        struct Node;
        explicit Composite(std::shared_ptr<const Node> const& node);
public:
        Composite();
        Composite(std::string const& name, Composite const& left,
                std::shared_ptr<Shape> shape, Composite const& right);
        Composite(std::initializer_list<std::shared_ptr<Shape>> list);
        std::shared_ptr<Shape> root() const;
        Composite left() const;
        Composite right() const;
        Composite insert(std::shared_ptr<Shape> shape) const;
        bool isEmpty() const;
        float area() const;
        float volume() const;
        bool intersect(Ray const& r, float & t);
        float closer_z() const;

        std::ostream& print(std::ostream& os) const;
private:
        std::shared_ptr<const Node> root_;
};

struct Node {
        Node(std::shared_ptr<const Node> left, Shape* shape,
                std::shared_ptr<const Node> right):
                        left_{left},
                        shape_{shape},
                        right_{right}
                        {}

        std::shared_ptr<const Node> left_;
        std::shared_ptr<Shape> shape_;
        std::shared_ptr<const Node> right_;
};

std::ostream& operator<<(std::ostream& os, Composite const& c);

#endif // BUW_COMPOSITE_HPP