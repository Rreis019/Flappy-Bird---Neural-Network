#include "neuralNetwork.h"
#include <algorithm>
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>

#define MIN_WEIGHT -1
#define MAX_WEIGHT 1

NetBot::NetBot(){}
NetBot::NetBot(std::vector<unsigned int> topology){
    assert(topology.size() > 1);
    neurons.resize(topology.size());
    weights.resize(topology.size() - 1);

    for(unsigned int i = 0; i < topology.size(); i++){
        assert(topology[i] > 0);

        //the output dont have bias
        if(i == topology.size()-1)
        {
            neurons[i].resize(topology[i]); 
        }else{
            neurons[i].resize(topology[i] + 1); // + 1 = is bias(constant variable)
            neurons[i][neurons[i].size( )-1] = 1;
        }
    }

    for(unsigned int i = 0; i < topology.size()-1; i++){
        weights[i].resize(neurons[i].size() * topology[i+1]); 
        for(int j = 0 ; j < weights[i].size();j++){
            weights[i][j] = RAND_DOUBLE(MIN_WEIGHT,MAX_WEIGHT);
        }
    }
}


void NetBot::feedForward(std::vector<double> data)
{
    assert(data.size() == neurons[0].size()-1);//-1 because have bias which is not data

    auto minMax = std::minmax_element(data.begin(),data.end());

    //printf("v %lf %lf\n",*minMax.first,*minMax.second);
    //printf("normalize %lf\n", NORMALIZE_VALUE(data[0],0,1000));

    for(int i = 0;i < data.size();i++){
        neurons[0][i] = data[i];
    }


    for(int i = 1; i < neurons.size() ; i++) //for each layer
    {
        //neuronsLayerSize is size of  without bias
        int neuronsLayerSize = i == neurons.size()-1 ? neurons[i].size():neurons[i].size()-1;
        for(int nIndex = 0;nIndex < neuronsLayerSize;nIndex++)
        {
            double sum = 0;
            int startIndex = nIndex*neurons[i-1].size(); 
            int endIndex = startIndex + neurons[i-1].size(); 
            for(int j = startIndex ; j < endIndex;j++)
            {
                sum += weights[i-1][j] * neurons[i-1][j-startIndex];
                //printf("sum[%d] += %lf * %lf;\n",i, weights[i-1][j] ,neurons[i-1][j-startIndex]);
                //printf("sum += weights[%d][%d] * neurons[%d][%d];\n",i-1,j,i-1,j-startIndex);
            }
            //printf("sum = %lf\n\n",sum);
            neurons[i][nIndex] = SIGMOID(sum);
            //printf("\n");
            //printf("neurons[%d].size() = %d\n",i,neurons[i].size());
        }
    }

    //activate function
    for(int i = 0; i < neurons[neurons.size()-1].size();i++){
        int x = neurons[neurons.size()-1][i] ;
        neurons[neurons.size()-1][i] = sin(neurons[neurons.size()-1][i]);
    }

}

NetBot NetBot::mutate(NetBot n1,NetBot n2)
{
    assert(n1.neurons.size() == n2.neurons.size());
    
    std::vector<unsigned int> topology;
    topology.resize(n1.neurons.size());
    for(int i = 0 ; i < n1.neurons.size();i++){ 
        assert(n1.neurons[i].size() == n2.neurons[i].size());
        topology[i] = n1.neurons[i].size();

        if(i != n1.neurons.size()-1){
            topology[i]--;
        }
    }
    NetBot children = NetBot(topology);

    //misture weights
    for(int i = 0; i < n2.weights.size();i++){
        for(int j = 0 ; j < n2.weights[i].size();j++)
        {
            int randN = RAND_INT(0,100);
            if(randN > 60){
                children.weights[i][j] = n2.weights[i][j];
            }else{
                float newWeight =  RAND_DOUBLE(MIN_WEIGHT,MAX_WEIGHT);
              
                children.weights[i][j] = (randN < 30) ? newWeight : n1.weights[i][j];
            }
        }
    }



    return children;
} 

NetBot NetBot::mutate(NetBot n1)
{
    std::vector<unsigned int> topology;
    topology.resize(n1.neurons.size());
    for(int i = 0 ; i < n1.neurons.size();i++){ 
        topology[i] = n1.neurons[i].size();
        if(i != n1.neurons.size()-1){ topology[i]--;}
    }
    NetBot children = NetBot(topology);

    //misture weights
    for(int i = 0; i < n1.weights.size();i++){
        for(int j = 0 ; j < n1.weights[i].size();j++)
        {
            double newWeight = 0; 
            newWeight = n1.weights[i][j] + RAND_DOUBLE(-0.2f,0.2f);
            int randN = RAND_INT(0,100);
            if(randN > 60){
                 //printf("%lf -> %lf\n", children.weights[i][j],newWeight);
                 children.weights[i][j] = newWeight;
            }else{
                children.weights[i][j] = n1.weights[i][j];
            }
        }
    }



    return children;
}


void NetBot::save(char* fileName)
{
    FILE* fp = fopen(fileName,"w");

    for(int i  = 0;i < weights.size();i++)
    {
        for(int j = 0;j < weights[i].size();j++)
        {
            fprintf(fp,"%lf ",weights[i][j]);
        }
    }
    fclose(fp);
}

bool NetBot::load(char* fileName)
{
    FILE* fp = fopen(fileName,"r");
    if(fp == NULL){return false;}

    for(int i  = 0;i < weights.size();i++)
    {
        for(int j = 0;j < weights[i].size();j++)
        {
            fscanf(fp,"%lf ",&weights[i][j]);
        }
    }
    fclose(fp);
    return true;
}

void NetBot::print()
{
    printf("Neurons:\n");
    for(int i  = 0;i < neurons.size();i++)
    {
        for(int j = 0;j < neurons[i].size();j++)
        {
            //printf("neural.neurons[%d][%d] %f\n",i,j,neural.neurons[i][j]);
            printf("%f\n",neurons[i][j]);
        }
        printf("\n");
    }

    printf("Weights:\n");
    for(int i  = 0;i < weights.size();i++)
    {
        for(int j = 0;j < weights[i].size();j++)
        {
            printf("%f\n",weights[i][j]);
        }
        printf("\n");
    }
}

