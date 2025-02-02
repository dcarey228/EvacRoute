#ifndef HEADER_H
#define HEADER_H

/* 
 * This is the header file for the final project. This contins structs for holding data as well as classes for boht
 * the menu and "exit finder" the mneu is where the program is essentially "ran through". The exitFinder class has to 
 * to do with everything about getting information such as starting location, making a node available or not, and 
 * where the actul algorithm implementations are.  
 */

//libraries
#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>       // For priority_queue
#include <utility>     // For std::pair
#include <algorithm>   // For reverse
#include <fstream>      //to read in/out file txt data

using namespace std;

//contains info for the vector of array which holds data about each node
struct info
{
    int ID;                         //unique arbitrarily chosen number
    string name;                    //The name of the node (plain english)
    char nodeType;                  //the node is either a room, a hallway or an exit
    bool isAvailable;               //used to track if a staircase/room is blocked off or not, set to true if it IS avaialble

    info(int ID, string name, char nodeType, bool isAvailable = true) : ID(ID), name(name), nodeType(nodeType), isAvailable(isAvailable) {}
    info();
};

//used to handle the menu abstarction aspect of the program
class menuClass
{
    public:
        menuClass();                //constructor
        void menuHub();             //where the menu /program is run from 
        void welcome();             //prints welcome message 
        void mainMenu();            //prints menu and returns user ans
        void endMessage();          //prints end message

    private:
        int menuAns;                //used to get input from user about how they want to proceed through program

};

//used to handle the exit finder
class exitFinder
{
    public:
        exitFinder();              //constructor
        void exitHub();            //where all of exit finder is ran through
        void getStart();           //finds the strating room number  
        void algoMenu();                //menu for the algorithms
        void getBlocked();             //allows user to update any blcoked rooms
        void resetBlocked();            //so that the blocked rooms can be reset
        void showBuildingPlan();           //shows the building plan roughly
        void dijkstra();           //main finder algorithm
        int getRoomIndex(const string& roomName); // For mapping room name to index in roomInfo

        bool readInfoData();        //reads in the text file for the building data
        bool readConnectionsData(); //reads in text file for building data connections
        bool updateInfoData();      //writes out new info to text file
        bool printRoomInfo();

    private:
        vector<vector<int>> connections; // Stores graph connection
        vector<info> roomInfo;      // Stores building plan
        int algoAns;                //gets answer for algoMenu
        int exitAns;               //gets the anser to menu questiosn asked inside exitfinder
        int startRoom;             //holds the starting room location
        //int lastChosenAlgo;        // Holds algorithm chosen for rerunning algo after a node is blocked
        vector<string> blockedRooms;   //holds all the blocked room in this vector so they can be reset

};

//general functions:
void verifyInput(int beginCap, int endCap, int & num);

#endif // HEADER_H