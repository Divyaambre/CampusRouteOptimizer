#include <iostream>
#include <cctype>
#include "Graph.h"
#include "Dijkstra.h"


using namespace std;

string findLocation(const Graph& graph, const string& input) {

    for (const auto& location : graph.getLocations()) {

        string locationLower = location;

        for (char& c : locationLower) {
            c = tolower(c);
        }

        if (locationLower == input) {
            return location;
        }
    }

    return "";
}


int main() {

    Graph graph;

    string source;
    string destination;

    auto normalize = [](string text) {
    for (char& c : text) {
        c = tolower(c);
    }
    return text;
};

    // Open JSON file
        graph.loadFromJSON("../data/campus.json");

        cout << "Available locations:" << endl;

for (const auto& location : graph.getLocations()) {
    cout << "- " << location << endl;
}

cout << endl;

        cout << "Enter source location: ";
cin >> source;

cout << "Enter destination location: ";
cin >> destination;

// Convert user input to lowercase
string sourceLower = normalize(source);
string destinationLower = normalize(destination);

source = findLocation(graph, sourceLower);
destination = findLocation(graph, destinationLower);

if (source == "" || destination == "") {
    cout << "Invalid source or destination." << endl;
    return 1;
}

if (source == destination) {
    cout << "Source and destination are the same." << endl;
    return 0;
}

char choice;

cout << "Do you want to block the Canteen-CSE road? (y/n): ";
cin >> choice;

if (choice == 'y' || choice == 'Y') {
    graph.blockRoad("Canteen", "CSE");
}  

else {
    graph.unblockRoad("Canteen", "CSE");
}

    // Find shortest route
    RouteResult result =
        findShortestPath(graph, source, destination);

    if (result.found) {

        cout << "Shortest Route: ";

        for (int i = 0; i < result.path.size(); i++) {

            cout << result.path[i];

            if (i != result.path.size() - 1) {
                cout << " -> ";
            }
        }

        cout << endl;
        cout << "Distance: " << result.distance << " km" << endl;

    } else {

        cout << "No route found." << endl;
    }

    

    graph.saveToJSON("../data/campus.json");

    return 0;
}