#include "Link.hpp"

Link::Link() : Gene() {
	init();
}

Link::Link(bool activation, float parameter) : Gene(activation, parameter) {
	init();
}

Link::Link(bool activation, float parameter, Node* node1, Node* node2) : Gene(activation, parameter) {
	init();
	nodes.push_back(node1);
	nodes.push_back(node2);
}

void Link::init() {
	nodes.clear();
}