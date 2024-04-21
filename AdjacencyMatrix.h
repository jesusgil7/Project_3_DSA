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
        vector<vector<int>> adjMatrix;


    public:

        AdjacencyMatrix(int numNodes);  // Construct empty adjacency matrix (all values are 0) of size = numNodes.

        void fillMatrix(Node* head);   //Recursively pass through the graph and update the adjacency matrix

        vector<vector<int>> getMatrix();   //Return the adjacency matrix

        void printMatrix();  //Print the adjacency matrix


};
#endif //FINALPROJECT_DSA_STATESGRAPH_H
