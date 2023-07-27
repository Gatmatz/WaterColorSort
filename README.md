#MODELING 

Two classes Pot and ColorGame are used to model the problem:

##POT

The class Pot represents a container with a capacity of 4ml. The pot is divided into 1ml slots and works as a stack with the help of a fixed array int pot[4]. Colors are represented by integers in the space [1,N-2]. The number 0 indicates that there is an empty space in the container. The class supports the basic functions of a stack such as adding liquid(addColor), removing liquid(removeColor) and checking if there is free space(isFree) making sure it ignores free spaces(nulls) and obeys the rules of the game.
The constructor accepts 4 integers and pushes them onto the stack so that the first argument is at the bottom of the stack. Also, the equality operator has been overloaded to check the equality of two 1 to 1 ml containers from the beginning to the end of the stack.
Finally, the getPot() function constructs a string of the colors in the pot starting from the bottom of the stack and working up.


##COLORGAME

The ColorGame class is the base class of the problem and represents a state of the game.
To represent the problem, an integer N is used that shows the size of the pots and a vector of type Pot where all the pots in the game are represented.
There is a single transition operator that accepts a ColorGame state to update (if the operator can be applied) and 2 integers that mark the source container and destination container. The operator makes the following checks to apply:
1. Checks if there is enough space in the destination container.
2. Checks if the color in the source and destination container is the same or even if the destination container is empty.
3. Checks if the source container is empty.
The transition operator does the above checks and if they can be applied then it only transfers 1ml. For fluid above ml a while loop structure is used which performs the above checks and transfers as many ml as possible.
To expand states, an expand function is used which initializes a vector that will hold all extended states (children). The function checks whether the transition operator is applied for all possible cases (from all containers to all containers) and if applied then keeps the child in the vector, otherwise deletes it.
Also, the equality operator has been overloaded so that when comparing two states the order of the containers does not count but only if the same containers exist.
At the same time, a key generation function (getKey) has been implemented for each situation. The key is a string containing the numbers of all containers in sequence separated by the “/” symbol. This function is used by BFS and is needed to store the states in BFS's unordered_map.
Finally, tracking of each step is supported with the functions set/getPrevious, in which the previous state is set and stored, and set/getActionName, in which the action of each state is set and stored.


#BFS

To implement BFS, a queue is used for the search front and an unordered_map for the closed set. The choice to implement unordered_map as a closed set was made because this particular structure is fast in looking up elements, which is essential for BFS.
Also, additional data are calculated and returned for searching the solution such as the memory (mem) required and the number of states (exam) checked.
If BFS finds a solution successfully then it returns it, otherwise it returns a null pointer.

#MAIN

In main there are assistive functions, which are used to construct the initial and final state.
The function makeInitialUSER accepts the number of containers N and gives the option to the user by typing in the colors of the containers one by one with integers to construct the initial state. Checks are made for the interval of integers ([0,N-2]) given as input by the user, but no check is made for the validity of the colors (ie that there are 4ml of each color scattered). At the same time, however, BFS will inform him that the problem is unsolved.
The makeInitialRANDOM function accepts the number of bins N and constructs a random initial state of the problem making sure that the colors are in the correct intervals while still conforming to the game rules.
The function makeGoal accepts the number of containers N and returns the final state of the game, i.e. each container contains 4ml of each color and two containers are empty.
In main the program asks the user for the number of containers N, checking if they are in the interval [3,19]. It then randomly constructs an initial and final state and runs BFS. At the same time, it times the BFS with the help of the <chrono> library and if it finds a solution it prints the fact that it found a solution along with the memory, the states and the time it took. Otherwise, it prints that the problem is unresolved.
