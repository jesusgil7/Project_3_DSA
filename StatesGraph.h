#ifndef FINALPROJECT_DSA_STATESGRAPH_H
#define FINALPROJECT_DSA_STATESGRAPH_H

#include <iostream>
#include <vector>
#include <map>

class StatesGraph
{
private:

    struct Node
    {
        std::string name;
        std::vector<Node> subNodes; //Head -> States -> Counties -> Year -> Population & Deaths

        float population;
        float numDeaths;
        float deathRate;

        std::map<std::string, Node> countiesMap;

    };

    bool exit = false;
    std::map<std::string, Node> statesMap;

public:

    //Create a graph of all 50 US states with adjacent states having connections.
    StatesGraph(std::vector<std::tuple<std::string>>& dataStream);

    //Recursively traverse through
    void traverseState();

    //Print every cancer incident for the current US state.
    void printState();

    //Iterate through the graph and print every cancer incidence by US state.
    void printAll();

    //Graph destructor.
    ~StatesGraph();

};
#endif //FINALPROJECT_DSA_STATESGRAPH_H
