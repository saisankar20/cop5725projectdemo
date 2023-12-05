#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

class Graph {
public:
    int vertices;
    vector<set<int> > adjList;

    Graph(int V) {
        vertices = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].insert(v);
        adjList[v].insert(u);
    }

    void motifPathBasedLocalClustering(int source, int motifSize) {
        vector<int> distances(vertices, -1);
        distances[source] = 0;

        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (set<int>::iterator it = adjList[current].begin(); it != adjList[current].end(); ++it) {
                int neighbor = *it;
                if (distances[neighbor] == -1) {
                    distances[neighbor] = distances[current] + 1;
                    q.push(neighbor);
                }
            }
        }

        vector<int> motifs(vertices, 0);

        for (int i = 0; i < vertices; ++i) {
            for (set<int>::iterator it = adjList[i].begin(); it != adjList[i].end(); ++it) {
                int neighbor = *it;
                if (distances[i] < distances[neighbor]) {
                    motifs[i]++;
                }
            }
        }


        cout << "Motif Counts for each node:\n";
        for (int i = 0; i < vertices; ++i) {
            cout << "Node " << i << ": " << motifs[i] << " motifs\n";
        }
    }
};

int main() {
    Graph graph(10);
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

    int sourceNode = 3;
    int motifSize = 9;

    graph.motifPathBasedLocalClustering(sourceNode, motifSize);

    return 0;
}
