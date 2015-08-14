#ifndef BUW_NODE_HPP
#define BUW_NODE_HPP
#include "shape.hpp"

struct Node {
        Node(std::shared_ptr<const Node> left, std::shared_ptr<Shape> shape,
                std::shared_ptr<const Node> right):
                        left_{left},
                        shape_{shape},
                        right_{right}
                        {}

        std::shared_ptr<const Node> left_;
        std::shared_ptr<Shape> shape_;
        std::shared_ptr<const Node> right_;
};

#endif // BUW_NODE_HPP