#include "DataSets.h"

/// Function to read the files
vector<DataSets::TupleCancerData> DataSets::readData(string& filename)
{
    /// Vector of tuples to store the data
    vector<TupleCancerData> data;

    ifstream file(filename);
    string line;
    string word;

    getline(file, line);

    while(getline(file, line))
    {
        stringstream ss(line);

        /// Data Parameters
        string county;
        string state;
        string StateCounty;
        string deaths;
        string population;

        getline(ss, word, ',');
        getline(ss, word, ',');
        county = word;

        getline(ss,word,',');
        getline(ss,word,',');
        state = word;

        int commaPos = StateCounty.find_last_of(",");
        if (commaPos != string::npos)
        {
            state = StateCounty.substr(commaPos + 2);
        }

        /// Deleting quotes after string
        if(!state.empty() && state.back() == '"')
        {
            state.pop_back();
        }

        for(int i = 4; i < 11; i++)
        {
            getline(ss,word,',');
        }
        deaths = word;

        for(int i = 10; i < 14; i++)
        {
            getline(ss, word, ',');
        }
        population = word;

        /// Store the data in the vector
        data.emplace_back(county, state, deaths, population);
    }

    file.close();
    return data;
}

/// Function to Print Data
void DataSets::printData(vector<TupleCancerData>& data,string &filename)
{

    string year;
    string year2009 = "2009";
    string year2010 = "2010";
    string year2012 = "2012";
    string year2013 = "2013";

    string input;
    getline(cin, input);

    /// Delete whitespaces
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

    /// Allow user to use lower case
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    for(auto entry : data)
    {
        /// State
        string state = get<1>(entry);
        state.erase(remove_if(state.begin(), state.end(), ::isspace), state.end());
        transform(state.begin(), state.end(), state.begin(), ::tolower);

        /// County
        string county = get<0>(entry);
        county.erase(remove_if(county.begin(), county.end(), ::isspace), input.end());
        transform(county.begin(), county.end(), county.begin(), ::tolower);

        /// If User search for State
        if(input == state)
        {
            cout<<"County: " << get<0>(entry) << endl;
            cout<<"Deaths: " << get<2>(entry) << endl;
            cout<< "Population: " << get<3>(entry) << endl;
            cout<< "---------------------------------" << endl;
        }

            /// If User search for County
        else if(input == county)
        {

            cout<<"State: " << get<1>(entry) << endl;
            cout<<"Deaths: " << get<2>(entry) << endl;
            cout<< "Population: " << get<3>(entry) << endl;
            cout<< "---------------------------------" << endl;
        }
    }
}

/// Function to construct filepath
string DataSets::FilePath(string& direcotory, string& fileExtension) {
    cout << "Enter the dataset name (e.g., 'dataSet2009'): ";
    string datasetName;
    getline(cin, datasetName);  // Get user input
    return direcotory + datasetName + fileExtension;  // Construct the full file path
}

