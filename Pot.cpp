#include "Pot.h"
using namespace std;
//Constructor that pushes the colors like a stack (color c1 is at the bottom).
Pot::Pot(int c1, int c2, int c3,int c4)
{
    pot[0] = c1;
    pot[1] = c2;
    pot[2] = c3;
    pot[3] = c4;
}
bool Pot::isFree()
{
    //If top of the pot has free space return true.
    if (pot[3]==0)
        return true;
    else
        return false;
}

void Pot::addColor(int color)
{
    //If pot has empty space
    if (this->isFree())
    {
        //Find the deepest empty space and insert the new color.
        for (int i=0;i<4;i++)
        {
            if (pot[i]==0)
            {
                pot[i]=color;
                break;
            }
        }
    }
}

int Pot::getUpColor()
{
    //Find the first non-empty position.
    int i = 3;
    while (pot[i] == 0 && i>=0)
    {
        i--;
    }
    //If there is a non-empty position then return its color.
    if (i>=0)
        return pot[i];
    else //If pot is empty return 0.
        return 0;
}

void Pot::removeColor()
{
    //Find the first non-empty position.
    int i = 3;
    while (pot[i] == 0 && i>=0)
    {
        i--;
    }
    //If there is one then remove the color by setting it to zero.
    if (i>=0)
        pot[i] = 0;
}

string Pot::getPot()
{
    string dummy;
    //Constructs a string with the colors of the pot starting from the bottom.
    for (int i=0;i<4;i++)
    {
        dummy.append(to_string(pot[i]));
    }
    return dummy;
}
bool Pot::operator==(const Pot &o) const
{
    //Checks if two Pots have the same color.
    bool flag = true;
    for (int i=0;i<4;i++)
    {
        if (this->pot[i] != o.pot[i])
        {
            flag = false;
            break;
        }
    }
    return flag;
}