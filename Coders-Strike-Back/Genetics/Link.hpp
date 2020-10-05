#ifndef Link_hpp
#define Link_hpp

#include <vector>

#include "Gene.hpp"
#include "Node.hpp"

class Link : public Gene {
public:
    Link();
    Link(bool, float);
    Link(bool, float, Node*, Node*);

    std::vector<Node*> nodes;

private:
    void init();
};



#endif /* Link_hpp */


