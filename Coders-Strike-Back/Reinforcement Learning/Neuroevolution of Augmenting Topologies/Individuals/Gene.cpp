#include "Gene.hpp"

Node::Node() {
    inputs.clear();
    outputs.clear();
}

Node::Node(char t, int i) : Node() {
    type = t;
    id = i;
}

Link::Link() {
    in = nullptr;
    out = nullptr;
}
