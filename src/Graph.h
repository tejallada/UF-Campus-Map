#pragma once

#include <unordered_map>
#include <vector>
#include <utility>   // for std::pair

class Graph {
public:
    // Adds an undirected edge between node1 and node2
    void AddEdge(int node1, int node2, int weight);

    // Toggles the open/closed state of an edge
    bool ToggleEdge(int node1, int node2);

    // Checks the status of an edge
    std::string GetEdgeStatus(int node1, int node2) const;

    // Returns neighbors of a node (only open edges)
    std::vector<std::pair<int, int>> GetNeighbors(int node) const;

    // Check if there is a path between two nodes
    bool IsConnected(int start, int end) const;

    // Dijkstra: Shortest path time between two nodes
    int GetShortestPath(int start, int end) const;

    // Clears the entire graph
    void Clear();

private:
    struct Edge {
        int weight;
        bool is_open;
    };

    // Adjacency list: node -> (neighbor -> edge)
    std::unordered_map<int, std::unordered_map<int, Edge>> adj_;
};
