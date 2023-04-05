//
// Created by houti on 2021/10/16.
//

#ifndef CLIONECODE_WGRAPH_H
#define CLIONECODE_WGRAPH_H

#endif //CLIONECODE_WGRAPH_H

#include "list.h"
typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points) with a weight
typedef struct Edge {
    Vertex v;
    Vertex w;
    int    weight;
} Edge;
typedef struct words_n {
    char n[31];
} WordNumber;
Graph newGraph(int);
int   numOfVertices(Graph);
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
int   adjacent(Graph, Vertex, Vertex);  // returns weight, or 0 if not adjacent
void  showGraph(Graph);
void  freeGraph(Graph);


Graph compareNeighbours(List L,Graph g,int n);
int findEnd(Graph g,Vertex v,int n);
void DFS_findPath(Graph g,int source,int point,bool visited[],int pre[]);
void setVisited(Graph g,int n,int point,WordNumber *wordNumber);
void showEndPath(const int pre[],int point, int source,Graph g,WordNumber *wordNumber);
int countEnd(Graph g,int n);
void showPath(int pre[],int n);