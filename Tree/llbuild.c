//
// Created by houti on 2021/10/3.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct node{
    int data;
    struct node *next;
}NodeT;

NodeT *makeNode(int v){
    NodeT *newNode=malloc(sizeof(NodeT));
    assert(newNode!=NULL);
    newNode->data=v;
    newNode->next=NULL;
    return newNode;
}

NodeT *joinLL(NodeT *h,int v){
    if (h == NULL){
        return makeNode(v);
    } else{
        NodeT *lasthead=h;
        while(lasthead->next!=NULL){
            lasthead=lasthead->next;
        }
        lasthead->next=makeNode(v);

    }
    return h;
}
void freeLL(NodeT *list) {
    NodeT *p, *temp;
    p = list;
    while (p != NULL) {
        temp = p->next;
        free(p);
        p = temp;
    }
}
void showLL(NodeT *h){
    if (h!=NULL){
        NodeT *p=h;
        printf("%d",p->data);
        h=h->next;
        for (p = h; p != NULL; p = p->next) {
            printf("-->%d",p->data);
        }
    }
}



int main(void){
    NodeT *h=NULL;
    int data;
    while(1){
        printf("Enter a number: ");
        if(scanf("%d",&data)==1){
            h=joinLL(h,data);
        } else{
            break;
        }
    }
    printf("Done.");
    if(h!=NULL){
        printf(" List is ");
        showLL(h);
    }
    freeLL(h);
}