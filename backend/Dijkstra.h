#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"

struct RouteResult {
    vector<string> path;
    int distance;
    bool found;
};

RouteResult findShortestPath(
    const Graph& graph,
    const string& source,
    const string& destination
);

#endif