## Title: 
EvacRoute

## A short description of the purpose and goals of the program:

Our project is an evacuation route program designed to help users find the safest and quickest exit in any building, starting from their current location. This program is especially useful in situations where you might be in a large, unfamiliar building and are unsure how to locate the nearest exit. It is also designed for emergencies, such as fires, earthquakes, or active shooter situations, where finding a safe route quickly can be critical.

The program uses a weighted, undirected graph to model each floor of the building. Nodes are placed at key points: every room, exit, stairwell, and doorway leading into hallways. These nodes are labeled with their type (e.g., 'R' for room, 'E' for exit, 'S' for stairwell) and include data about their status, such as whether they are blocked. The distances between connected nodes are also factored in to calculate the shortest, safest path.

When the program begins, you enter your starting location, which can be updated later if needed. Using this input, the program calculates the directions to the nearest safe exit, providing you with a step-by-step list of rooms to pass through or by. The intuitive design ensures that even hallway nodes are named after nearby rooms to make it easier to identify your current location. For example, a hallway outside a room is labeled based on the adjacent room's name.

The goal is to offer an easy-to-use tool that guides users safely and efficiently to an exit, especially in emergencies. Whether you're navigating an unfamiliar building or responding to a crisis, this program ensures your safety by finding the best available path, adapting to blocked routes or other changing conditions along the way.

## Description of the algorithmic approach used to solve the problem:

For connected, undirected graphs, Dijkstra’s algorithm is determined be the most efficient approach for finding the shortest path, given its suitability for weighted graphs and finding the shortest path based on a single starting node. 

## Documentation on how to run the program:

This program is developed in C++ and operates as a console shell. it should berun with this command line in terminal: g++ -std=c++11 -o prog *.cpp. Below is a detailed guide on how to use it.

After launching the program, the welcome screen first displays a welcome message, welcoming the user to use the program. After that is the first menu, where the user can select options 1–3:

1) Start Program - Allows the user to start the program.
2) Show building plan - Shows the user the building plan outline and how all of the rooms are connected together.
3) Exit - Allows the user to end the program.

Start program - Option 1 from the Main Menu:
When the user selects this option, they are prompted to enter their current location in the building. This can be done by stating the actual room you are in, such as "122." You can also enter your location if you are in the hallway by first inputting a capital 'H,' followed by the closest room you are next to. You can even enter a stairway or exit node location. 

An algorithm is then run which prints out your shortest path to safety. This then takes you to another menu. You can also choose 4, which will exit you from this menu and take you to the Main Menu. After the algorithm runs, the next menu is the Path Finder Main Menu, which is the last menu in the program, the Path Finder Main Menu. From this menu, you can:

 1. Update unavailable room in path
 2. Reset all rooms to unblocked
 3. Update starting room
 4. RETURN

Option 1 allows the user to mark a room or path as blocked off. This is for if you attempt to follow a path, but one of the listed nodes is blocked off, and you will be able to indicate that.
Option 2 allows you to rest all of the rooms marked "blocked" to "unblocked"
Option 3 Update a new starting location. This will prompt you to enter your new location in the same way as before and then take you back to the Path Finder Main Menu.
option 4: RETURN. This will take you back to the actual Main Menu of the program.

## What assumptions did you make when working on the project (e.g. knowledge level of users, etc.):

We assume that the user can at least identify the name of the room or hallway they are currently in. This is important for the program to work properly since it relies on the user’s input to calculate the path. Unless specifically implemented in future versions, we also assume able-bodiedness. People with mobility challenges often need to find designated points of rescue rather than direct exits if they can’t reach one, which isn’t accounted for in this version of the program.

Building information is stores in flies which are read into the program. This program takes in two different text files: one for that building room data which includes the rooms ID number, room number, Room type identifier, and if it is unblocked or not. The second text file is a list which contaisn the connections in a building such as where one room leads to another, as well as the weight between them. Based on user input, the program dynamically generates an exit path. 

## A detailed pseudo-code design for the algorithm:

A user will input a request to either start the program or to see the building floor plan. From there, the user will
select a start room once the program has begun. The start room will be denoted as 'Room 631" or "H633" for example. The
user then has the ability to choose their algorithm and generate a path to safetly. The output of the program will
be the sequence of rooms, staircases and halls needed to escape!

//Dijkstras
//User will give us the source node (room input)
//From source node, set distance to itself to 0 and look at nearby unvisited nodes
//Find the shortest path between the source node and the unvisited neighbor nodes
//The priority queue replaces the array of distances in this example and will update the distance
//from the node to the source and keep the best option at the top of the priority queue
//after it has identified the shortest path to each exit, the program determines which of the
//shortest paths is the ultimate shortest path. 
//The user is then displayed a walking path of rooms, hallways and stairs that will lead to an exit
user can now either change their room, update if a node is blocked, or exit!

## Works Cited:
runtime 
https://cplusplus.com/reference/chrono/high_resolution_clock/now/
research for priority queue in Dijkstras
https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
research for priority queue and analysis of big O
https://www.geeksforgeeks.org/time-and-space-complexity-of-dijkstras-algorithm/
Further research and explanation of how the queue works (I did not copy or mimick the code given, I used the images for conceptual understanding)
https://takeuforward.org/data-structure/dijkstras-algorithm-using-priority-queue-g-32/

