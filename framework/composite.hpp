#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP
#include "node.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include <vector>
#include <memory>

class Composite : public Shape
{
        explicit Composite(std::shared_ptr<const Node> const& node);
public:
        Composite();
        Composite(std::string const& name, Composite const& left,
                std::shared_ptr<Shape> shape, Composite const& right);
        Composite(std::initializer_list<std::shared_ptr<Shape>> list);
        std::shared_ptr<const Node> root() const;
        Composite left() const;
        Composite right() const;
        Composite insert(std::shared_ptr<Shape> shape) const;
        bool isEmpty() const;
        float area() const;
        float volume() const;
        bool intersect(Ray const& r, float & t);
        float closer_z() const;
        std::ostream& print(std::ostream& os) const;

        Color getLight(float & d, Ray const& r, Light const& light, float shade) const;

        void translate(glm::vec3 const& direction);
        void scale(glm::vec3 const& scale);

private:
        std::shared_ptr<const Node> root_;
};

// std::ostream& operator<<(std::ostream& os, Composite const& c);

#endif // BUW_COMPOSITE_HPP