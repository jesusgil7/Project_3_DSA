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
#include "StatesGraph.h"


using namespace std;

class AdjacencyMatrix
{
    private:
        int adjMatrix[numNodes][numNodes];  // graph[from][to]


    public:

        AdjacencyMatrix(int numNodes);  // Construct empty adjacency matrix (all values are 0) of size = numNodes.

        void fillMatrix(Node* head);

        vector<vector<int>> adjMatrix 


};
#endif //FINALPROJECT_DSA_STATESGRAPH_H
