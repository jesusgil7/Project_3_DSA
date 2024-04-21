#include "StatesGraph.h"
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <chrono>

StatesGraph::StatesGraph(vector<tuple<string, string, string, string, string>>& dataStream) {
    Node* head = new Node; // Head node
    graphHead = head;

    numNodes++;
    head->nodeID = numNodes; //Give each new node its unique ID

    for (const auto& entry : dataStream) {
        string currentCounty = get<0>(entry);
        string currentState = get<1>(entry);
        string currentDeaths = get<2>(entry);
        string currentPop = get<3>(entry);
        string currentYear = get<4>(entry);

        // N/A if data does not exist for this field.
        if(currentDeaths.empty())
        {
            currentDeaths = "N/A";
        }
        if(currentPop.empty())
        {
            currentPop = "N/A";
        }

        // Check if the state exists, and add if not
        if (statesMap.find(currentState) == statesMap.end()) {
            Node* newState = new Node{name: currentState};
            head->subNodes.push_back(newState);
            statesMap[currentState] = newState;

            numNodes++;
            newState->nodeID = numNodes;
        }

        // Access state node
        Node* stateNode = statesMap[currentState];

        // Check for existing county and year
        bool found = false;
        for (auto& pair : stateNode->countiesMap[currentCounty]) {
            if (pair.first == currentYear) { // Year exists
                found = true;
                break;
            }
        }

        // If not found, add new county with year
        if (!found) {
            Node* newCounty = new Node{name: currentCounty, population: currentPop, numDeaths: currentDeaths, numYear: currentYear};
            stateNode->subNodes.push_back(newCounty);
            stateNode->countiesMap[currentCounty].emplace_back(currentYear, newCounty);

            numNodes++;
            newCounty->nodeID = numNodes;
        }
    }

    connectStates();

    ///   Call adjacency matrix
    //AdjacencyMatrix newMatrix(numNodes);
    //newMatrix.fillMatrix(graphHead);
}

/***
//Recursively traverse the graph. Initial call from main() should be: traverseGraph(0);
void StatesGraph::traverseGraph(int level)
{
    bool back = false;

    if(level == 0) //If current node is head.
    {
        graphCurrent = graphHead;

        while(!exit)
        {

            cout<< "Enter state name. Otherwise, enter \"exit\" to quit Explore." << endl;

            string input;
            getline(cin, input);

            //If inputted US state is in the graph, travel to that state.
            if(statesMap.find(input) != statesMap.end())
            {
                graphCurrent = statesMap[input];
                traverseGraph(level + 1);
            }
            else if(input == "exit")
            {
                exit = true;
            }


        }

        //Reset exit for next graph traversal.
        exit = false;
    }
    else if(level == 1) //If current node is a US state.
    {
        while(!back && !exit)
        {
            cout << "Enter county name. Otherwise, enter \"back\" to change state selection or \"exit\" to quit Explore." << endl;
            string input;
            getline(cin, input);

            //If inputted county is in the graph, travel to that county.
            if(graphCurrent->countiesMap.find(input) != graphCurrent->countiesMap.end())
            {
                graphCurrent = graphCurrent->countiesMap[input];
                traverseGraph(level + 1);
            }
            else if(input == "back")
            {
                back = true;
            }
            else if(input == "exit")
            {
                exit = true;
            }
        }
    }
    else if(level == 2)
    {

        while(!back && !exit)
        {
            cout << "Enter \"population\" to view this county's population or enter \"deaths\" to see the number of cancer deaths. Otherwise, enter \"back\" to change county selection or \"exit\" to quit Explore." << endl;

            string input;
            getline(cin, input);

            //If "population" or "deaths" was entered, print the corresponding data.
            //If "back" or "exit" was entered, perform the corresponding action.
            if(input == "population")
            {
                cout << "Population: " << graphCurrent->population << endl << endl;
            }
            else if(input == "deaths")
            {
                cout << "Deaths: " << graphCurrent->numDeaths << endl << endl;
            }
            else if(input == "back")
            {
                back = true;
            }
            else if(input == "exit")
            {
                exit = true;
            }
        }
    }
}
***/

//Print each county in the specified state in alphabetical order.
void StatesGraph::printState(Node* state)
{
    map<string, vector<pair<string, Node*>>>::iterator iter;

    for(iter = state->countiesMap.begin(); iter != state->countiesMap.end(); iter++)
    {
        cout << iter->first << endl;
        const auto& counties = iter->second;

        for (const auto& county : counties) {
            const std::string& year = county.first;  // Year as string
            const Node* node = county.second;  // Pointer to the Node structure

            std::cout << "\tYear: " << year << std::endl;
            std::cout << "\tPopulation: " << node->population << std::endl;
            std::cout << "\tDeaths: " << node->numDeaths << std::endl;
            std::cout << "\t---------------------------------" << std::endl;
        }
    }
}

//Prints every state on the graph in alphabetical order.
void StatesGraph::printAll()
{
    map<string, Node*>::iterator iter;
    for(iter = statesMap.begin(); iter != statesMap.end(); iter++)
    {
        cout << "State:" << iter->second->name << endl;
        printState(iter->second); //Print each county in the state in alphabetical order.
    }
}

//Connect all 50 states to show that they are the same type of entity.
void StatesGraph::connectStates()
{
    map<string, Node*>::iterator iter1;
    map<string, Node*>::iterator iter2;

    //Each state is connected to each other state.
    for(iter1 = statesMap.begin(); iter1 != statesMap.end(); iter1++)
    {
        for(iter2 = iter1 + 1; iter2 != statesMap.end(); iter2++)
        {
            iter1->second->adjacentNodes.push_back(iter2->second);
            iter2->second->adjacentNodes.push_back(iter1->second);
        }

        connectCounties(iter1->second->countiesMap);
    }
}

//Connect counties within each state to show that they are related. Nodes are only connected if they are from the same year.
void StatesGraph::connectCounties(map<string, vector<pair<string, Node*>>>& allCounties)
{
    map<string, Node*>::iterator iter1;
    map<string, Node*>::iterator iter2;

    vector<string> years{2009, 2010, 2012, 2013};
    string year = years[0];

    Node* currentNode = nullptr;

    for(int i = 0; i < 4; i++)
    {
        year = years[i]
        bool found = false;
        
        //Each county Node is connected to each other county Node within the same year.
        for(iter1 = allCounties.begin(); iter1 != allCounties.end(); iter1++)
        {
            //Find this county's node for the current year
            for (auto& pair : iter1) 
            {
                if (pair.first == year)  // Year exists
                {
                    currentNode = pair.second;
                    found = true;
                    break;
                }
            }

            if(found)
            {
                for(iter2 = iter1 + 1; iter2 != allCounties.end(); iter2++)
                {
                    for (auto& pair : iter2) 
                    {
                        if (pair.first == currentYear)  // Year exists
                        {
                            // Nodes only connect to nodes that share the same year.
                            currentNode->adjacentNodes.push_back(pair.second);
                            pair.second->adjacentNodes.push_back(currentNode);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void StatesGraph::findState(){
    auto start = std::chrono::high_resolution_clock::now();
    string state;
    cout << "Choose a State" << endl;
    getline(cin,state);
    auto it = statesMap.find(state);
    if (it != statesMap.end()) {
        printState(it->second);
    } else {
        std::cout << "State not found." << '\n';
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;
}

void StatesGraph::findCounty() {
    string state;
    cout << "Choose a State" << endl;
    getline(cin,state);

    string county;
    cout << "Choose a County" << endl;
    getline(cin,county);

    string year;
    cout << "Choose a Year: 2008, 2009, 2010, 2011, 2012, 2013. (Write \"All\" to print all years)"<< endl;
    getline(cin,year);
    auto start = std::chrono::high_resolution_clock::now();
    auto stateIter = statesMap.find(state);
    if (stateIter != statesMap.end()) {

        Node* stateNode = stateIter->second;
        auto countyIter = stateNode->countiesMap.find(county);
        if (countyIter != stateNode->countiesMap.end()) {
            cout << county << " in state: " << state << endl;
            for (const auto& yearPair : countyIter->second) {
                if(yearPair.first == year){
                    cout << "Population: " << yearPair.second->population <<endl;
                    cout << "Deaths: " << yearPair.second->numDeaths << endl;
                    cout << "-----------------------------" << endl;
                }
                else if(year == "All"){
                    cout << "Population: " << yearPair.second->population <<endl;
                    cout << "Deaths: " << yearPair.second->numDeaths << endl;
                    cout << "Year: " << yearPair.first <<endl;
                    cout << "-----------------------------" << endl;
                }
            }
        } else {
            cout << "County " << county << " not found in state " << county << endl;
        }
    } else {
        cout << "State " << state << " not found." << endl;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto durationNano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by function: " << durationNano.count() << " nanoseconds" << std::endl;

}

void StatesGraph::findYear() {
    string year;
    cout << "Choose a Year: 2008, 2009, 2010, 2011, 2012, 2013. (Write \"All\" to print all years)"<< endl;
    getline(cin,year);
    map<string, Node*>::iterator iter;


    string stateName;
    cout << "Choose a State: (Write \"All\" to print all the states)" << endl;
    getline(cin,stateName);

    auto start = std::chrono::high_resolution_clock::now();
    if(stateName == "All") {
        for (auto &State: statesMap) {
            cout << "State:" << State.second->name << endl;
            for (auto &countyPair: State.second->countiesMap) {
                cout << "County: " << countyPair.first << endl;

                for (const auto &yearData: countyPair.second) {
                    const string &dataYear = yearData.first;
                    const Node *node = yearData.second;

                    // Check if the user input matches the data year or if the user wants all years
                    if (year == dataYear || year == "All") {
                        cout << "\tYear: " << dataYear << endl;
                        cout << "\tPopulation: " << node->population << endl;
                        cout << "\tDeaths: " << node->numDeaths << endl;
                        cout << "\t---------------------------------" << endl;
                    }
                }
            }
        }
    }
    else {
        auto stateIter = statesMap.find(stateName);
        if (stateIter != statesMap.end()) {
            cout << "State:" << stateIter->second->name << endl;
            for (auto &countyPair: stateIter->second->countiesMap) {
                cout << "County: " << countyPair.first << endl;

                for (const auto &yearData: countyPair.second) {
                    const string &dataYear = yearData.first;
                    const Node *node = yearData.second;

                    // Check if the user input matches the data year or if the user wants all years
                    if (year == dataYear || year == "All") {
                        cout << "\tYear: " << dataYear << endl;
                        cout << "\tPopulation: " << node->population << endl;
                        cout << "\tDeaths: " << node->numDeaths << endl;
                        cout << "\t---------------------------------" << endl;
                    }
                }
            }
        } else{
            cout << "Not found "<< endl;
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto durationNano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cout << "Time taken by function: " << durationNano.count() << " nanoseconds" << std::endl;
    }
}

int StatesGraph::getNodeCount()
{
    return numNodes;
}

Node* StatesGraph::getGraphHead()
{
    return graphHead;
}

/***
//Graph destructor.
StatesGraph::~StatesGraph()
{
    map<string, Node*>::iterator iter;
    map<string, Node*>::iterator iter2;

    for(iter = statesMap.begin(); iter != statesMap.end(); iter++)
    {
        for(iter2 = iter->second->countiesMap.begin(); iter2 != iter->second->countiesMap.end(); iter2++)
        {
            delete iter2->second;
        }

        delete iter->second;
    }
}***/
