#include "Graph.h"
#include <queue>
#include <limits>
#include <unordered_set>

void Graph::AddEdge(int node1, int node2, int weight) {
    Edge edge{weight, true};
    adj_[node1][node2] = edge;
    adj_[node2][node1] = edge;
}

bool Graph::ToggleEdge(int node1, int node2) {
    if (adj_.count(node1) && adj_[node1].count(node2)) {
        adj_[node1][node2].is_open = !adj_[node1][node2].is_open;
        adj_[node2][node1].is_open = !adj_[node2][node1].is_open;
        return true;
    }
    return false;
}

std::string Graph::GetEdgeStatus(int node1, int node2) const {
    if (!adj_.count(node1) || !adj_.at(node1).count(node2)) {
        return "DNE";
    }
    return adj_.at(node1).at(node2).is_open ? "open" : "closed";
}

std::vector<std::pair<int, int>> Graph::GetNeighbors(int node) const {
    std::vector<std::pair<int, int>> neighbors;
    if (!adj_.count(node)) return neighbors;

    for (const auto& [neighbor, edge] : adj_.at(node)) {
        if (edge.is_open) {
            neighbors.emplace_back(neighbor, edge.weight);
        }
    }
    return neighbors;
}

bool Graph::IsConnected(int start, int end) const {
    if (start == end) return true;

    std::unordered_set<int> visited;
    std::queue<int> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        int curr = q.front(); q.pop();

        for (const auto& [neighbor, edge] : adj_.at(curr)) {
            if (edge.is_open && !visited.count(neighbor)) {
                if (neighbor == end) return true;
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    return false;
}

int Graph::GetShortestPath(int start, int end) const {
    if (!adj_.count(start) || !adj_.count(end)) return -1;

    std::unordered_map<int, int> dist;
    for (const auto& [node, _] : adj_) {
        dist[node] = std::numeric_limits<int>::max();
    }
    dist[start] = 0;

    using Pair = std::pair<int, int>; // (distance, node)
    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [curr_dist, curr_node] = pq.top(); pq.pop();

        if (curr_node == end) return curr_dist;

        for (const auto& [neighbor, edge] : adj_.at(curr_node)) {
            if (!edge.is_open) continue;

            int next_dist = curr_dist + edge.weight;
            if (next_dist < dist[neighbor]) {
                dist[neighbor] = next_dist;
                pq.emplace(next_dist, neighbor);
            }
        }
    }

    return -1; // unreachable
}

void Graph::Clear() {
    adj_.clear();
}
