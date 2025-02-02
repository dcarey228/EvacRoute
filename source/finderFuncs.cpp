#ifndef FUNCS
#define FUNCS
#include "header.h"
using namespace std;
/*
 * This file is where all of the functions from the exitFinder clas are implemented (except for constructor which is in
 * buildingData.cpp). The functions are eventually all called through the exitHub() which is where the main inner loop for
 * the program is executed from. 
 */


//constructor for exit finder
exitFinder::exitFinder() : algoAns(0), exitAns(0), startRoom(0) {}

//constructor for struct info
info :: info()
{
    int ID = 0;                         //unique aritrarily chosen number
    int name = 0;                    //The name of the node (plain english)
    char nodeType = '\0';                  //the node is either a room, a hallway or an exit
    bool isAvailable = true;

}

bool exitFinder::printRoomInfo()
{
    cout << "roominfo size: " << roomInfo.size() << endl;

    for(int i = 0; i < roomInfo.size(); ++i)
    {
        cout << "\nID: " << roomInfo[i].ID << " | "
             << "name: " << roomInfo[i].name << " | "
             << "nodeType: " << roomInfo[i].nodeType << " | ";
        if(roomInfo[i].isAvailable) //is true
            cout << "isAvailable: TRUE" << endl;
        else cout << "isAvailable: FALSE" << endl;
    }
    return true;
}

bool exitFinder::updateInfoData()
{
    ofstream fout("roomInfoData.txt");

    if(!fout)
    {
        cerr << "\nERROR: Unable to write new data to file";
        return false;
    }
    for(const auto& entry : roomInfo)
        fout << entry.ID << "|"
             << entry.name << "|"
             << entry.nodeType << "|"
             << entry.isAvailable << "|" << "\n";

    fout.close();
    return true;
}

//function to control everything for finding the actual path
void exitFinder :: exitHub()
{
  /*if(!printRoomInfo())
        cerr << "\nERROR: could not print room info data!";
    else cout << "\nSuccessfully printed roomInfo data";
  */
    getStart();             //gets a valid starting room number
    algoMenu();             //prints menu options and returns ans

    while(algoAns != 4) //4 means to exit
    {
        if(algoAns == 1)    //update blocked room
            getBlocked(); 

        if(algoAns == 2)    //reset all blocked rooms
            resetBlocked();

        if(algoAns == 3)    //update starting room
            getStart();       

        algoMenu();
    }
}

//updates any rooms that are blocked
void exitFinder :: getBlocked()
{
    string roomName = "";
    bool isValid = false; // Controlling loop
    while (!isValid) {
        cout << "\n\t Enter the name of the blocked room (ie: '122', 'H115', '32'): "
             << "\n\t Blocked Room: ";
        cin.ignore(100, '\n'); // Clearing input buffer
        cin >> roomName; 
        //cout << "\nYou enetered Room: " << roomName << endl;

        blockedRooms.push_back(roomName);   //add it to the list of blocked rooms for resetting later if wanted

        int blockedRoomID = getRoomIndex(roomName);  //returns ID of blocked room
        if (blockedRoomID == -1) {
            cout << "Invalid, no matching room. Try again." << endl;
        }
        else 
        {
            //roomInfo[blockedRoomID -1].isAvailable = false; // Marking room as blocked
            roomInfo[blockedRoomID].isAvailable = false; // Marking room as blocked
            if(!updateInfoData())
                cerr << "\nERROR: could not write new data to file";
            else cout << "\nSuccess! Wrote new data to file.";
            //printRoomInfo();
            isValid = true; 
        }
    }
}

void exitFinder::resetBlocked()
{
    for (auto& room : roomInfo)
    {
        room.isAvailable = true;
    }
    if(!updateInfoData())
        cerr << "\nERROR: could not write new data to file" << endl;
    else cout << "\nSuccess! Reset all rooms to unblocked" << endl;
}

void exitFinder::showBuildingPlan()
{
    cout << "\n~-~-~-~-~-~Building Plan-~-~-~-~-~-~-~-" << endl;
    cout << endl;
    cout << "Connections: " << endl; 

    for (const auto& conn : connections)
    {
        int startNode = conn[0];
        int endNode = conn[1];
        int weight = conn[2];

        // Including names for the start and end nodes
        string startName, endName;
        for (const auto& room : roomInfo)
        {
            if (room.ID == startNode) startName = room.name;
            if (room.ID == endNode) endName = room.name;
        }
        cout << startName << " (Node " << startNode << ") -> "
             << endName << " (Node " << endNode << ") [Weight: " << weight << "ft.]" << endl;
        cout << endl;
    }

    cout << "-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-" << endl;
}

//prints menu options and gets user ans
void exitFinder :: algoMenu()
{
    cout << "\n~-~-~ Path Finder Main Menu ~-~-~"
         << "\n\t1. Update unavailable room in path"
         << "\n\t2. Reset all blocked rooms"
         << "\n\t3. Update starting room"
         << "\n\t4. RETURN"
         << "\n~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~"
         << "\n\tEnter: ";
    cin >> algoAns;
    verifyInput(1,4,algoAns);
}

//gets a valid starting room number
void exitFinder :: getStart()
{
    string roomName = "";
    bool isValid = false;
    while(!isValid)
    {
        cout << "\nEnter the name of the room you are in ie: '233', 'H115', '32'): "
             << "\nRoom: ";
        cin.ignore(100, '\n'); // Clearing input buffer
        cin >> roomName; 

        //cout << "\nYou entered Room " << roomName << "!" << endl;

        int startRoomIndex = getRoomIndex(roomName);    //returns ID of blocked room

        if (startRoomIndex == -1) //-1 means room entered does not exist
            cout << "No match :( Try again." << endl;
        else
        {
            startRoom = roomInfo[startRoomIndex].ID; // Updating startRoom with corresponding ID
            isValid = true;
        }
    }
    dijkstra();
}

//searches for matching room/hallway/stair in roomInfo and returns its unique ID number
int exitFinder::getRoomIndex(const string& roomName) {

    for (const auto& room : roomInfo)
    {
        if (room.name == roomName)
            return room.ID;
    }
    return -1; 
}


void exitFinder::dijkstra() 
{
    int n = roomInfo.size();

    int startRoomIndex = -1;
    for (size_t i = 0; i < roomInfo.size(); ++i) {
        if (roomInfo[i].ID == startRoom) { // Matching by room ID
            startRoomIndex = i;
            break;
        }
    }

    if(!roomInfo[startRoomIndex-1].isAvailable) //if it's false
    {
        cerr << "\nThis room is blocked off!" << endl;
        return;
    }
    if (startRoomIndex == -1) {
        cout << "Invalid start room: " << startRoom << endl;
        return;
    }

    vector<int> dist(n, INT_MAX); // Distance from startRoomIndex
    vector<int> prev(n, -1);      // Previous node in the shortest path
    vector<bool> visited(n, false); //visited vector to keep track of visited nodes

    dist[startRoomIndex] = 0;
    
    // Min-heap priority queue to select the next closest node
    using NodeDist = pair<int, int>; // {distance, node}
    priority_queue<NodeDist, vector<NodeDist>, greater<NodeDist>> pq;
    pq.push({0, startRoomIndex});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (visited[currentNode]) continue;
        visited[currentNode] = true;

        //actual dijkstra's algorithm implementation
        for (const auto& conn : connections) {
            int from = conn[0] - 1;
            int to = conn[1] - 1;
            int weight = conn[2];

            if ((from == currentNode || to == currentNode) && roomInfo[from].isAvailable && roomInfo[to].isAvailable) {
                int neighbor = (from == currentNode) ? to : from;
                if (currentDist + weight < dist[neighbor]) {
                    dist[neighbor] = currentDist + weight;
                    prev[neighbor] = currentNode;
                    pq.push({dist[neighbor], neighbor});
                }
            }
        }
    }

    // Find the nearest exit of all given exits
    int nearestExit = -1;
    int shortestDist = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (roomInfo[i].nodeType == 'E' && dist[i] < shortestDist) {
            shortestDist = dist[i];
            nearestExit = i;
        }
    }

    //no exits are accessible
    if (nearestExit == -1 || shortestDist == INT_MAX)
    {
        cout << "No accessible exits." << endl;
        return;
    }

    cout << "Nearest Exit: " << roomInfo[nearestExit].name
         << " (Distance: " << shortestDist << ")" << endl;

    // Reconstruct the path to the nearest exit
    vector<int> path;
    for (int at = nearestExit; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    cout << "Path to Exit: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << roomInfo[path[i]].name;
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}


bool exitFinder::readInfoData()
{
    ifstream fin("roomInfoData.txt");

    if (!fin) {
        cout << "Failed to open file." << endl;
        return false;
    }

    info tempInfo;      //used to read in info as we go

    while (!fin.eof() && fin)  //ensure first data set is a valid read, then enter loop
    {
        tempInfo = info();  //call constructro to reset

        fin >> tempInfo.ID;        // Read integer ID
        //tempInfo.push_back(addFile.ID);
        fin.ignore(100, '|');     // Ignore the delimiter

        getline(fin, tempInfo.name, '|');  // Read the name string until '|'

        fin >> tempInfo.nodeType;    // Read char for gender (e.g., 'M' or 'F')
        fin.ignore(100, '|');     // Ignore the delimiter

        fin >> tempInfo.isAvailable; // Read bool (expecting 1 or 0)
        fin.ignore(100, '\n');     // Ignore the newline after the record

        roomInfo.push_back(tempInfo);
    }

    fin.close();
    return true;
}


bool exitFinder::readConnectionsData()
{ 
    ifstream fin;
    fin.open("connectionsData.txt");

    if(!fin.is_open())
    {
        cerr << "\nERROR! Cannot open file" << endl;
        return false;
    }

    vector<int> tempConn;
    while(!fin.eof() && fin)
    {
        tempConn.clear();
        int value;
        fin >> value;
        tempConn.push_back(value);
        fin.ignore(100,'|');


        fin >> value;
        tempConn.push_back(value);
        fin.ignore(100,'|');

        fin >> value;
        tempConn.push_back(value);
        fin.ignore(100,'|');

        connections.push_back(tempConn);
        fin.ignore(100, '\n');
    }
    fin.close();
    return true;
}

#endif //FUNCS