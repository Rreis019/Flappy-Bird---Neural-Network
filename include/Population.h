#include "bird.h"
#include "neuralNetwork.h"

class Population
{
    public:
        Population();
        Population(int totalPopulation);
        void onUpdate();
        int currentGeneration = 0;
        std::vector<Bird> birds;
    private:
        void nextGen();
        int totalPopulation = 100;
        std::vector<NetBot> brains;
        int startTick = 0;
};

extern Population population;