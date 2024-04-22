#include <iostream>
#include <fstream>
#include <tuple>
#include <sstream>
#include <string>
#include <vector>
#pragma once

using namespace std;

class DataSets{
public:


    using TupleCancerData = tuple<string, string, string, string, string>;

    /// Function to read the files
    vector<TupleCancerData> readData(string& filename);

    /// Function to Print Data
    void printData(vector<TupleCancerData>& data);

    /// Function to construct filepath
    string FilePath(string& directory, string& fileExtension);

};

