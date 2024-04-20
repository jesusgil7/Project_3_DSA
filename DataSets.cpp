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
        string year;

        /// County
        getline(ss, word, ',');
        getline(ss, word, ',');
        county = word;

        /// State
        getline(ss,word,',');
        getline(ss,word,',');
        state = word;

        /// Deleting quotes after string
        if(!state.empty() && state.back() == '"')
        {
            state.pop_back();
        }

        /// Deaths
        for(int i = 4; i < 11; i++)
        {
            getline(ss,word,',');
        }
        deaths = word;

        /// Population
        for(int i = 11; i < 15; i++)
        {
            getline(ss, word, ',');
        }
        population = word;

        /// Year
        for(int i = 0; i < 19; i++)
        {
            getline(ss, word, ',');
        }
        year = word;
        year.erase(remove(year.begin(), year.end(), '\r'), year.end());

        /// Store the data in the vector
        data.emplace_back(make_tuple(county, state, deaths, population, year));
    }

    file.close();
    return data;
}

/// Function to Print Data
void DataSets::printData(vector<TupleCancerData>& data)
{
    /// Input Options
    string input3;
    cout<<"1) Search by State (Enter 1)" << endl;
    cout<<"2) Search by County (Enter 2)" << endl;
    cout<<"3) Search by year (Enter 3)" << endl;
    getline(cin,input3);

    /// If option 1 is selected
    if(input3 == "1")
    {
        cout<<"Enter State: " << endl;
        string input2;
        getline(cin, input2);

        /// Delete whitespaces
        input2.erase(remove_if(input2.begin(), input2.end(), ::isspace), input2.end());

        /// Allow user to use lower case
        transform(input2.begin(), input2.end(), input2.begin(), ::tolower);

        for(auto entry : data)
        {
            /// State
            string state = get<1>(entry);
            /// Erase whitespaces
            state.erase(remove_if(state.begin(), state.end(), ::isspace), state.end());
            /// Allow lowercase
            transform(state.begin(), state.end(), state.begin(), ::tolower);

            /// If User search for State
            if(input2 == state)
            {
                cout<<"County: " <<get<0>(entry) << endl;
                cout<<"State: " << get<1>(entry) << endl;
                cout<<"Deaths: " << get<2>(entry) << endl;
                cout<< "Population: " << get<3>(entry) << endl;
                cout<< "Year: " << get<4>(entry) << endl;
                cout<< "---------------------------------" << endl;
            }
        }
    }

    /// If option 2 is selected
    if(input3 == "2")
    {
        cout<< "Enter County: " << endl;
        string input;
        getline(cin, input);

        cout<<"Enter State: " << endl;
        string input2;
        getline(cin, input2);

        /// Delete whitespaces
        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

        /// Allow user to use lower case
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        /// Delete whitespaces
        input2.erase(remove_if(input2.begin(), input2.end(), ::isspace), input2.end());

        /// Allow user to use lower case
        transform(input2.begin(), input2.end(), input2.begin(), ::tolower);

        for(auto entry : data)
        {

            /// State
            string state = get<1>(entry);
            /// Erase whitespaces
            state.erase(remove_if(state.begin(), state.end(), ::isspace), state.end());
            /// Allow lowercase
            transform(state.begin(), state.end(), state.begin(), ::tolower);

            /// County
            string county = get<0>(entry);
            /// Erase whitespaces
            county.erase(remove_if(county.begin(), county.end(), ::isspace), input.end());
            /// Allow lowercase
            transform(county.begin(), county.end(), county.begin(), ::tolower);

            /// If User search for County
            if(input2 == state && input == county)
            {
                cout<<"County: " <<get<0>(entry) << endl;
                cout<<"State: " << get<1>(entry) << endl;
                cout<<"Deaths: " << get<2>(entry) << endl;
                cout<< "Population: " << get<3>(entry) << endl;
                cout<< "Year: " << get<4>(entry) << endl;
                cout<< "---------------------------------" << endl;
            }
        }
    }

    /// If option 3 is selected
    if(input3 == "3")
    {
        cout<<"Enter Year: " << endl;
        string input4;
        getline(cin, input4);

        /// Delete whitespaces
        input4.erase(remove_if(input4.begin(), input4.end(), ::isspace), input4.end());

        /// Allow user to use lower case
        transform(input4.begin(), input4.end(), input4.begin(), ::tolower);

        for(auto entry : data)
        {
            /// Year
            string year = get<4>(entry);
            /// Erase whitespaces
            year.erase(remove_if(year.begin(), year.end(), ::isspace), year.end());
            /// Allow lowercase
            transform(year.begin(), year.end(), year.begin(), ::tolower);

            /// If User search for Year
            if(input4 == year)
            {
                cout<<"County: " <<get<0>(entry) << endl;
                cout<<"State: " << get<1>(entry) << endl;
                cout<<"Deaths: " << get<2>(entry) << endl;
                cout<< "Population: " << get<3>(entry) << endl;
                cout<< "Year: " << get<4>(entry) << endl;
                cout<< "---------------------------------" << endl;
            }
        }
    }
}

