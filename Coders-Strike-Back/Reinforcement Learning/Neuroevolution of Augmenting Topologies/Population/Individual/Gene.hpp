#ifndef Gene_hpp
#define Gene_hpp

#include <vector>

class Node;
class Link;

class Node {
public:
    Node();
    Node(char, int);
    
    std::vector<Link*> inputs;
    std::vector<Link*> outputs;
    
    int id;
    char type; // I : input | O : output | H : hidden
};

class Link {
public:
    Link();
    
    Node* in;
    Node* out;
    
    float weight;
    bool enable;
    int innov;
};


#endif /* Gene_hpp */
