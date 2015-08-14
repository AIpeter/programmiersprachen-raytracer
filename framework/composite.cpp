/*#include "composite.hpp"

Composite::Composite(std::shared_ptr<const Node> const& node):
        Shape(),
        root_{node}
        {}

Composite::Composite():
        Shape(),
        root_{NULL}
        {}

Composite::Composite(std::string const& name, Composite const& left,
                        std::shared_ptr<Shape> shape, Composite const& right):
        Shape(name),
        root_{std::make_shared<const Node>(left.root_, shape, right.root_)}
        {}

Composite::Composite(std::initializer_list<std::shared_ptr<Shape>> list):
        Shape(),
        root_{NULL}
        {
        Composite c;
        for (auto i : list) {
                c = c.insert(i);
        }
        root_ = c.root_;
}

bool Composite::isEmpty() const {
        return !root_;
}

std::shared_ptr<const Node> Composite::root() const {
        return root_;
}

Composite Composite::left() const {
        return Composite(root_->left_);
}

Composite Composite::right() const {
        return Composite(root_->right_);
}

Composite Composite::insert(std::shared_ptr<Shape> shape) const {
        if (isEmpty()) {
                return Composite(name_, Composite(), shape, Composite());
        }
        if (left().isEmpty()) {
                return Composite(name_, left().insert(shape), root()->shape_, right());
        }
        else if (right().isEmpty()) {
                return Composite(name_, left(), root()->shape_, right().insert(shape));
        }
        else {
                return Composite(name_,left().insert(shape), root()->shape_, right());       
        }
}
*/
/* virtual */ /*float Composite::area() const { // Überlappung?!
        float area = root()->shape_->area();
        auto n = root();
        if (n) {
                area += left().volume();
                area += right().volume();
        }
        return area;
}
*/
/* virtual */ /*float Composite::volume() const { // Überlappung?!
        float volume = root()->shape_->volume();
        auto n = root();
        if (n) {
                volume += left().volume();
                volume += right().volume();
        }
        return volume;
}*/

<<<<<<< HEAD
/* virtual */ bool Composite::intersect(Ray const& r, float & t) {
=======
/* virtual */ /* bool Composite::intersect(Ray const& r, float & t) const {
>>>>>>> bc43b1790431e0a25f70c351ebd14f63b6b3a0e9
        bool intersect = root()->shape_->intersect(r, t);
        if (intersect == true) {
                return intersect;
        }
        else {
                auto n = root();
                if (n) {
                        if (left().intersect(r, t)) {
                                return true;
                        }
                        else if (right().intersect(r, t)) {
                                return true;
                        }
                        else {
                                return false;
                        }
                }
                else {
                        return false;
                }
        }
}*/

/* virtual */ /*float Composite::closer_z() const {
        float z = root()->shape_->closer_z();
        auto n = root();
        if (n) {
                if (left().closer_z() < z) {
                        z = left().closer_z();
                }
                else if (right().closer_z() < z) {
                        z = right().closer_z();
                }
        }
        return z;
}*/

<<<<<<< HEAD
/* virtual */ std::ostream& Composite::print(std::ostream& os) const {
=======
/* virtual */ /*std::ostream& Composite::print(std::ostream& os) {
>>>>>>> bc43b1790431e0a25f70c351ebd14f63b6b3a0e9
        root()->shape_->print(os);
        auto n = root();
        if (n) {
                left().print(os);
                right().print(os);
        }
        return os;
}
/*
std::ostream& operator<<(std::ostream& os, Composite const& c) {
        c.print(os);
        return os;
<<<<<<< HEAD
} */
=======
}*/
>>>>>>> bc43b1790431e0a25f70c351ebd14f63b6b3a0e9
