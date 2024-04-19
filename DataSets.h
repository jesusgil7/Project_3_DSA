
#ifndef FINALPROJECT_DSA_DATASETS_H
#define FINALPROJECT_DSA_DATASETS_H
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


    using TupleCancerData = tuple<string, string, string, string>;

    /// Function to read the files
    vector<TupleCancerData> readData(string& filename);

    /// Function to Print Data
    void printData(vector<TupleCancerData>& data,string &filename);

    /// Function to construct filepath
    string FilePath(string& direcotory, string& fileExtension);

};
#endif //FINALPROJECT_DSA_DATASETS_H
