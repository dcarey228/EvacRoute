#include "header.h"

int main()
{
    //Input: User identifies a building they are in
    //Program will select the corresponding building struct with all weights, nodes, and other relavant information
    //Input: User will select a room
    //Program will use the room node as the starting node and calculate the shortest path to EACH exit in building
    //Program will then use whatever the shortest of the shortest paths generated to direct the user out of the building
    //Within the loop, the program will expect input if the user reports an exit is inaccessible. From there it will generate
    //a new shortest path to each exit and select the shortest of those
    //Once the user reports safety, the program is complete
    
    menuClass menu; //object of the menu class to access functions
    menu.menuHub();   //calls all of menu

    return 0;
}


