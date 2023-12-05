#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
public:
    int vertices;
    vector<vector<int> > adjacencyList;

    Graph(int v) : vertices(v), adjacencyList(v) {}

    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    vector<int> getNodeRanking(int startNode) {
        vector<int> nodeRanking(vertices, -1); 
        queue<int> q;
        q.push(startNode);
        nodeRanking[startNode] = 3; 

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (vector<int>::iterator it = adjacencyList[current].begin(); it != adjacencyList[current].end(); ++it) {
                int neighbor = *it;
                if (nodeRanking[neighbor] == -1) {
                    nodeRanking[neighbor] = nodeRanking[current] + 1;
                    q.push(neighbor);
                }
            }
        }

        return nodeRanking;
    }
};

int main() {
    int vertices = 10;
    Graph graph(vertices);

    graph.addEdge(4, 1);
    graph.addEdge(4, 7);
    graph.addEdge(2, 4);
    graph.addEdge(4, 6);
    graph.addEdge(1, 5);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(2, 3);
    graph.addEdge(2, 5);
    graph.addEdge(7, 8);
    graph.addEdge(7, 6);
    graph.addEdge(8, 9);
    graph.addEdge(9, 6);
    graph.addEdge(8, 6);

    int startNode = 1;
    vector<int> nodeRanking = graph.getNodeRanking(startNode);

    
    cout << "Node Ranking:\n";
    for (int i = 0; i < vertices; ++i) {
        cout << "Node " << i << ": " << nodeRanking[i] << "\n";
    }

    return 0;
}
