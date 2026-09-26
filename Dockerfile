FROM gcc:latest

WORKDIR /app

COPY backend/ ./backend/
COPY data/ ./data/

WORKDIR /app/backend

RUN g++ -std=c++17 server.cpp Graph.cpp Dijkstra.cpp -o server -pthread

CMD ["./server"]
