#include "AdjacencyMatrix.h"
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <chrono>

AdjacencyMatrix::AdjacencyMatrix(int numNodes) 
{
    for(int i = 0; i < numNodes; i++)
    {
        vector<int> weights;
        for(int j = 0; j < numNodes; j++)
        {
            toNodes.push_back(0);
        }
        adjMatrix.push_back(weights);
    }
}

//Recursively pass through the graph and update the adjacency matrix
void AdjacencyMatrix::fillMatrix(Node* head)
{
    for(int i = 0; i < head->subNodes.size(); i++)
    {
        adjMatrix[head->nodeID][head->subNodes[i]->nodeID] = 1; // Graph[from][to] = 1 if there is a path and 0 otherwise.
        fillMatrix(head->subNodes[i]); //Recursively visit each other node.
    }
    for(int j = 0; j < head->adjacentNodes.size(); j++)
    {
        adjMatrix[head->nodeID][head->adjacentNodes[j]->nodeID] = 1;
    }
}

//Return the adjacency matrix.
vector<vector<int>> AdjacencyMatrix::getMatrix()
{
    return adjMatrix;
}

//Print the adjacency matrix
void AdjacencyMatrix::printMatrix()
{
    for(int i = 0; i < adjMatrix.size(); i++)
    {
        for(int j = 0; j < adjMatrix.size(); j++)
        {
            cout << adjMatrix[i][j];   // Print each value of the adjacency matrix with same [to] rows on the same line.

            if(j != adjMatrix.size() - 1)
            {
                cout << ', '; //Separator other than a space since the entire row won't be on the same line of the terminal when printed.
            }
        }
        cout << ';' << endl;  //Separator used to make clear where a new line happens.
    }
}
   