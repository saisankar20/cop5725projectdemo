#include <iostream>
#include <vector>
#include <set>
#include <queue>

typedef std::vector<std::vector<int> > Graph;

struct MotifInstance {
    int node1, node2, node3;
};

void SMP(const Graph& graph, int tau, int seed, int& discoveredCount, std::set<int>& discoveredNodes, std::vector<MotifInstance>& motifInstances) {

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

    std::vector<int> distance(graph.size(), -1);
    std::queue<int> q;
    q.push(seed);
    distance[seed] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (size_t i = 0; i < graph[current].size(); ++i) {
            int neighbor = graph[current][i];
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }

    discoveredCount += motifInstances.size();
    for (size_t i = 0; i < motifInstances.size(); ++i) {
        const MotifInstance& motif = motifInstances[i];
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
