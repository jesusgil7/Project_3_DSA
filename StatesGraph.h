#ifndef FINALPROJECT_DSA_STATESGRAPH_H
#define FINALPROJECT_DSA_STATESGRAPH_H

#include <iostream>
#include <fstream>
#include <tuple>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class StatesGraph
{
    private:

        struct Node
        {
            string name;
            vector<Node*> subNodes; //Head -> States -> Counties -> Year -> Population & Deaths

            string population = "";
            string numDeaths = "";

            map<string, Node*> countiesMap;

        };

        bool exit = false;
        map<string, Node*> statesMap;
        int year;

        Node* graphHead = nullptr;
        Node* graphCurrent = nullptr;

    public:

        //Create a graph of all 50 US states with adjacent states having connections.
        StatesGraph(vector<tuple<string, string, string, string>>& dataStream);

        //Recursively traverse through 
        void traverseGraph(int level);

        //Print every county's data for the current US state.
        void printState(Node*);

        //Iterate through the graph and print every county's data by US state.
        void printAll();

        //Graph destructor.
        ~StatesGraph();

};
#endif //FINALPROJECT_DSA_STATESGRAPH_H
