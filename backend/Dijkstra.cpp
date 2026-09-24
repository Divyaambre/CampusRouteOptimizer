#include "Dijkstra.h"

#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

RouteResult findShortestPath(
    const Graph& graph,
    const string& source,
    const string& destination
) {
    const auto& adj = graph.getGraph();

    unordered_map<string, int> distance;
    unordered_map<string, string> parent;

    // Initially, every location has infinite distance
    for (const auto& node : adj) {
        distance[node.first] = numeric_limits<int>::max();
    }

    // Distance from source to itself is 0
    distance[source] = 0;

    // Priority queue stores {distance, location}
    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;

    pq.push({0, source});

    while (!pq.empty()) {

        auto current = pq.top();
        pq.pop();

        int currentDistance = current.first;
        string currentNode = current.second;

        // Ignore outdated information
        if (currentDistance > distance[currentNode]) {
            continue;
        }

        // Destination reached
        if (currentNode == destination) {
            break;
        }

        // Check all roads connected to current location
        for (const auto& edge : adj.at(currentNode)) {

            // Ignore blocked roads
            if (edge.blocked) {
                continue;
            }

            string neighbor = edge.destination;
            int weight = edge.distance;

            int newDistance = currentDistance + weight;

            // Found a shorter route
            if (newDistance < distance[neighbor]) {

                distance[neighbor] = newDistance;
                parent[neighbor] = currentNode;

                pq.push({newDistance, neighbor});
            }
        }
    }

    // No route exists
    if (distance[destination] == numeric_limits<int>::max()) {
        return {{}, -1, false};
    }

    // Reconstruct the route
    vector<string> path;

    string current = destination;

    while (current != source) {
        path.push_back(current);
        current = parent[current];
    }

    path.push_back(source);

    reverse(path.begin(), path.end());

    return {path, distance[destination], true};
}