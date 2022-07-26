#ifndef AI_PROJECT_1_COLORGAME_H
#define AI_PROJECT_1_COLORGAME_H
#include "Pot.h"
#include <string>
#include <vector>

class ColorGame {
public:
    ColorGame(int N, vector<Pot> containers); //Constructor that takes the number of pots N and a set of N pots.
    void setPrevious (ColorGame *p); //Sets the previous state.
    ColorGame *getPrevious(); //Returns the previous state.
    void setActionName (string s); //Sets the action name of current state.
    string getActionName(); //Returns the action name of current state.
    bool operator==(const ColorGame& o) const; //Overload equal operation for state comparison.
    bool pourColor(ColorGame &n, int source, int destination); //Transition operator.
    string getKey(); //Key generator to help with the BFS.
    vector <ColorGame *> expand(); //Expand states.
private:
    //Game representation
    int N;
    vector<Pot> containers;

    //Path from the root
    string actionName;
    ColorGame *previous;
};


#endif