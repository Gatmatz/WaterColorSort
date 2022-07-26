#ifndef AI_PROJECT_1_POT_H
#define AI_PROJECT_1_POT_H
#define LIMIT 3
#include <stack>
#include <string>
#include <vector>
using namespace std;

class Pot{

private:
    int pot[4]; //Array of 4 items representing a pot. (0 is empty space)
public:
    //Constructor
    Pot(int, int, int ,int);
    bool isFree(); //Checks if there is free space in the pot.
    int getUpColor(); //Returns the top color of the pot.
    void addColor(int); //Adds a color into the pot if possible.
    void removeColor(); //Removes a color from the pot if there is one.
    string getPot(); //Constructs a string with the colors of the pot starting from the bottom.
    bool operator==(const Pot& o) const; //Checks if two Pots have the same color.
};
#endif
