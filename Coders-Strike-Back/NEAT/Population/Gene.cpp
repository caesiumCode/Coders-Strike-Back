#include "Gene.hpp"

Node::Node() {
    inputs.clear();
    outputs.clear();
}

Node::Node(char t) : Node() {
    type = t;
}

Link::Link() {
    in = nullptr;
    out = nullptr;
}
