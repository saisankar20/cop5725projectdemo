#include <iostream>
#include <vector>
#include <queue>
#include <climits>

class Graph {
public:
    int vertices;
    std::vector<std::vector<int>> adjacencyList;

    Graph(int v) : vertices(v), adjacencyList(v) {}

    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    std::vector<int> calculateNodeRanks(int startNode) {
        std::vector<int> nodeRanks(vertices, INT_MAX);
        std::queue<int> q;
        q.push(startNode);
        nodeRanks[startNode] = 0;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : adjacencyList[current]) {
                if (nodeRanks[neighbor] == INT_MAX) {
                    nodeRanks[neighbor] = nodeRanks[current] + 1;
                    q.push(neighbor);
                }
            }
        }

        return nodeRanks;
    }
};

int main() {
    const int numVertices = 10;
    Graph graph(numVertices);

    graph.addEdge(4, 1);
    graph.addEdge(4, 7);
    graph.addEdge(2, 4);
    graph.addEdge(4, 6);
    graph.addEdge(1, 5);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 5);
    graph.addEdge(7, 8);
    graph.addEdge(7, 6);
    graph.addEdge(8, 9);
    graph.addEdge(9, 6);
    graph.addEdge(8, 6);

    const int startNode = 1;
    std::vector<int> nodeRanks = graph.calculateNodeRanks(startNode);

    std::cout << "Node Ranks:\n";
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Node " << i << ": " << nodeRanks[i] << "\n";
    }

    return 0;
}
