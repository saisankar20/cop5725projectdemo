#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Graph {
    int V;
    std::vector<std::vector<int> > adjList;

    Graph(int vertices) : V(vertices), adjList(vertices) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
};

struct MotifInstance {
    std::vector<int> nodes;
};

bool isMotif(const std::vector<int>& nodes, const Graph& baseGraph) {
    
    if (nodes.size() == 3) {
        int u = nodes[0];
        int v = nodes[1];
        int w = nodes[2];


        return std::find(baseGraph.adjList[u].begin(), baseGraph.adjList[u].end(), v) != baseGraph.adjList[u].end() &&
               std::find(baseGraph.adjList[v].begin(), baseGraph.adjList[v].end(), w) != baseGraph.adjList[v].end() &&
               std::find(baseGraph.adjList[w].begin(), baseGraph.adjList[w].end(), u) != baseGraph.adjList[w].end();
    }

    return false;
}

bool checkIfMotifInstancesShouldConnect(const MotifInstance& instance1, const MotifInstance& instance2) {
        for (std::vector<int>::const_iterator it1 = instance1.nodes.begin(); it1 != instance1.nodes.end(); ++it1) {
        for (std::vector<int>::const_iterator it2 = instance2.nodes.begin(); it2 != instance2.nodes.end(); ++it2) {
            if (*it1 == *it2) {
                return true;
            }
        }
    }
    return false;
}

Graph constructHigherOrderGraph(const Graph& baseGraph, const std::vector<MotifInstance>& motifInstances) {
    Graph higherOrderGraph(motifInstances.size());

    for (int i = 0; i < motifInstances.size(); ++i) {
        for (int j = i + 1; j < motifInstances.size(); ++j) {
            bool shouldConnect = checkIfMotifInstancesShouldConnect(motifInstances[i], motifInstances[j]);

            if (shouldConnect) {
                higherOrderGraph.addEdge(i, j);
            }
        }
    }

    return higherOrderGraph;
}

std::vector<MotifInstance> findShortestMotifPath(const Graph& baseGraph, int s, int t, const std::vector<MotifInstance>& motifInstances) {
    std::queue<int> bfsQueue;
    std::vector<int> distance(baseGraph.V, -1);
    std::vector<int> parent(baseGraph.V, -1);

    bfsQueue.push(s);
    distance[s] = 0;

    while (!bfsQueue.empty()) {
        int u = bfsQueue.front();
        bfsQueue.pop();

        for (std::vector<int>::const_iterator it = baseGraph.adjList[u].begin(); it != baseGraph.adjList[u].end(); ++it) {
            int v = *it;
            if (distance[v] == -1) {
                distance[v] = distance[u] + 1;
                parent[v] = u;
                bfsQueue.push(v);
            }
        }
    }


    std::vector<MotifInstance> motifPath;
    int currentNode = t;

    while (currentNode != -1) {
        MotifInstance instance;
        instance.nodes.push_back(currentNode);
        motifPath.insert(motifPath.begin(), instance);  // Insert at the beginning to reverse the order
        currentNode = parent[currentNode];
    }

    return motifPath;
}

int main() {
   
    int numNodes = 10;
    Graph baseGraph(numNodes);


    baseGraph.addEdge(4, 1);
    baseGraph.addEdge(4, 7);
    baseGraph.addEdge(2, 4);
    baseGraph.addEdge(4, 6);
    baseGraph.addEdge(1, 5);
    baseGraph.addEdge(1, 2);
    baseGraph.addEdge(1, 3);
    baseGraph.addEdge(2, 4);
    baseGraph.addEdge(2, 3);
    baseGraph.addEdge(2, 5);
    baseGraph.addEdge(7, 8);
    baseGraph.addEdge(7, 6);
    baseGraph.addEdge(8, 9);
    baseGraph.addEdge(9, 6);
    baseGraph.addEdge(8, 6);

   
    std::vector<MotifInstance> motifInstances;
    for (int i = 0; i < numNodes - 2; ++i) {
        for (int j = i + 1; j < numNodes - 1; ++j) {
            for (int k = j + 1; k < numNodes; ++k) {
                std::vector<int> motifNodes;
                motifNodes.push_back(i);
                motifNodes.push_back(j);
                motifNodes.push_back(k);
                if (isMotif(motifNodes, baseGraph)) {
                    MotifInstance instance;
                    instance.nodes = motifNodes;
                    motifInstances.push_back(instance);
                }
            }
        }
    }

 
    int startNode = 1;  // Adjust based on your random values
    int endNode = 7;    // Adjust based on your random values

    Graph higherOrderGraph = constructHigherOrderGraph(baseGraph, motifInstances);

    std::vector<MotifInstance> shortestMotifPath = findShortestMotifPath(baseGraph, startNode, endNode, motifInstances);

   
    std::cout << "Base Graph:\n";
    for (int i = 0; i < numNodes; ++i) {
        std::cout << "Node " << i << ": ";
        for (std::vector<int>::const_iterator it = baseGraph.adjList[i].begin(); it != baseGraph.adjList[i].end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }

   
    std::cout << "\nMotif Instances:\n";
    for (std::vector<MotifInstance>::const_iterator it = motifInstances.begin(); it != motifInstances.end(); ++it) {
        std::cout << "Motif Instance: ";
        for (std::vector<int>::const_iterator nodeIt = it->nodes.begin(); nodeIt != it->nodes.end(); ++nodeIt) {
            std::cout << *nodeIt << " ";
        }
        std::cout << "\n";
    }


    std::cout << "\nShortest Motif-Path: ";
    for (std::vector<MotifInstance>::const_iterator it = shortestMotifPath.begin(); it != shortestMotifPath.end(); ++it) {
        for (std::vector<int>::const_iterator nodeIt = it->nodes.begin(); nodeIt != it->nodes.end(); ++nodeIt) {
            std::cout << *nodeIt << " ";
        }
        std::cout << "-> ";
    }
    std::cout << "End\n";

    return 0;
}
