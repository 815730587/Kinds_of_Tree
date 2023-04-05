//
// Created by houti on 2021/10/16.
//


#include "WGraph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
typedef struct GraphRep {
    int **edges;  // adjacency matrix storing positive weights
    // 0 if nodes not adjacent
    int nV;       // #vertices
    int nE;       // #edges
} GraphRep;

Graph newGraph(int V) {
    assert(V >= 0);
    int i;

    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nV = V;
    g->nE = 0;

    // allocate memory for each row
    g->edges = malloc(V * sizeof(int *));
    assert(g->edges != NULL);
    // allocate memory for each column and initialise with 0
    for (i = 0; i < V; i++) {
        g->edges[i] = calloc(V, sizeof(int));
        assert(g->edges[i] != NULL);
    }

    return g;
}

int numOfVertices(Graph g) {
    return g->nV;
}

// check if vertex is valid in a graph
int validV(Graph g, Vertex v) {
    return (g != NULL && v >= 0 && v < g->nV);
}

void insertEdge(Graph g, Edge e) {
    assert(g != NULL && validV(g, e.v) && validV(g, e.w));

    if (g->edges[e.v][e.w] == 0) {   // edge e not in graph
        g->edges[e.v][e.w] = e.weight;
        g->nE++;
    }
}

void removeEdge(Graph g, Edge e) {
    assert(g != NULL && validV(g, e.v) && validV(g, e.w));

    if (g->edges[e.v][e.w] != 0) {   // edge e in graph
        g->edges[e.v][e.w] = 0;
        g->nE--;
    }
}

int adjacent(Graph g, Vertex v, Vertex w) {
    assert(g != NULL && validV(g, v) && validV(g, w));

    return g->edges[v][w];
}

void showGraph(Graph g) {
    assert(g != NULL);
    int i, j;

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++)
        for (j = 0; j < g->nV; j++)
            if (g->edges[i][j] != 0)
                printf("Edge %d - %d: %d\n", i, j, g->edges[i][j]);
}

int findEnd(Graph g, Vertex v, int n) {
    for (int w = v + 1; w < n; w++) {
        if (g->edges[v][w] == 1) {
            return 0;
        }
    }
    return 1;
}
int countEnd(Graph g,int n){
    int count=0;
    for(int i=0;i<n;i++){
        if(findEnd(g,i,n)){
            count++;
        }
    }
    return count;

}
void showPath(int pre[],int n){
    printf("%d",pre[0]);
    for(int i=1;i<n;i++){
        printf("-->%d",pre[i]);
    }
}
void DFS_findPath(Graph g, int source, int point, bool visited[],int pre[]) {
    visited[source]=true;
    for(int i=0;i<point;i++){
        if(visited[i]==false && g->edges[source][i]==1){
            pre[i]=source;
            DFS_findPath(g,i,point,visited,pre);
        }
    }

}
int *sort(int max[], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1;j++){
            if(max[j]<max[j+1]){
                int temp=max[j];
                max[j]=max[j+1];
                max[j+1]=temp;
            }
        }
    }
    return max;

}
int singleOrSome(int max[],int n){
    if(n>1&& max[0]==max[1]){
        return 0;
    } else{
        return max[0];
    }

}
void setVisited(Graph g, int n, int point,WordNumber *wordNumber) {
    int pre[point];
    bool visited[point];
    for (int i = 0; i < point; i++) {
        pre[i]=0;
        visited[i] = false;
    }
    DFS_findPath(g,n,point,visited,pre);
    showEndPath(pre,point,n,g,wordNumber);
}
void showEndPath(const int pre[],int point, int source,Graph g,WordNumber *wordNumber){
    int end=countEnd(g,point);
    int array[end][point];
    int max[end];
    for(int i=0;i<end;i++){
        max[i]=1;
        for(int j=0;j<point;j++){
            array[i][j]=-1;
        }
    }
    int k=0;
    for(int i=source+1;i<point;i++){
        if(findEnd(g,i,point)==1){
            array[k][0]=i;
            int j=i;
            int m=1;
            while(1){
                array[k][m]=pre[j];
                if(pre[j]==source){
                    break;
                }
                m++;
                j=pre[j];
            }
            k++;
        }

    }

    for(int i=0;i<end;i++) {
        for (int j = 1; j < point; j++) {
            if(array[i][j]!=-1)
                max[i]++;
            else
                break;
        }
    }
    int *a=sort(max,end);
    int cur=singleOrSome(a,end);
    if(cur!=0){
        int ending=0;
        for(int i=0;i<end;i++) {
            int counter=1;
            for (int j = 1; j < point; j++) {
                if(array[i][j]!=-1)
                    counter++;
            }
            if(cur==counter)
                ending=i;
        }
        printf("Maximum sequence length: %d\n"
               "Maximal sequence(s):\n",cur);
        printf("%s", wordNumber[array[ending][cur-1]].n);
        for (int j = cur-2; j >=0; j--) {
            printf(" -> %s", wordNumber[array[ending][j]].n);
        }
        printf("\n");
    }else{
        cur=a[0];
        printf("Maximum sequence length: %d\n"
               "Maximal sequence(s):\n",cur);
        for(int i=0;i<end;i++) {
            int counter=1;
            for (int j = 1; j < point; j++) {
                if(array[i][j]!=-1)
                    counter++;
            }
            if(cur==counter){
                printf("%s", wordNumber[array[i][cur-1]].n);
                for (int j = cur-2; j >=0; j--) {
                    printf(" -> %s", wordNumber[array[i][j]].n);
                }
                printf("\n");
            }
        }

    }

}



void freeGraph(Graph g) {
    assert(g != NULL);
    int i;
    for (i = 0; i < g->nV; i++)
        free(g->edges[i]);
    free(g->edges);
    free(g);
}