#include "DataSets.h"

using namespace std;

int main() {

    DataSets datasets;
    /// Constants for the base directory and file extension
    string baseDirectory = "path/to/the/file"; // Here adjust the path for your file
    string fileExtension = ".csv";

    /// Get the full file path using the base directory and file extension
    string filename = datasets.FilePath(baseDirectory, fileExtension);

    /// Read and process the data from the specified file
    vector<DataSets::TupleCancerData> data = datasets.readData(filename);
    datasets.printData(data, filename);

    return 0;
}