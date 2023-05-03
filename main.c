#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "func.h"

int main(void) {
    int sizeGraph;
    if (scanf("%d", &sizeGraph) == -1) {
        printf("bad number of lines");
        return 0;
    }
    if (sizeGraph > 2000 || sizeGraph < 0) {
        printf("bad number of vertices");
        return 0;
    }
    long long countEdge;
    if (scanf("%lld", &countEdge) == -1) {
        printf("bad number of lines");
        return 0;
    }
    if (countEdge < 0 || countEdge > sizeGraph * (sizeGraph - 1) / 2) {
        printf("bad number of edges");
        return 0;
    }
    long long startPoint, endPoint;
    char* associatedMatrix = calloc(sizeGraph * sizeGraph / 8 + 1, sizeof(char));
    for (long long i = 0; i < countEdge; ++i) {
        if (scanf("%lld %lld", &startPoint, &endPoint) < 2) {
            free(associatedMatrix);
            printf("bad number of lines");
            return 0;
        }
        if (startPoint < 0 || startPoint > sizeGraph || endPoint < 0 || endPoint > sizeGraph) {
            free(associatedMatrix);
            printf("bad vertex");
            return 0;
        }
        long long index = ((startPoint - 1) * sizeGraph + (endPoint - 1)) / 8;
        associatedMatrix[index] |= 1 << ((startPoint - 1) * sizeGraph + (endPoint - 1)) % 8;
    }
    TOutput* output = NULL;
    if (TopSort(associatedMatrix, sizeGraph, &output) == 1) {
        printf("impossible to sort");
        free(associatedMatrix);
        FreeOutput(output);
        return 0;
    }
    free(associatedMatrix);
    while (output) {
        printf("%lld ", output->Value);
        TOutput* cur = output;
        output = output->Next;
        free(cur);
    }
    return 0;
}
