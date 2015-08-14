/*#include "composite.hpp"

Composite::Composite(std::shared_ptr<const Node> const& node):
        root_{node}
        {}

Composite::Composite():
        Shape(name)
        {}

Composite::Composite(std::string const& name, Composite const& left,
                        std::shared_ptr<Shape> shape, Composite const& right):
        root_{std::make_shared<const Node>(left.root_, shape, right.root_)}
        {}

Composite::Composite(std::initializer_list<std::shared_ptr<Shape>> list) {
        Composite c;
        for (auto i : list) {
                c = c.insert(i);
        }
        root_ = c.root_;
}

bool Composite::isEmpty() const {
        return !root_;
}

std::shared_ptr<Shape> Composite::root() const {
        return root_->shape_;
}

Composite Composite::left() const {
        return Composite(root_->left_);
}

Composite Composite::right() const {
        return Composite(root_->right_);
}

Composite Composite::insert(std::shared_ptr<Shape> shape) const {
        if (isEmpty()) {
                return Composite(Composite(), shape, Composite());
        }
        if (left().isEmpty()) {
                return Composite(left().insert(shape), root(), right());
        }
        else if (right().isEmpty()) {
                return Composite(left(), root(), right().insert(shape));
        }
        else {
                return Composite(left().insert(shape), root(), right());       
        }
}
*/
/* virtual */ /*float Composite::area() const { // Überlappung?!
        float area = root()->shape_->area();
        auto n = root();
        if (n) {
                area += n->left()->volume();
                area += n->right()->volume();
        }
        return area;
}
*/
/* virtual */ /*float Composite::volume() const { // Überlappung?!
        float volume = root()->shape_->volume();
        auto n = root();
        if (n) {
                volume += n->left()->volume();
                volume += n->right()->volume();
        }
        return volume;
}*/

/* virtual */ /* bool Composite::intersect(Ray const& r, float & t) const {
        bool intersect = root()->shape_->intersect(r, t);
        if (intersect == true) {
                return intersect;
        }
        auto n = root();
        if (n) {
                if (n->left()->intersect(r, t)) {
                        return true;
                }
                else if (n->right()->intersect(r, t)) {
                        return true;
                }
                else {
                        return false
                }
        }
}*/

/* virtual */ /*float Composite::closer_z() const {
        float z = root()->shape_->closer_z();
        auto n = root();
        if (n) {
                if (n->left()->closer_z() < z) {
                        z = n->left()->closer_z();
                }
                else if (n->right()->closer_z() < z) {
                        z = n->right()->closer_z();
                }
        }
        return z;
}*/

/* virtual */ /*std::ostream& Composite::print(std::ostream& os) {
        root()->shape_->print(os);
        auto n = root();
        if (n) {
                n->left()->print(os);
                n->right()->print(os);
        }
        return os;
}

std::ostream& operator<<(std::ostream& os, Composite const& c) {
        c.print(os);
        return os;
}*/
