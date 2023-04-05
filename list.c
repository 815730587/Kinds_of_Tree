//
// Created by houti on 2021/10/23.
//
#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "WGraph.h"

typedef struct Node {
    char         *v;
    struct Node *next;
} Node;

Node *makeNode(char n[]) {
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->v=malloc(sizeof(char)*(strlen(n)+1));
    assert(new->v !=NULL);
    strcpy(new->v,n);
    new->v[strlen(n)] = '\0';
    new->next = NULL;
    return new;
}

List insertLL(List L, char n[]) {
    if(L==NULL){
        L=makeNode(n);
    } else{
        List newList=L;
        while (newList->next!=NULL){
            newList=newList->next;
        }
        newList->next=makeNode(n);
    }
    return L;
}

List deleteLL(List L, char n[]) {
    if (L == NULL) {
        return L;
    } else if (strcmp(L->v ,n)==0) {
        Node *p = L->next;
        free(L->v);
        free(L);
        return p;
    } else {
        L->next = deleteLL(L->next, n);
        return L;
    }
}


void showLL(List L) {
    if (L != NULL){
        printf("%s",L->v);
        while (L->next!=NULL){
            printf("-->%s",L->next->v);
            L=L->next;
        }
        printf("\n");
    }
}

void freeLL(List L) {
    if (L != NULL) {
        List cur=L;
        List next;
        while (cur!=NULL){
            next=cur->next;
            free(cur->v);
            free(cur);
            cur=next;
        }
    }
}

int stringStrcmp(List L,char n[]){
    if(L!=NULL){
        if(strcmp(L->v,n)<0)
            return 1;
        else
            return -1;
    } else{
        return 1;
    }
}

int compareWords(char a[],char b[]){
    int cont=0;
    if(strlen(a)==strlen(b)){
        for(int i=0;i<strlen(a);i++){
            if(*(a+i)!=*(b+i))
                cont++;
            if(cont>1)
                break;
        }
        if(cont<=1)
            return 1;
        else
            return 0;
    }else if(strlen(a)>strlen(b)&&strspn(b,a)+1==strlen(a)){
        int cur=-1;
        char c[strlen(a)+1];
        strcpy(c,a);
        for(int i=0;i<strlen(b);i++){
            if(*(a+i)!=*(b+i)){
                cur=i;
                break;
            }
        }
        if(cur==-1)
            cur=strlen(a);
        else
            cur=cur+1;
        for(int i=cur-1;i<strlen(a);i++)
            *(c+i)=*(c+i+1);
        *(c+strlen(c))='\0';
        int res=compareWords(c,b);
        if(res==1)
            return 1;
        else
            return 0;

    } else if(strlen(a)<strlen(b)&&strspn(a,b)+1==strlen(b)){
        int cur=-1;
        char c[strlen(b)+1];
        strcpy(c,b);
        for(int i=0;i<strlen(a);i++){
            if(*(a+i)!=*(b+i)){
                cur=i;
                break;
            }
        }
        if(cur==-1)
            cur=strlen(b);
        else
            cur=cur+1;
        for(int i=cur-1;i<strlen(b);i++)
            *(c+i)=*(c+i+1);
        *(c+strlen(c))='\0';
        int res=compareWords(a,c);
        if(res==1)
            return 1;
        else
            return 0;
    } else{
        return 0;
    }

}

Graph compareNeighbours(List L,Graph g,int n){
    if(L!=NULL){
        Edge edge;
        for(int i=0;i<n;i++){
            List cur=NULL;
            cur=L;
            int j=i+1;
            while (cur->next!=NULL){
                if(compareWords(L->v,cur->next->v)==1){
                    edge.v=i;
                    edge.w=j;
                    edge.weight=1;
                    insertEdge(g,edge);
                }
                j++;
                cur=cur->next;
            }
            L=L->next;
        }
    }
    return g;
}
//strspn包含字符串函数