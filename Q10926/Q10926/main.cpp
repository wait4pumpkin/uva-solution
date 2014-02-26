//
//  main.cpp
//  Q10926
//
//  Created by Pumpkin Lee on 2/26/14.
//  Copyright (c) 2014 Pumpkin Lee. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstdint>

using namespace std;

struct Graph {
    Graph(int v): adjList(v) {
        nV = v;
    }
    
    void addEdge(int v, int w) {
        adjList[v].push_back(w);
    }
    
    vector<int>& adjTo(int v) {
        return adjList[v];
    }
    
    int nV;
    vector<vector<int>> adjList;
};

struct DFS {
    DFS(Graph *graph, int v) {
        g = graph;
        isVisited = new bool[g->nV];
        fill(isVisited, isVisited + g->nV, false);
        total = 0;
        
        isVisited[v] = true;
        dfs(v);
    }
    
    ~DFS(void) {
        delete [] isVisited;
    }
    
    void dfs(int v) {
        vector<int> &adj = g->adjTo(v);
        for (int i=static_cast<int>(adj.size()-1); i>=0; --i) {
            int w = adj[i];
            if (!isVisited[w]) {
                isVisited[w] = true;
                ++total;
                dfs(w);
            }
        }
    }
    
    Graph *g;
    bool *isVisited;
    int total;
};

int main(int argc, const char * argv[])
{
//    freopen("input.txt", "r", stdin);
    
    while (true) {
        int n;
        scanf("%d", &n);
        if (n <= 0) break;
        
        Graph *g = new Graph(n);
        for (int v=0; v<n; ++v) {
            int nAdj;
            scanf("%d", &nAdj);
            for (int j=0; j<nAdj; ++j) {
                int w;
                scanf("%d", &w);
                g->addEdge(v, w - 1);
            }
        }
        
        int max = INT32_MIN;
        int result = -1;
        for (int i=0; i<n; ++i) {
            DFS dfs(g, i);
            if (dfs.total > max) {
                max = dfs.total;
                result = i;
            }
        }
        printf("%d\n", result + 1);
        
        delete g;
    }
    
    return 0;
}

// 很简单的题目，每个点DFS一次，看看哪个CC最大
// WA很久，磨了两个小时，发现是忘了注释freopen，欲哭无泪
