#pragma once

#include "StatesGraph.h"
#include <vector>
#include <map>
#include <iostream>

StatesGraph::StatesGraph(std::vector<std::tuple<std::string>>& dataStream)
{
    std::string currentState = ""; //get from vector of tuples
    int currentYear = 0; //get from vector of tuples
    std::string currentCounty = "";

    float currentPop = 0; //Population of current tuple.
    float currentDeaths = 0; //# deaths of current tuple.
    float currentRate = 0; //Death rate per 100,000 population of current tuple.

    //Make head of graph. Any of the 50 states are accessible from here.
    Node* head = new Node;

    //Loop through the data stream.
    for(int i = 0; i < dataStream.length(); i++)
    {
        currentYear = get<0>(dataStream[i]);
        currentState = get<1>(dataStream[i]);
        currentCounty = get<2>(dataStream[i]);

        currentPop = get<3>(dataStream[i]);
        currentDeaths = get<4>(dataStream[i]);
        currentRate = get<5>(dataStream[i]);

        //If the state isn't in the graph, add it as a new Node.
        if(statesMap.find(currentState) == statesMap.end())
        {
            //Add new state to the graph & update values.
            Node* newState = new Node;
            head->subNodes.push_back(newState);
            newState->name = currentState;

            //Add new state to the list of states in the graph.
            statesMap[currentState] = newState;
        }

        //If the county isn't in the graph, add it as a new Node pointed to by the state Node.
        if(statesMap[currentState].find(currentCounty) == statesMap.end())
        {
            //Add new county to the graph & update values.
            Node* newCounty = new Node;
            statesMap[currentState]->subNodes.push_back(newCounty);
            newCounty->name = currentCounty;

            //Add new county to the list of states in the graph.
            countiesMap[currentCounty] = newCounty;

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
            newCounty->subNodes.push_back(year11);
            newCounty->subNodes.push_back(year12);
        }

        if(currentYear == "2009")
        {
            Node* data = new Node;
            statesMap[currentState]->countiesMap[currentCounty]->subNodes[0]->population
        }


    }

    /*
    Node* node1 = new Node;
    node1->stateName = "Alabama";
    statesMap["Alabama"] = node1;

    Node* node2 = new Node;
    node2->stateName = "Alaska";
    statesMap["Alaska"] = node2;

    Node* node3 = new Node;
    node3->stateName = "Arizona";
    statesMap["Arizona"] = node3;

    Node* node4 = new Node;
    node4->stateName = "Arkansas";
    statesMap["Arkansas"] = node4;

    Node* node5 = new Node;
    node5->stateName = "California";
    statesMap["California"] = node5;

    Node* node6 = new Node;
    node6->stateName = "Colorado";
    statesMap["Colorado"] = node6;
    
    Node* node7 = new Node;
    node7->stateName = "Connecticut";
    statesMap["Connecticut"] = node7;

    Node* node8 = new Node;
    node8->stateName = "Delaware";
    statesMap["Delaware"] = node8;

    Node* node9 = new Node;
    node9->stateName = "Florida";
    statesMap["Florida"] = node9;

    Node* node10 = new Node;
    node10->stateName = "Georgia";
    statesMap["Georgia"] = node10;

    Node* node11 = new Node;
    node11->stateName = "Hawaii";
    statesMap["Hawaii"] = node11;

    Node* node12 = new Node;
    node12->stateName = "Idaho";
    statesMap["Idaho"] = node12;

    Node* node13 = new Node;
    node13->stateName = "Illinois";
    statesMap["Illinois"] = node13;

    Node* node14 = new Node;
    node14->stateName = "Indiana";
    statesMap["Indiana"] = node14;

    Node* node15 = new Node;
    node15->stateName = "Iowa";
    statesMap["Iowa"] = node15;

    Node* node16 = new Node;
    node16->stateName = "Kansas";
    statesMap["Kansas"] = node16;

    Node* node17 = new Node;
    node17->stateName = "Kentucky";
    statesMap["Kentucky"] = node17;

    Node* node18 = new Node;
    node18->stateName = "Louisiana";
    statesMap["Louisiana"] = node18;

    Node* node19 = new Node;
    node19->stateName = "Maine";
    statesMap["Maine"] = node19;

    Node* node20 = new Node;
    node20->stateName = "Maryland";
    statesMap["Maryland"] = node20;

    Node* node21 = new Node;
    node21->stateName = "Massachusetts";
    statesMap["Massachusetts"] = node21;

    Node* node22 = new Node;
    node22->stateName = "Michigan";
    statesMap["Michigan"] = node22;

    Node* node23 = new Node;
    node23->stateName = "Minnesota";
    statesMap["Minnesota"] = node23;

    Node* node24 = new Node;
    node24->stateName = "Mississippi";
    statesMap["Mississippi"] = node24;

    Node* node25 = new Node;
    node25->stateName = "Missouri";
    statesMap["Missouri"] = node25;

    Node* node26 = new Node;
    node26->stateName = "Montana";
    statesMap["Montana"] = node26;

    Node* node27 = new Node;
    node27->stateName = "Nebraska";
    statesMap["Nebraska"] = node27;

    Node* node28 = new Node;
    node28->stateName = "Nevada";
    statesMap["Nevada"] = node28;

    Node* node29 = new Node;
    node29->stateName = "New Hampshire";
    statesMap["New Hampshire"] = node29;

    Node* node30 = new Node;
    node30->stateName = "New Jersey";
    statesMap["New Jersey"] = node30;

    Node* node31 = new Node;
    node31->stateName = "New Mexico";
    statesMap["New Mexico"] = node31;

    Node* node32 = new Node;
    node32->stateName = "New York";
    statesMap["New York"] = node32;

    Node* node33 = new Node;
    node33->stateName = "North Carolina";
    statesMap["North Carolina"] = node33;

    Node* node34 = new Node;
    node34->stateName = "North Dakota";
    statesMap["North Dakota"] = node34;

    Node* node35 = new Node;
    node35->stateName = "Ohio";
    statesMap["Ohio"] = node35;

    Node* node36 = new Node;
    node36->stateName = "Oklahoma";
    statesMap["Oklahoma"] = node36;

    Node* node37 = new Node;
    node37->stateName = "Oregon";
    statesMap["Oregon"] = node37;

    Node* node38 = new Node;
    node38->stateName = "Pennsylvania";
    statesMap["Pennsylvania"] = node38;

    Node* node39 = new Node;
    node39->stateName = "Rhode Island";
    statesMap["Rhode Island"] = node39;

    Node* node40 = new Node;
    node40->stateName = "South Carolina";
    statesMap["South Carolina"] = node40;

    Node* node41 = new Node;
    node41->stateName = "South Dakota";
    statesMap["South Dakota"] = node41;

    Node* node42 = new Node;
    node42->stateName = "Tennessee";
    statesMap["Tennessee"] = node42;

    Node* node43 = new Node;
    node43->stateName = "Texas";
    statesMap["Texas"] = node43;

    Node* node44 = new Node;
    node44->stateName = "Utah";
    statesMap["Utah"] = node44;

    Node* node45 = new Node;
    node45->stateName = "Vermont";
    statesMap["Vermont"] = node45;

    Node* node46 = new Node;
    node46->stateName = "Virginia";
    statesMap["Virginia"] = node46;

    Node* node47 = new Node;
    node47->stateName = "Washington";
    statesMap["Washington"] = node47;

    Node* node48 = new Node;
    node48->stateName = "West Virginia";
    statesMap["West Virginia"] = node48;

    Node* node49 = new Node;
    node49->stateName = "Wisconsin";
    statesMap["Wisconsin"] = node49;

    Node* node50 = new Node;
    node49->stateName = "Wyoming";
    statesMap["Wyoming"] = node50;
    */
}



//Graph destructor.
/*
StatesGraph::~StatesGraph()
{
    std::map<string, Node>::iterator iter;

    for(iter = statesMap.begin(); iter != statesMap.end(); iter++)
    {

    }
}
*/