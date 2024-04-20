#include "DataSets.h"

using namespace std;

int main() {

    DataSets datasets;
    /// Constants for the base directory and file extension
    string baseDirectory = "/Users/juanpostiglione/CLionProjects/project3/";
    vector<string> filenames = {"dataSet2009.csv", "dataSet2010.csv", "dataSet2012.csv", "dataSet2013.csv"};
    vector<DataSets::TupleCancerData> allData;

    for(auto files : filenames)
    {
        /// Get the full file path using the base directory and file extension
        string filename = baseDirectory + files;

        /// Read and process the data from the specified file
        vector<DataSets::TupleCancerData> data = datasets.readData(filename);
        allData.insert(allData.end(), data.begin(), data.end());
    }
    datasets.printData(allData);

    return 0;
}

