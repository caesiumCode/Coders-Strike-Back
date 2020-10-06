#include "NEAT.hpp"

NEAT::NEAT() {
    generation = 0;
}

NEAT::NEAT(int s) : NEAT() {
    population = Population(s);
}

void NEAT::evolve(int nb) {
    population.play(nb);
    population.speciation();
    population.selection();
    population.mating();
    population.mutation();
}
