//
// Created by houti on 2021/9/27.
//
#include <stdlib.h>
#include <stdio.h>

void password(int seed, int size, int pass[]) {
    srand(seed);
    for (int i = 0; i < size; i++) {
        pass[i] = rand() % 94 + 33;
    }
}

int main(int argc,char *argv[]) {
    int seed=atoi(argv[1]);
    int size=atoi(argv[2]);
    int p[size];
    password(seed, size, p);
    for (int i = 0; i < size; i++)
        printf("%c", p[i]);
    return 0;
}