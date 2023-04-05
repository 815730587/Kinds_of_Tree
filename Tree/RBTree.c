//
// Created by houti on 2021/11/5.
//

// Red-Black Tree ADT implementation ... COMP9024 21T3

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "RBTree.h"

#define PRINT_COLOUR_RED   "\x1B[31m"
#define PRINT_COLOUR_RESET "\x1B[0m"

#define data(tree)   ((tree)->data)
#define left(tree)   ((tree)->left)
#define right(tree)  ((tree)->right)
#define colour(tree) ((tree)->colour)
#define NodeisRed(t) ((t) != NULL && (t)->colour == RED)

typedef enum {RED,BLACK} Colr;

typedef struct Node {
    Item data;
    Colr colour;
    Tree left, right;
} Node;

// create a new empty Tree
Tree newTree() {
    return NULL;
}

// make a new node containing data
Tree newNode(Item it) {
    Tree new = malloc(sizeof(Node));
    assert(new != NULL);
    data(new) = it;
    colour(new) = RED;
    left(new) = right(new) = NULL;
    return new;
}

Tree rotateRight(Tree);
Tree rotateLeft(Tree);
Tree insertRB(Tree tree,Item item,bool inRight){
    if (tree==NULL)
        return newNode(item);
    else if (item==data(tree))
        return tree;
    else{
        if(NodeisRed(right(tree)) && NodeisRed(left(tree)) ){
            colour(tree)=RED;
            colour(left(tree))=BLACK;
            colour(right(tree))=BLACK;
        }
        if(item>data(tree)){
            right(tree)=insertRB(right(tree),item,1);
            if(NodeisRed(tree) && NodeisRed(right(tree)) && inRight==0)
                tree=rotateLeft(tree);
            if(NodeisRed(right(tree))&&NodeisRed(right(right(tree)))){
                tree=rotateLeft(tree);
                colour(tree)=BLACK;
                colour(left(tree))=RED;
            }
        } else{
            left(tree)=insertRB(left(tree),item,0);
            if(NodeisRed(tree) && NodeisRed(left(tree)) && inRight==1)
                tree=rotateRight(tree);
            if(NodeisRed(left(tree)) && NodeisRed(left(left(tree)))){
                tree=rotateRight(tree);
                colour(tree)=BLACK;
                colour(right(tree))=RED;
            }
        }
    }

    return  tree;
}

// insert a new item into a tree
Tree TreeInsert(Tree tree, Item item) {

    tree=insertRB(tree,item,0);
    colour(tree)=BLACK;
    return tree;

}

// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
    if (t == NULL)
        return false;
    else if (it < data(t))
        return TreeSearch(left(t), it);
    else if (it > data(t))
        return TreeSearch(right(t), it);
    else                                 // it == data(t)
        return true;
}

Tree rotateRight(Tree n1) {
    if (n1 == NULL || left(n1) == NULL)
        return n1;
    Tree n2 = left(n1);
    left(n1) = right(n2);
    right(n2) = n1;
    return n2;
}

Tree rotateLeft(Tree n2) {
    if (n2 == NULL || right(n2) == NULL)
        return n2;
    Tree n1 = right(n2);
    right(n2) = left(n1);
    left(n1) = n2;
    return n1;
}

// free memory associated with Tree
void freeTree(Tree t) {
    if (t != NULL) {
        freeTree(left(t));
        freeTree(right(t));
        free(t);
    }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
    if (t != NULL) {
        showTreeR(right(t), depth+1);
        int i;
        for (i = 0; i < depth; i++)
            putchar('\t');            // TAB character
        if (NodeisRed(t))
            printf("%s%d%s\n", PRINT_COLOUR_RED, data(t), PRINT_COLOUR_RESET);
        else
            printf("%d\n", data(t));
        showTreeR(left(t), depth+1);
    }
}

void showTree(Tree t) {
    showTreeR(t, 0);
}




