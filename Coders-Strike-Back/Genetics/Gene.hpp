#ifndef Gene_hpp
#define Gene_hpp

class Gene {
public:
    Gene();
    Gene(bool, float);

    bool activated;
    float parameter;

};

#endif /* Gene_hpp */
