#pragma once
#include <vector>


typedef std::vector<double> Layer;

class NetBot
{
    public:
        NetBot();
        NetBot(std::vector<unsigned int> topology);
        void feedForward(std::vector<double> data);
        static NetBot mutate(NetBot n1,NetBot n2);
        static NetBot mutate(NetBot n1);
        void print();
        static NetBot save(char* fileName){}
        static NetBot load(char* fileName){} 
    public:
        double fitness;
        std::vector<Layer> neurons;
        std::vector<Layer> weights;
        
};