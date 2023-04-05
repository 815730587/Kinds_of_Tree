//
// Created by houti on 2021/10/16
#include <stdio.h>
#include "WGraph.h"
#include <stdlib.h>

typedef struct degree {
    int follower;
    int followed;
    int u_vertix;
} Degree;

void showRankingFollower(Degree *follow, int size) {
    printf("Ranking by follower base:\n");
    for (int i = 0; i < size; i++) {
        printf("%d has %d follower(s) and follows %d user(s).", follow[i].u_vertix, follow[i].follower,
               follow[i].followed);
        if (i != size - 1)
            printf("\n");
    }

}

//j,m
int compar(Degree follow, Degree temp) {
    if (follow.follower - temp.follower > 0) {
        return -1;
    } else if (follow.follower - temp.follower < 0) {
        return 1;
    } else {
        if (follow.followed - temp.followed > 0) {
            return -1;
        } else if (follow.followed - temp.followed < 0) {
            return 1;
        } else {
            return follow.u_vertix - temp.u_vertix;
        }
    }

}

void insertsort(int nV, Degree *follow) {
    int m;
    for (m = 1; m < nV; m++) {
        int j = m - 1;
        Degree temp = follow[m];
        while (j >= 0 && compar(follow[j], temp) > 0) {
            follow[j + 1] = follow[j];
            j--;
        }
        follow[j + 1] = temp;
    }
    showRankingFollower(follow, nV);
}

void countDegreeAndSort(Graph g) {
    int nV = numOfVertices(g);
    Degree *follow = malloc(sizeof(struct degree) * nV);
    for (int i = 0; i < nV; i++) {
        follow[i].follower = 0;
        follow[i].followed = 0;
        follow[i].u_vertix = i;
    }
    for (int k = 0; k < nV; k++) {
        for (int n = 0; n < nV; n++) {
            if (adjacent(g, k, n) == 1) {
                follow[k].followed++;
                follow[n].follower++;
            }
        }
    }

    insertsort(nV, follow);
    free(follow);
}

int main(void) {
    int v = 0;
    Edge e;
    int user_e = 0;
    int follower_e = 0;
    Graph g;
    printf("Enter the number of users: ");
    if (scanf("%d", &v) == 1 && v != 0) {
        g = newGraph(v);
        while (1) {
            printf("Enter a user (follower): ");
            if (scanf("%d", &user_e) == 1) {
                e.v = user_e;
                printf("Enter a user (followed by %d): ", user_e);
                if (scanf("%d", &follower_e) == 1) {
                    e.w = follower_e;
                    e.weight = 1;
                    insertEdge(g, e);
                } else {
                    printf("Done.\n");
                    printf("\n");
                    break;
                }
            } else {
                printf("Done.\n");
                printf("\n");
                break;
            }
        }
        countDegreeAndSort(g);
        freeGraph(g);
    } else {
        printf("Done.\n");
    }
    return 0;
}
