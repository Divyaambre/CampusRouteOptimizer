#include "httplib.h"
#include <iostream>
#include "Graph.h"
#include "Dijkstra.h"
using namespace std;

int main() {

    httplib::Server server;

    server.set_default_headers({
    {"Access-Control-Allow-Origin", "*"}
});

server.set_mount_point("/", "../frontend");

Graph graph;

graph.loadFromJSON("../data/campus.json");

server.Get("/locations", [&graph](const httplib::Request& req,
                                  httplib::Response& res) {

    auto locations = graph.getLocations();

    string result = "[";

    for (int i = 0; i < locations.size(); i++) {

        result += "\"" + locations[i] + "\"";

        if (i != locations.size() - 1) {
            result += ",";
        }
    }

    result += "]";

    res.set_content(result, "application/json");
});

server.Get("/route", [&graph](const httplib::Request& req,
                              httplib::Response& res) {

    // Check whether source and destination were provided
    if (!req.has_param("source") || !req.has_param("destination")) {

        res.status = 400;

        res.set_content(
            "{\"error\":\"Source and destination are required.\"}",
            "application/json"
        );

        return;
    }

    string source = req.get_param_value("source");
    string destination = req.get_param_value("destination");

    // Check whether locations exist
    if (!graph.hasLocation(source) ||
        !graph.hasLocation(destination)) {

        res.status = 404;

        res.set_content(
            "{\"error\":\"Invalid source or destination.\"}",
            "application/json"
        );

        return;
    }

    // Run Dijkstra
    RouteResult result =
        findShortestPath(graph, source, destination);

    // No route available
    if (!result.found) {

        res.status = 404;

        res.set_content(
            "{\"error\":\"No route found.\"}",
            "application/json"
        );

        return;
    }

    // Build JSON response
    string jsonResponse = "{";

    jsonResponse += "\"found\":true,";
    jsonResponse += "\"distance\":" +
                    to_string(result.distance) + ",";
    jsonResponse += "\"path\":[";

    for (int i = 0; i < result.path.size(); i++) {

        jsonResponse += "\"" + result.path[i] + "\"";

        if (i != result.path.size() - 1) {
            jsonResponse += ",";
        }
    }

    jsonResponse += "]}";

    res.set_content(
        jsonResponse,
        "application/json"
    );
});

server.Post("/block", [&graph](const httplib::Request& req,
                               httplib::Response& res) {

    if (!req.has_param("source") ||
        !req.has_param("destination")) {

        res.status = 400;

        res.set_content(
            "{\"error\":\"Source and destination are required.\"}",
            "application/json"
        );

        return;
    }

    string source = req.get_param_value("source");
    string destination = req.get_param_value("destination");

    if (!graph.hasLocation(source) ||
        !graph.hasLocation(destination)) {

        res.status = 404;

        res.set_content(
            "{\"error\":\"Invalid source or destination.\"}",
            "application/json"
        );

        return;
    }

    graph.blockRoad(source, destination);

    graph.saveToJSON("../data/campus.json");

    res.set_content(
        "{\"message\":\"Road blocked successfully.\"}",
        "application/json"
    );
});
server.Post("/unblock", [&graph](const httplib::Request& req,
                                 httplib::Response& res) {

    if (!req.has_param("source") ||
        !req.has_param("destination")) {

        res.status = 400;

        res.set_content(
            "{\"error\":\"Source and destination are required.\"}",
            "application/json"
        );

        return;
    }

    string source = req.get_param_value("source");
    string destination = req.get_param_value("destination");

    if (!graph.hasLocation(source) ||
        !graph.hasLocation(destination)) {

        res.status = 404;

        res.set_content(
            "{\"error\":\"Invalid source or destination.\"}",
            "application/json"
        );

        return;
    }

    graph.unblockRoad(source, destination);

    graph.saveToJSON("../data/campus.json");

    res.set_content(
        "{\"message\":\"Road unblocked successfully.\"}",
        "application/json"
    );
});

cout << "Server starting on http://localhost:8080" << endl;

server.listen("localhost", 8080);

return 0;

    
}