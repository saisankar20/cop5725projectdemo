#include <iostream>
#include <vector>
#include <set>

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

    
    double MKI(int x, int y, int L, double epsilon) {
        double score = 0.0;

        for (int l = 1; l <= L; ++l) {
            
            double motifPathCount = calculateMotifPathCount(x, y, l);

            
            score += epsilon * (l - 1) * motifPathCount;
        }

        return score;
    }

    
    double MGD(int x, int y) {
        
        double shortestPathLength = calculateShortestPathLength(x, y);

        
        return 1.0 / shortestPathLength;
    }

private:
    
    double calculateMotifPathCount(int x, int y, int length) {
        
        return 1.0;
    }

    double calculateShortestPathLength(int x, int y) {
        
        return 1.0;
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

    int nodeX = 3;
    int nodeY = 9;
    int L = 3; 
    double epsilon = 0.8; 

    double MKIScore = graph.MKI(nodeX, nodeY, L, epsilon);
    double MGDScore = graph.MGD(nodeX, nodeY);

    cout << "Motif-path Katz Index score: " << MKIScore << endl;
    cout << "Motif-path Graph Distance score: " << MGDScore << endl;

    return 0;
}
