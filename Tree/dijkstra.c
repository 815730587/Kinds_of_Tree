//
// Created by houti on 2021/10/16.
//

// Starting code for Dijkstra's algorithm ... COMP9024 21T3

#include <stdio.h>
#include <stdbool.h>
#include "PQueue.h"

#define VERY_HIGH_VALUE 999999
void showPath(int dist[],int pred[],int source,int size){
    for(int s=0;s<size;s++){
        if(dist[s]==VERY_HIGH_VALUE){
            printf("%d: no path\n",s);
        } else{
            printf("%d: distance = %d, shortest path: %d",s,dist[s],source);
            if(s!=source && pred[s]!=source){
                int array[size-1];
                for(int k=0;k<size-1;k++)
                    array[k]=-2;
                array[0]=s;
                int j=1;
                while (1){
                    array[j]=pred[array[j-1]];
                    if(pred[array[j]]==source){
                        break;
                    }
                    j++;
                }
                for(int n=size-2;n>=0 ;n--){
                    if(array[n]!=-2 )
                        printf("-%d",array[n]);
                }
            } else if(s!=source){
                printf("-%d",s);
            }

            printf("\n");

        }
    }


}
void dijkstraSSSP(Graph g, Vertex source) {
    int  dist[MAX_NODES];
    int  pred[MAX_NODES];
    bool vSet[MAX_NODES];  // vSet[v] = true <=> v has not been processed
    int s,t;

    PQueueInit();
    int nV = numOfVertices(g);
    for (s = 0; s < nV; s++) {
        joinPQueue(s);
        dist[s] = VERY_HIGH_VALUE;
        pred[s] = -1;
        vSet[s] = true;
    }
    dist[source] = 0;
    /* NEEDS TO BE COMPLETED */
    while (1){
        if(PQueueIsEmpty()==false){
            s=leavePQueue(dist);
            t=0;
            while(t<nV){
                int weight=adjacent(g,s,t);
                if(weight>0 &&vSet[t]==true ){
                    if(dist[s]+weight<dist[t]){
                        dist[t]=dist[s]+weight;
                        pred[t]=s;
                    }
                }
                t++;
            }
            vSet[s]=false;
        } else{
            break;
        }
    }
    showPath(dist,pred,source,nV);


}

void reverseEdge(Edge *e) {
    Vertex temp = e->v;
    e->v = e->w;
    e->w = temp;
}

int main(void) {
    Edge e;
    int  n, source;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph g = newGraph(n);

    printf("Enter the source node: ");
    scanf("%d", &source);
    printf("Enter an edge (from): ");
    while (scanf("%d", &e.v) == 1) {
        printf("Enter an edge (to): ");
        scanf("%d", &e.w);
        printf("Enter the weight: ");
        scanf("%d", &e.weight);
        insertEdge(g, e);
        reverseEdge(&e);               // ensure to add edge in both directions
        insertEdge(g, e);
        printf("Enter an edge (from): ");
    }
    printf("Finished.\n");
    dijkstraSSSP(g, source);
    freeGraph(g);
    return 0;
}