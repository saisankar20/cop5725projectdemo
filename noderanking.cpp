#include <iostream>
#include <vector>
#include <queue>
#include <climits>

class MyGraph {
public:
    int totalVertices;
    std::vector<std::vector<int> > connections;

    MyGraph(int totalV) : totalVertices(totalV), connections(totalV) {}

    void createConnection(int a, int b) {
        connections[a].push_back(b);
        connections[b].push_back(a);
    }

    std::vector<int> getNodeLevels(int start) {
        std::vector<int> levels(totalVertices, INT_MAX);
        std::queue<int> q;
        q.push(start);
        levels[start] = 0;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (std::vector<int>::iterator it = connections[current].begin(); it != connections[current].end(); ++it) {
                int neighbor = *it;
                if (levels[neighbor] == INT_MAX) {
                    levels[neighbor] = levels[current] + 1;
                    q.push(neighbor);
                }
            }
        }

        return levels;
    }
};

int main() {
    const int totalNodes = 10;
    MyGraph myGraph(totalNodes);

    myGraph.createConnection(4, 1);
    myGraph.createConnection(4, 7);
    myGraph.createConnection(2, 4);
    myGraph.createConnection(4, 6);
    myGraph.createConnection(1, 5);
    myGraph.createConnection(1, 2);
    myGraph.createConnection(1, 3);
    myGraph.createConnection(2, 3);
    myGraph.createConnection(2, 5);
    myGraph.createConnection(7, 8);
    myGraph.createConnection(7, 6);
    myGraph.createConnection(8, 9);
    myGraph.createConnection(9, 6);
    myGraph.createConnection(8, 6);

    const int startNode = 1;
    std::vector<int> nodeLevels = myGraph.getNodeLevels(startNode);

    std::cout << "Node Levels:\n";
    for (int i = 0; i < totalNodes; ++i) {
        std::cout << "Node " << i << ": " << nodeLevels[i] << "\n";
    }

    return 0;
}
