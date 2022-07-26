#include "ColorGame.h"
#include <string>
using namespace std;

/*
 * Constructor that takes the number of pots N and a set of N pots.
 */
ColorGame::ColorGame(int N, vector<Pot> containers)
{
    this->N = N;
    this->containers = containers;
}

/*
 * Returns the action name of current state.
 */
string ColorGame::getActionName() {return actionName;}

/*
 * Returns the previous state.
 */
ColorGame *ColorGame::getPrevious() {return previous;}

/*
 * Sets the action name of current state.
 */
void ColorGame::setActionName(string s) {actionName=s;}

/*
 * Sets the previous state.
 */
void ColorGame::setPrevious(ColorGame *p) {previous=p;}

/*
 * Equal operator overload to check if two states are the same.
 * Implemented so that the order of the pots does not count.
 */
bool ColorGame::operator==(const ColorGame &o) const
{
    bool flag;
    //For every pot of first state.
    for (int i=0;i<this->containers.size();i++)
    {
        //Check if there is an identical pot in the second state.
        flag = false;
        Pot s1 = this->containers.at(i);
        for (int j=0;j<o.containers.size();j++)
        {
            Pot s2 = o.containers.at(j);
            if (s1 == s2)
            {
                flag = true;
                break;
            }
        }
        //If not then the two states are not the same.
        if (!flag)
            return false;
    }
    return true;
}

/*
 * The one and only transition operator.
 * Takes the position of source and destination pots and pours as much as liquid is possible from source to destination if possible.
 */
bool ColorGame::pourColor(ColorGame &n, int source, int destination)
{
    //If positions are out of bounds then return false.
    if (source>=N || destination>=N)
        return false;
    else
    {
        //Get the top colors
        int topSourceColor=this->containers.at(source).getUpColor();
        int topDestinationColor=this->containers.at(destination).getUpColor();
        //Check if source and destination have the same top color or the destination pot is empty and destination has empty space and source is not empty.
        if (topSourceColor!=topDestinationColor && topDestinationColor!=0 || !(this->containers.at(destination).isFree()) || topSourceColor==0)
            return false;
        else
        {
            n=*this;
            int mlCounter = 0;
            //Pour all liquid possible with the same color to the destination pot.
            while ((topSourceColor==topDestinationColor || topDestinationColor==0) && n.containers.at(destination).isFree() && (topSourceColor!=0))
            {
                    //Pour 1ml of source color to destination pot
                    n.containers.at(source).removeColor();
                    n.containers.at(destination).addColor(topSourceColor);
                    //Update the top colors
                    topSourceColor=n.containers.at(source).getUpColor();
                    topDestinationColor=n.containers.at(destination).getUpColor();
                    //Increase the ml counter
                    mlCounter++;
            }
            //Construct the string with the action and insert it.
            string str= "Pour "+ to_string(mlCounter) + "ml from "+ to_string(source+1)+" to "+ to_string(destination+1)+".\n";
            n.setActionName(str);
            n.setPrevious(this);
            return true;
        }
    }
}

/*
 * Expand function that applies the transition operator for every pot to every other pot.
 */
vector<ColorGame *> ColorGame::expand()
{
    vector <ColorGame*> children;
    ColorGame *child;
    //For every pot of current state
    for (int i=0;i<N;i++)
    {
        //Check if liquid can be poured to every other pot except the same pot.
        for (int j=0;j<N;j++)
        {
            if (i!=j)
            {
                child = new ColorGame(*this);
                if (pourColor(*child,i,j))
                    children.push_back(child); //If operator can be applied then keep the child.
                else
                    delete child; //If operator can not be applied then delete the child.
            }
        }
    }
    return children;
}
/*
 * Function that generates a key for the current state to help the unordered map of the BFS.
 * Constructs a string with all pot from bottom to top, from first to last with a backslash as a separator.
 */
string ColorGame::getKey()
{
    string dummy;
    for (int i=0;i<containers.size();i++)
    {
        dummy.append(containers.at(i).getPot());
        dummy.append("/");
    }
    dummy.erase(dummy.end()-1);
    return dummy;
}