#ifndef FINALPROJECT_DSA_STATESGRAPH_H
#define FINALPROJECT_DSA_STATESGRAPH_H

#include <iostream>
#include <fstream>
#include <tuple>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <utility>


using namespace std;

class StatesGraph
{
private:

    struct Node
    {
        string name;
        vector<Node*> subNodes; //Head -> States -> Counties -> Year -> Population & Deaths
        vector<Node*> adjacentNodes; //State points to other states, county points to other counties within state.
        string population;
        string numDeaths;
        string numYear;
        map<string, vector<pair<string, Node*>>> countiesMap;
        int nodeID; //Each node gets a unique ID

    };

    bool exit = false;
    map<string, Node*> statesMap;

    Node* graphHead = nullptr;
    Node* graphCurrent = nullptr;

    int numNodes = 0;

public:

    //Create a graph of all 50 US states with states having connections to one another and counties within each state having connections.
    StatesGraph(vector<tuple<string, string, string, string,string>>& dataStream);

    //Recursively traverse through
    void traverseGraph(int level);

    //Print every county's data for the current US state.
    void printState(Node*);

    //Iterate through the graph and print every county's data by US state.
    void printAll();

    //Connect all 50 states to show that they are the same type of entity.
    void connectStates();

    //Connect counties within each state to show that they are related.
    void connectCounties(map<string, vector<pair<string, Node*>>>& allCounties);

    //Print graph data.
    void findState();
    void findCounty();
    void findYear();

    //Graph destructor.
    //~StatesGraph();

};
#endif //FINALPROJECT_DSA_STATESGRAPH_H
