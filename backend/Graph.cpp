#include <iostream>
#include "Graph.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

void Graph::addLocation(const string& location) {
    if (adj.find(location) == adj.end()) {
        adj[location] = {};
    }
}

void Graph::addRoad(
    const string& source,
    const string& destination,
    int distance,
    bool blocked
) {
    addLocation(source);
    addLocation(destination);

   adj[source].push_back({destination, distance, blocked});
   adj[destination].push_back({source, distance, blocked});
}

void Graph::blockRoad(
    const string& source,
    const string& destination
) {
    for (auto& edge : adj[source]) {
        if (edge.destination == destination) {
            edge.blocked = true;
        }
    }

    for (auto& edge : adj[destination]) {
        if (edge.destination == source) {
            edge.blocked = true;
        }
    }
}

void Graph::unblockRoad(
    const string& source,
    const string& destination
) {
    for (auto& edge : adj[source]) {
        if (edge.destination == destination) {
            edge.blocked = false;
        }
    }

    for (auto& edge : adj[destination]) {
        if (edge.destination == source) {
            edge.blocked = false;
        }
    }
}

void Graph::loadFromJSON(const string& filename) {

    ifstream file(filename);

    if (!file) {
    cerr << "Error: Could not open JSON file: "
         << filename << endl;
    return;
}

  json data;

try {
    file >> data;
}
catch (const json::parse_error& e) {
    cerr << "Error: Invalid JSON format: "
         << e.what() << endl;
    return;
}

for (const auto& road : data["roads"]) {

    if (!road.contains("source") ||
        !road.contains("destination") ||
        !road.contains("distance") ||
        !road.contains("blocked")) {

        cerr << "Error: Invalid road data in JSON file." << endl;
        continue;
    }

    string source = road["source"];
    string destination = road["destination"];
    int distance = road["distance"];
    bool blocked = road["blocked"];

    if (distance <= 0) {
        cerr << "Error: Invalid road distance between "
             << source << " and "
             << destination << endl;
        continue;
    }

    addRoad(source, destination, distance, blocked);
}
}


vector<string> Graph::getLocations() const {
    vector<string> locations;

    for (const auto& item : adj) {
        locations.push_back(item.first);
    }

    return locations;
}

bool Graph::hasLocation(const string& location) const {
    return adj.find(location) != adj.end();
}

const unordered_map<string, vector<Edge>>& Graph::getGraph() const {
    return adj;
}
void Graph::saveToJSON(const string& filename) const {

    json data;

    // Save locations
    for (const auto& item : adj) {
        data["locations"].push_back(item.first);
    }

    // Save roads
    for (const auto& item : adj) {

        string source = item.first;

        for (const auto& edge : item.second) {

            // Save each road only once
            if (source < edge.destination) {



    data["roads"].push_back({
        {"source", source},
        {"destination", edge.destination},
        {"distance", edge.distance},
        {"blocked", edge.blocked}
    });
}
    }

    // Write JSON to file
    ofstream file(filename);

    if (!file) {
        return;
    }

    file << data.dump(4);
}
}
