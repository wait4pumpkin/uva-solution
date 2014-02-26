//
//  main.cpp
//  Q599
//
//  Created by Pumpkin Lee on 2/26/14.
//  Copyright (c) 2014 Pumpkin Lee. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

#define char2int(c) c - 'A'

struct Graph {
    Graph(int v): adjList(v) {
        nV = v;
    }
    
    void addEdge(int v, int w) {
        adjList[v].push_back(w);
        adjList[w].push_back(v);
    }
    
    vector<int>& adjTo(int v) {
        return adjList[v];
    }
    
    int nV;
    vector<vector<int>> adjList;
};

struct DFS {
    DFS(Graph *graph) {
        g = graph;
        isVisited = new bool[g->nV];
        fill(isVisited, isVisited + g->nV, false);
        nTree = 0;
        nAcorn = 0;
        
        for (int i=g->nV-1; i>=0; --i) {
            if (isVisited[i]) continue;
            int counter = 1;
            isVisited[i] = true;
            dfs(i, counter);
            if (counter > 1) ++nTree;
            else ++nAcorn;
        }
    }
    
    ~DFS(void) {
        delete [] isVisited;
    }
    
    void dfs(int v, int &counter) {
        vector<int> &adj = g->adjTo(v);
        for (int i=static_cast<int>(adj.size()-1); i>=0; --i) {
            int w = adj[i];
            if (!isVisited[w]) {
                isVisited[w] = true;
                ++counter;
                dfs(w, counter);
            }
        }
    }

    Graph *g;
    bool *isVisited;
    int nTree;
    int nAcorn;
};

int main(int argc, const char * argv[])
{
//    freopen("input.txt", "r", stdin);
    
    int nCases;
    scanf("%d", &nCases);
    getchar();
    
    while (nCases--) {
        vector<pair<int, int>> edges;
        int table[26];
        fill(table, table + 26, -1);
        int counter = 0;
        while (true) {
            char c = getchar();
            if (c == '*') break;
            
            int v = char2int(getchar());
            getchar();
            int w = char2int(getchar());
            getchar();
            getchar();
            
            if (table[v] < 0) table[v] = counter++;
            v = table[v];
            if (table[w] < 0) table[w] = counter++;
            w = table[w];
            edges.push_back(pair<int, int>(v, w));
        }
        
        while (getchar() != '\n') ;
        
        while (true) {
            int v = char2int(getchar());
            if (table[v] < 0) table[v] = counter++;
            if (getchar() == '\n') break;
        }

        Graph *g = new Graph(counter);
        for (int i=static_cast<int>(edges.size()-1); i>=0; --i) {
            pair<int, int> edge = edges[i];
            g->addEdge(edge.first, edge.second);
        }
        
        DFS dfs(g);
        printf("There are %d tree(s) and %d acorn(s).\n", dfs.nTree, dfs.nAcorn);
        
        delete g;
    }
    
    return 0;
}

// 类变量必须初始化
// 注意有些点不会出现在edge，用一个数组把字母映射为连续的整数
