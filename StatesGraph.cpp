#include "StatesGraph.h"
#include <iostream>
#include <vector>
#include <map>
#include <tuple>

StatesGraph::StatesGraph(vector<tuple<string, string, string, string, string>>& dataStream) {
    Node* head = new Node; // Head node
    graphHead = head;

    for (const auto& entry : dataStream) {
        string currentCounty = get<0>(entry);
        string currentState = get<1>(entry);
        string currentDeaths = get<2>(entry);
        string currentPop = get<3>(entry);
        string currentYear = get<4>(entry);

        // Check if the state exists, and add if not
        if (statesMap.find(currentState) == statesMap.end()) {
            Node* newState = new Node{name: currentState};
            head->subNodes.push_back(newState);
            statesMap[currentState] = newState;
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
        }
    }
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
        cout << "State: " << iter->second->name << endl;
        printState(iter->second); //Print each county in the state in alphabetical order.
    }
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
