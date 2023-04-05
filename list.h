//
// Created by houti on 2021/10/23.
//

#ifndef CLIONECODE_LIST_H
#define CLIONECODE_LIST_H

#endif //CLIONECODE_LIST_H
#include <stdbool.h>
#include <string.h>
typedef struct Node *List;

List insertLL(List list, char n[]);
List deleteLL(List list, char n[]);
int stringStrcmp(List L,char n[]);
void freeLL(List L);
void showLL(List L);