# Campus Route Optimizer 🗺️

A Graph-Based Shortest Path and Dynamic Road Management System

Campus Route Optimizer is a web-based application that finds the shortest route between campus locations using Dijkstra’s shortest path algorithm. It represents campus roads as a weighted graph and allows users to block or unblock roads dynamically. When a road is blocked, the system calculates an alternative route automatically.

## 🚀 Live Demo

https://campus-route-optimizer.vercel.app/

## ✨ Features

- Shortest Path Calculation: Finds the shortest route between two locations using Dijkstra’s algorithm.
- Weighted Graph: Represents campus locations as vertices and roads as weighted edges.
- Dynamic Road Blocking: Blocks and unblocks roads based on user input.
- Automatic Rerouting: Calculates a new shortest route when a road becomes unavailable.
- Interactive Web Interface: Allows users to select locations and view route results.
- REST API: Connects the frontend with the C++ backend.
- JSON Data Storage: Loads and saves campus locations, road distances, and blocked-road status.
- Online Deployment: Frontend hosted on Vercel and backend hosted on Render.

## 🛠️ Technology Stack

| Component | Technologies |
|---|---|
| Backend | C++17 |
| Data Structures | Graph, adjacency list, unordered map, priority queue |
| Algorithm | Dijkstra’s shortest path |
| API | REST API using cpp-httplib |
| Frontend | HTML5, CSS3, JavaScript |
| Data Storage | JSON |
| Version Control | Git and GitHub |
| Deployment | Docker, Vercel, Render |

## 🏗️ System Architecture

The application follows a client-server architecture. The frontend sends requests to the backend through REST API endpoints. The backend processes the requests, updates the graph when required, and returns the results to the frontend.



Request Flow

1. The user selects a source and destination.
2. The frontend sends a request to the backend API.
3. The backend reads the campus graph and checks road availability.
4. Dijkstra’s algorithm calculates the shortest available route.
5. The backend returns the route and total distance.
6. The frontend displays the result to the user.

For road blocking, the backend updates the edge status, saves the updated data, and uses the modified graph for future route calculations.

🧠 Data Structures and Algorithm

# 1. Graph

The campus is represented as a weighted, undirected graph.

- Vertices: Campus locations such as Library, Canteen, CSE, and Admin.
- Edges: Roads connecting the locations.
- Weights: Road distances in kilometres.
- Blocked edges: Roads that cannot currently be used.

# 2. Adjacency List

The graph is stored using an adjacency list implemented with an `unordered_map` and a `vector` of edges.

Each edge stores:
- Destination location
- Distance
- Blocked status

This representation stores the roads connected to each location and supports efficient graph traversal.

# 3. Dijkstra’s Algorithm

Dijkstra’s algorithm finds the shortest path between a source and a destination when edge weights are non-negative.

The implementation uses a priority queue to process the location with the smallest known distance first. Blocked roads are skipped during route calculation.

Time complexity: \(O((V+E)\log V)\), using a priority queue and adjacency list, where \(V\) is the number of vertices and \(E\) is the number of edges.

Space complexity: \(O(V+E)\) for the graph and supporting data structures.

## 🗺️ Example Campus Graph

The following example represents the campus network used in the project.


flowchart 
    L["Library"]
    C["Canteen"]
    S["CSE"]
    A["Admin"]

    L ---|"2 km"| C
    L ---|"4 km"| S
    C ---|"1 km"| A
    S ---|"3 km"| A


# Example: Shortest Route

Normal condition

- Source: Library
- Destination: Admin
- Route: Library → Canteen → Admin
- Total distance: 3 km

When the Canteen–Admin road is blocked

- Route: Library → CSE → Admin
- Total distance: 7 km

When the road is unblocked, the original 3 km route becomes available again.

## 🔌 REST API Endpoints

The backend provides the following endpoints:

| Method | Endpoint | Purpose |
|---|---|---|
| `GET` | `/locations` | Returns available campus locations |
| `GET` | `/route?source=Library&destination=Admin` | Calculates the shortest route |
| `POST` | `/block?source=Canteen&destination=Admin` | Blocks a road |
| `POST` | `/unblock?source=Canteen&destination=Admin` | Unblocks a road |

### Example API Request

To calculate the shortest route from Library to Admin:

```http
GET /route?source=Library&destination=Admin
```

To block the road between Canteen and Admin:

```http
POST /block?source=Canteen&destination=Admin
```

The actual response format depends on the backend implementation.

## 📁 Project Structure

Folder/file	Purpose
backend/include/	Header files containing class and function declarations
backend/src/	C++ implementations, Dijkstra's algorithm, and server
backend/lib/	Third-party header libraries used by the project
frontend/css/	Website styling
frontend/js/	Frontend logic and API requests
frontend/assets/	Images, icons, and other static resources
data/	Campus locations, road distances, and blocked-road information
docs/	Architecture documentation and project screenshots
Dockerfile	Instructions for building and running the backend container
CMakeLists.txt	Build configuration for compiling the C++ project
README.md	Project overview, architecture diagram, features, and setup instructions


 # 💻 Running the Project Locally

### Prerequisites

- A C++17-compatible compiler
- Git
- A web browser
- The project’s included header libraries

# 1. Clone the Repository

git clone https://github.com/Divyaambre/CampusRouteOptimizer.git
cd CampusRouteOptimizer


# 2. Compile the Backend

From the project root, run:


g++ -std=c++17 backend/server.cpp backend/Graph.cpp backend/Dijkstra.cpp -o backend/server -pthread


# 3. Start the Backend

Run the executable from the project root so the relative data and frontend paths resolve correctly:

./backend/server

On Windows, run the generated executable using:

powershell
.\backend\server.exe

The server uses port `8080` by default when the `PORT` environment variable is not set.

### 4. Open the Frontend

Open `frontend/index.html` in your browser if your local setup supports serving the frontend this way. For the most reliable experience, serve the frontend over HTTP and make sure the frontend API URL points to your local backend, `http://localhost:8080`.

For local testing, update the `API_URL` value in `frontend/script.js` to:

javascript
const API_URL = "http://localhost:8080";

For the deployed frontend, use the deployed backend URL instead.

## 🌐 Deployment

The project is deployed using separate frontend and backend services.

- Frontend — Vercel: Hosts the HTML, CSS, and JavaScript interface.
- Backend — Render: Runs the C++ REST API in a Docker container.
- Repository — GitHub: Stores the source code and supports version control.


flowchart 
    A["GitHub Repository"] --> B["Vercel - Frontend"]
    A --> C["Render - Docker + C++ Backend"]
    B <--> D["User's Browser"]
    D <--> C

The frontend communicates with the deployed backend through HTTP requests. The backend listens on the host and port configured by the deployment environment.

## 🔮 Future Enhancements

Possible improvements include:

- Integrating a real campus map.
- Supporting larger campus networks.
- Adding route preferences such as travel time or accessibility.
- Replacing or extending JSON storage with a database.
- Adding administrator authentication and road-management controls.
- Supporting more advanced route visualisation.

## 🎯 Learning Outcomes

This project demonstrates the practical use of:

- Graphs and adjacency lists.
- Priority queues and shortest-path algorithms.
- C++ modular programming.
- REST API development and frontend-backend integration.
- JSON-based data handling.
- Git, GitHub, Docker, and cloud deployment.


Developed as a Data Structures project to demonstrate how graph algorithms can solve a practical campus navigation problem.

Campus Route Optimizer - Finding the shortest route across campus, even when roads are blocked.
