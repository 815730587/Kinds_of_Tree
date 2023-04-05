//
// Created by houti on 2021/10/23.
//
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WGraph.h"
/*
 The algorithm complexity of task 1( For each word ω, compute and output all the words that could be used as the next word after ω in a word sequence) is O(m*n(n-1)) .

Explain:
To judge whether a word meets the meaning of the question, all words need to be compared with each other,the algorithm complexity is O(n(n-1)), and then each letter needs to be compared according to the length of the word m. The algorithm complexity is O(m), and the final algorithm The complexity is O(mn(n-1)).

The algorithm complexity of task 2 (Compute and output) is O(n).

Explain:
The worst case is that all words constitute the largest word sequence, so the algorithm complexity is O(n)
Assuming that the maximum word sequence length is x, the maximum number of word sequences is y.The complexity of the largest word sequence output algorithm is O(xy).
 */



void showWords(WordNumber *words, int n, Graph g) {
    for (int i = 0; i < n; i++) {
        printf("%s: ", words[i].n);
        for (int j = 0; j < n; j++) {
            if (adjacent(g, i, j) == 1)
                printf("%s ",words[j].n);
        }
        printf("\n");
    }
}


void distanceMax(Graph g,int point,int source,WordNumber *wordNumber){
    setVisited(g ,source,point,wordNumber);
}
int main(int argc, char *argv[]) {
    List list_word = NULL;
    int number;
    char words[32];
    char lowerWords[] = "abcdefghijklmnopqrstuvwxyz";
    printf("Enter a number: ");
    if (scanf("%d", &number) == 1 && number <= 100) {
        WordNumber *wordNumber = malloc(sizeof(struct words_n) * number);
        for (int i = 0; i < number; i++) {//O(n)
            printf("Enter a word: ");
            if (scanf("%s", words) == 1 && strspn(words, lowerWords) == strlen(words) && strlen(words) <= 31 &&
                stringStrcmp(list_word, words) > 0) {
                strcpy(wordNumber[i].n, words);
                list_word = insertLL(list_word, words);
            } else {
                printf("error");
                break;
            }
        }
        Graph g = newGraph(number);
        compareNeighbours(list_word, g, number);
        printf("\n");
        showWords(wordNumber, number, g);
        printf("\n");
        distanceMax(g,number,0,wordNumber);
        freeLL(list_word);
        freeGraph(g);
        free(wordNumber);
    }
    return 0;
}