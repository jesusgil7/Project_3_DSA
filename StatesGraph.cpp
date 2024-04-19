#pragma once

#include "StatesGraph.h"
#include <vector>
#include <map>
#include <iostream>
#include <tuple>

StatesGraph::StatesGraph(vector<tuple<string, string, string, string>>& dataStream)
{
    string currentState = ""; //get from vector of tuples
    int currentYear = 0; //get from vector of tuples
    string currentCounty = "";

    string currentPop = 0; //Population of current tuple.
    string currentDeaths = 0; //# deaths of current tuple.

    //Make head of graph. Any of the 50 states are accessible from here.
    Node* head = new Node;
    graphHead = head;

    //Loop through the data stream.
    for(int i = 0; i < dataStream.size(); i++)
    {
        currentState = get<1>(dataStream[i]);
        currentCounty = get<0>(dataStream[i]);

        currentPop = get<3>(dataStream[i]);
        currentDeaths = get<2>(dataStream[i]);

        //If the state isn't in the graph, add it as a new Node.
        if(statesMap.find(currentState) == statesMap.end())
        {
            //Add new state to the graph & update values.
            Node* newState = new Node;
            head->subNodes.push_back(newState);

            newState->name = currentState;

            //transform(currentState.begin(), currentState.end(), currentState.begin(), ::tolower);

            //Add new state to the list of states in the graph.
            statesMap[currentState] = newState;    
        }

        //If the county isn't in the graph, add it as a new Node pointed to by the state Node.
        if(statesMap[currentState]->countiesMap.find(currentCounty) == statesMap.end())
        {
            //Add new county to the graph & update values.
            Node* newCounty = new Node;
            statesMap[currentState]->subNodes.push_back(newCounty);
            newCounty->name = currentCounty;

            //transform(currentCounty.begin(), currentCounty.end(), currentCounty.begin(), ::tolower);

            //Add new county to the list of states in the graph.
            statesMap[currentState]->countiesMap[currentCounty] = newCounty;    

            //Add a new Node for each of the 4 years
            Node* year09 = new Node;
            year09->name = "2009";

            Node* year10 = new Node;
            year10->name = "2010";

            Node* year12 = new Node;
            year12->name = "2012";

            Node* year13 = new Node;
            year13->name = "2013";

            newCounty->subNodes.push_back(year09);
            newCounty->subNodes.push_back(year10);
            newCounty->subNodes.push_back(year12);
            newCounty->subNodes.push_back(year13);
        }

        statesMap[currentState]->countiesMap[currentCounty]->population = currentPop;
        statesMap[currentState]->countiesMap[currentCounty]->numDeaths = currentDeaths;
    }
}

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

            /*
            /// Delete whitespaces
            input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

            /// Allow user to use lower case
            transform(input.begin(), input.end(), input.begin(), ::tolower);
            */
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

//Print each county in the specified state in alphabetical order.
void StatesGraph::printState(Node* state)
{
    map<string, Node*>::iterator iter;

    for(iter = state->countiesMap.begin(); iter != state->countiesMap.end(); iter++)
    {
        cout<<"\tCounty: " << iter->second->name << endl;
        cout<<"\tDeaths: " << iter->second->numDeaths << endl;
        cout<< "\tPopulation: " << iter->second->population << endl;
        cout<< "\t---------------------------------" << endl;
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
}
