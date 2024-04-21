#include "DataSets.h"
#include "StatesGraph.h"
#include "AdjacencyMatrix.h"

using namespace std;

int main() {

    DataSets datasets;
    /// Constants for the base directory and file extension.
    string baseDirectory = "data/"; /// Data path directory.
    vector<string> filenames = {"dataSet2008.csv" , "dataSet2009.csv", "dataSet2010.csv", "dataSet2011.csv", "dataSet2012.csv", "dataSet2013.csv"};
    vector<DataSets::TupleCancerData> allData;

    for(auto files : filenames)
    {
        /// Get the full file path using the base directory and file extension
        string filename = baseDirectory + files;

        /// Read and process the data from the specified file
        vector<DataSets::TupleCancerData> data = datasets.readData(filename);
        allData.insert(allData.end(), data.begin(), data.end());
    }

    /// Create the graph and get necessary values
    StatesGraph graph(allData);
    int nodeCount = graph.getNodeCount;
    Node* graphHead = graph.getGraphHead;

    /// Call adjacency matrix
    AdjacencyMatrix newMatrix(nodeCount);
    newMatrix.fillMatrix(graphHead);

    while(true){
        string type;
        cout << "How do you want to read the data? Graph or Directly" <<endl;
        getline(cin,type);

        if(type == "Graph") {
            string input;
            cout << "1) Search by State (Enter 1)" << endl;
            cout << "2) Search by County (Enter 2)" << endl;
            cout << "3) Search by Year (Enter 3)" << endl;
            cout << "3) Display Adjacency Matrix (Enter 4)" << endl;
            getline(cin, input);
            if (input == "1") {
                graph.findState();
            } else if (input == "2") {
                graph.findCounty();
            } else if (input == "3") {
                graph.findYear();
            } else if (input == "4") {
                newMatrix.printMatrix();
            } else {
                cout << "Invalid Option. Try Again" << endl;
            }
        }
        else if (type == "Directly"){
            datasets.printData(allData);
        }
    }






    return 0;
}

