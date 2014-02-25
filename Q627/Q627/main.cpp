//
//  main.cpp
//  Q627
//
//  Created by Pumpkin Lee on 2/25/14.
//  Copyright (c) 2014 Pumpkin Lee. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>
#include <set>
#include <algorithm>

using namespace std;

struct Graph {
    
    Graph(int v): adjList(v) {
        nV = v;
    }
    
    void addEdge(int v, int w) {
        adjList[v].push_back(w);
//        adjList[w].push_back(v);
    }
    
    vector<int>& adjTo(int v) {
        return adjList[v];
    }
    
    int nV;
    vector<vector<int>> adjList;
};

struct Dijkstra {
    
    Dijkstra(Graph *g, int start): edgeTo(g->nV) {
        this->start = start;
        distanceTo = new int[g->nV];
        fill(distanceTo, distanceTo + g->nV, INT32_MAX);
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(pair<int, int>(0, start));
        distanceTo[start] = 0;
        
        while (!pq.empty()) {
            int v = pq.top().second;
            int dist = pq.top().first;
            pq.pop();
            
            if (distanceTo[v] < dist) continue;
            vector<int> &adj = g->adjTo(v);
            for (int i=0; i<adj.size(); ++i) {
                int w = adj[i];
                if (distanceTo[w] < distanceTo[v] + 1) continue;
                
                if (distanceTo[w] > distanceTo[v] + 1) {
                    distanceTo[w] = distanceTo[v] + 1;
                    edgeTo[w].clear();
                }
                edgeTo[w].insert(v);
                pq.push(pair<int, int>(distanceTo[w], w));
            }
        }
    }
    
    vector<int> getPath(int end) {
        vector<int> result;
        result.push_back(end);
        if (distanceTo[end] < INT32_MAX) {
            while (true) {
                if (edgeTo[end].find(start) != edgeTo[end].end()) {
                    result.push_back(start);
                    break;
                } else {
                    end = *min_element(edgeTo[end].begin(), edgeTo[end].end());
                    result.push_back(end);
                }
            }
        }
        return result;
    }
    
    ~Dijkstra() {
        delete [] distanceTo;
    }
    
    int start;
    int *distanceTo;
    vector<set<int>> edgeTo;
};

int main(int argc, const char * argv[])
{
    while (true) {
        int nNode = 0;
        cin >> nNode;
        if (nNode <= 0) break;
        
        Graph *g = new Graph(nNode);
        for (int i=0; i<nNode; ++i) {
            int v;
            cin >> v;
            --v;
            
            cin.get();
            while (true) {
                char c = cin.get();
                if (c == '\n') {
                    break;
                } else {
                    cin.putback(c);
                }
                
                int w;
                cin >> w;
                --w;
                g->addEdge(v, w);
                if (cin.get() == '\n') break;
            }
        }
        
        cout << "-----" << endl;
        
        int nQuery;
        cin >> nQuery;
        for (int i=0; i<nQuery; ++i) {
            int start, end;
            cin >> start >> end;
            --start;
            --end;
            
            Dijkstra sp(g, start);
            vector<int> path = sp.getPath(end);
            if (path.size() <= 1) {
                cout << "connection impossible" << endl;
            } else {
                while (path.size() > 1) {
                    cout << path.back() + 1 << " ";
                    path.pop_back();
                }
                cout << path.back() << endl;
            }
        }
        
        delete g;
    }
    
    return 0;
}

// 注意题目给出的邻接条件是单向的
// Dijkstra求最短路径，回溯时选最小的前驱
// 实际上直接BFS即可
// 路径最后不可有空格
