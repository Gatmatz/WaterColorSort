#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <ctime>
#include <string>
#include "Pot.h"
#include "ColorGame.h"
#include <queue>
#include <chrono>
#include <algorithm>

using namespace std;

ColorGame *BFS (ColorGame *initial, ColorGame *goal, long long &exam, long long &mem)
{
    queue<ColorGame*> front; //Initialize search front using a queue(BFS).
    unordered_map<string,ColorGame*> closed; //Initialize closed set using an unordered map.
    front.push(initial); //Insert the initial state to the search front.
    mem=1;
    exam=0;
    while (front.size() > 0) //As long as search front has states to examine.
    {
        //Calculate the memory needed
        if (front.size() + closed.size() > mem)
            mem = front.size() + closed.size();
        ColorGame *s = front.front(); //Take out the front item of the queue.
        front.pop();
        if (closed.count(s->getKey())==0) //Check if current state is already checked.
        {
            exam++; //Increase the state counter because a new state is about to be checked.
            if (*s==*goal) //If current state is same as the goal of the problem, then return the solution.
                return s;
            //Put the examined state into the closed set.
            pair<string, ColorGame*> k (s->getKey(),s);
            closed.insert(k);
            //Expand using the possible operators from current state.
            vector<ColorGame*> children = s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.count(children[i]->getKey())==0) //Check if children states are included in the closed set.
                    front.push(children[i]);
        }
    }
    return nullptr; //Return null if BFS failed to find a solution.
}

/*
 * Function to make the initial state completely from the user.
 */
ColorGame* makeInitialUSER(int N)
{
    int c1,c2,c3,c4;
    vector<Pot> dummy;
    ColorGame *initial = new ColorGame(N, dummy);
    Pot dum = Pot(c1,c2,c3,c4);
    for (int i=0;i<N;i++)
    {
        cout<<"Give the 4 colors of "<<i+1<<" pot"<<endl;
        cin>>c1>>c2>>c3>>c4;
        if (c1>N-2 || c2>N-2 || c3>N-2 || c4>N-2 || c1<0 || c2<0 || c3<0 || c4<0)
        {
            cout<<"Colors must be strictly positive and up to "<<N - 2<<endl;
            return initial;
        }
        dum = Pot(c1,c2,c3,c4);
        dummy.push_back(dum);
    }
    initial = new ColorGame(N, dummy);
    return initial;
}

/*
 * Function to construct the goal of the water sort problem given the N;
 */
ColorGame* makeGoal(int N)
{
    vector<Pot> dummy;
    for (int i =1;i<N-1;i++)
    {
        Pot dum = Pot(i,i,i,i);
        dummy.push_back(dum);
    }
    for (int i=N-2;i<N;i++)
    {
        Pot dum = Pot(0,0,0,0);
        dummy.push_back(dum);
    }
    ColorGame* goal = new ColorGame(N,dummy);
    return goal;
}

/*
 * Function to construct a random initial state with N-2 colors of 4ml scattered in N pots.
 */
ColorGame* makeInitialRANDOM(int N)
{
    int left[N-1];
    int zeros= 4*N - 4*(N-2);
    int zCounter=0;
    for (int i=0;i<N-1;i++)
        left[i] = 4;
    srand(time(NULL));
    int c1,c2,c3,c4;
    vector<Pot> dummy;
    Pot dum = Pot(c1,c2,c3,c4);
    for (int i=0;i<N;i++)
    {
        c1 = rand()%(N-1);
        while (left[c1]==0 || c1==0 && zCounter>=zeros)
        {
            c1 = rand()%(N-1);
        }
        if (c1==0)
            zCounter++;
        else
            left[c1]--;

        c2 = rand()%(N-1);
        while (left[c2]==0 || c2==0 && zCounter>=zeros)
        {
            c2 = rand()%(N-1);
        }
        if (c2==0)
            zCounter++;
        else
            left[c2]--;

        c3 = rand()%(N-1);
        while (left[c3]==0 || c3==0 && zCounter>=zeros)
        {
            c3 = rand()%(N-1);
        }
        if (c3==0)
            zCounter++;
        else
            left[c3]--;

        c4 = rand()%(N-1);
        while (left[c4]==0 || c4==0 && zCounter>=zeros)
        {
            c4 = rand()%(N-1);
        }
        if (c4==0)
            zCounter++;
        else
            left[c4]--;

        Pot dum = Pot(c1,c2,c3,c4);
        dummy.push_back(dum);
    }
    ColorGame* initial = new ColorGame(N, dummy);
    return initial;
}

int main()
{
    int N;
    cout<<"Insert number of Pots:";
    cin>>N;
    if (N>=20 || N<3)
    {
        cout<<"N must be less than 20"<<endl;
        return -1;
    }
    ColorGame* initial = makeInitialRANDOM(N);
    cout<<"Initial: "<<initial->getKey()<<endl;
    ColorGame* goal = makeGoal(N);
    cout<<"Goal: "<<goal->getKey()<<endl;
    long long memory, examined;
    auto start = chrono::high_resolution_clock::now();
    ColorGame *solution = BFS(initial,goal, examined, memory);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    if (solution == nullptr)
        cout<<"Unsolvable"<<endl;
    else
    {
        cout<<"Found a solution with required memory:"<<memory<<", examined "<<examined<< " states, "<<"in time: "<<duration.count()<<" milliseconds."<<endl;
    }
}
