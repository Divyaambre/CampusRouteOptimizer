#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Edge {
    string destination;
    int distance;
    bool blocked;
};

class Graph {

private:
    unordered_map<string, vector<Edge>> adj;

public:

    void addLocation(const string& location);

   void addRoad(
    const string& source,
    const string& destination,
    int distance,
    bool blocked = false
);

    void blockRoad(
        const string& source,
        const string& destination
    );

    void unblockRoad(
        const string& source,
        const string& destination
    );

    vector<string> getLocations() const;
    bool hasLocation(const string& location) const;
const unordered_map<string, vector<Edge>>& getGraph() const;

void loadFromJSON(const string& filename);
void saveToJSON(const string& filename) const;
};

#endif