#include <iostream>
#include <vector>
#include <set>
#include <queue>

typedef std::vector<std::vector<int>> Graph;

struct MotifInstance {
    int node1, node2, node3;
};

void findMotifs(const Graph &graph, int seed, std::vector<MotifInstance> &motifInstances) {
    for (size_t i = 0; i < graph[seed].size(); ++i) {
        int neighbor1 = graph[seed][i];
        for (size_t j = 0; j < graph[neighbor1].size(); ++j) {
            int neighbor2 = graph[neighbor1][j];
            for (size_t k = 0; k < graph[neighbor2].size(); ++k) {
                int neighbor3 = graph[neighbor2][k];
                if (neighbor3 == seed) {
                    MotifInstance motif = {seed, neighbor1, neighbor2};
                    motifInstances.push_back(motif);
                }
            }
        }
    }
}

void performTraversal(const Graph &graph, int start, std::vector<int> &distances) {
    std::queue<int> traversalQueue;
    std::set<int> visitedNodes;

    traversalQueue.push(start);
    visitedNodes.insert(start);
    distances[start] = 0;

    while (!traversalQueue.empty()) {
        int currentVertex = traversalQueue.front();
        traversalQueue.pop();

        for (size_t idx = 0; idx < graph[currentVertex].size(); ++idx) {
            int nextNeighbor = graph[currentVertex][idx];
            if (visitedNodes.find(nextNeighbor) == visitedNodes.end()) {
                distances[nextNeighbor] = distances[currentVertex] + 1;
                traversalQueue.push(nextNeighbor);
                visitedNodes.insert(nextNeighbor);
            }
        }
    }
}

void SMP(const Graph &graph, int tau, int seed, int &discoveredCount, std::set<int> &discoveredNodes, std::vector<MotifInstance> &motifInstances) {
    std::vector<int> distances(graph.size(), -1);
    performTraversal(graph, seed, distances);

    findMotifs(graph, seed, motifInstances);

    discoveredCount += motifInstances.size();
    for (size_t i = 0; i < motifInstances.size(); ++i) {
        const MotifInstance &motif = motifInstances[i];
        discoveredNodes.insert(motif.node1);
        discoveredNodes.insert(motif.node2);
        discoveredNodes.insert(motif.node3);
    }
}

int main() {
    Graph graph;

    graph.push_back(std::vector<int>());
    graph[0].push_back(1);
    graph[0].push_back(2);

    graph.push_back(std::vector<int>());
    graph[1].push_back(0);
    graph[1].push_back(2);
    graph[1].push_back(3);

    graph.push_back(std::vector<int>());
    graph[2].push_back(0);
    graph[2].push_back(1);
    graph[2].push_back(3);

    graph.push_back(std::vector<int>());
    graph[3].push_back(1);
    graph[3].push_back(2);

    int tau = 1;   // Tau parameter
    int k = 3;     // Desired size of the cluster
    int seed = 0;  // Seed node

    int discoveredCount = 0;
    std::set<int> discoveredNodes;
    std::vector<MotifInstance> motifInstances;

    // Run SMP until k nodes are discovered
    while (discoveredCount < k) {
        SMP(graph, tau, seed, discoveredCount, discoveredNodes, motifInstances);
    }

    // Output the discovered cluster
    std::cout << "Discovered Cluster: { ";
    for (std::set<int>::iterator it = discoveredNodes.begin(); it != discoveredNodes.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "}" << std::endl;

    return 0;
}
