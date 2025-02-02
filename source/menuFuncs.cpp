#ifndef MENU
#define MENU
#include "header.h"

/*
 * This file is where all of the functions from the menuClass are implemented. The functions are eventually all
 * called through the menuHub which is where the main outer loop for the program is executed from. From the menuHub,
 * the rest of the programs functions are called as well.
 */


//constructor
menuClass :: menuClass(){menuAns = 0;}

//this function is where the program is run/looped from
void menuClass :: menuHub()
{
    exitFinder finder;      //create object to access exitHub
    //info roomInfo;
    if(!finder.readInfoData() && !finder.readConnectionsData())
        cerr << "\nERROR: file data could not be read";
    else cout << "\nSucessfully read in external file data" << endl;

    welcome();  //print welcome message
    mainMenu(); //prints main menu and updates menuAns

    while (menuAns != 3) { // 3 means to exit the program
        if (menuAns == 1)
            finder.exitHub(); // Controls finding the actual path

        if (menuAns == 2)
            finder.showBuildingPlan(); // Show the building plan

        mainMenu();
    }

    endMessage();      //prints end message
}

//function to print welcome message
void menuClass :: welcome()
{
    cout << "\nWelcome to EvacRoute, we are here to help!" << endl;
    //add more stuff maybe a description and names??
}

//prints end message
void menuClass :: endMessage()
{
    cout << "\nThank you for using the program!" << endl;
}      


//function to print main menu and gain input 
void menuClass :: mainMenu()
{
    cout << "\n    ~~~ Main Menu ~~~"
         << "\n\t1. Start"
         << "\n\t2. Show Building Plan"
         << "\n\t3. Exit Program"
         << "\n~~~~~~~~~~~~~~~~~~~~~~~~~"
         << "\nEnter 1-3: ";
        
    cin >> menuAns;
    verifyInput(1,3, menuAns);   //to verify input
}


//used to verify inout is within a speciifc range
void verifyInput(int beginCap, int endCap, int & num)
{
    while(num < beginCap || num > endCap)    //loops until its valid input
    {
        cerr << "\nERROR: Please enter a valid number between " << beginCap << " and " << endCap << ": ";
        cin >> num;
    }
}

#endif // MENU