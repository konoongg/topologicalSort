#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "func.h"

void FreeOutput (TOutput* output) {
	while (output) {
		TOutput* cur = output;
		output = output->Next;
		free(cur);
	}
}
TOutput* AddValue(TOutput* output, int value) {
	if (output) {
		TOutput* cur = (TOutput*)malloc(sizeof(TOutput));
		cur->Value = value + 1;
		cur->Next = output;
		output = cur;
	}
	else {
		output = calloc(1, sizeof(TOutput));
		output->Value = value + 1;
	}
	return output;
}

int DFS(TOutput** output, char* colors, char* associatedMatrix, int sizeGraph, int index) {
	colors[index] = 1;
	for (int i = 0; i < sizeGraph; ++i) {
		long long findIndex = (index * sizeGraph + i) / 8;
		int value = 1 << (index * sizeGraph + i) % 8;
		value &= associatedMatrix[findIndex];
		if (value != 0) {
			if (colors[i] == 0) {
				if (DFS(output, colors, associatedMatrix, sizeGraph, i) == 1) {
					return 1;
				}
			}
			else if (colors[i] == 1) {
				return 1;
			}
		}
	}
	*output = AddValue(*output, index);
	colors[index] = 2;
	return 0;
}

int TopSort(char* associatedMatrix, int sizeGraph, TOutput** output) {
	char* colors = (char*)calloc(sizeGraph, sizeof(char));
	for (int i = 0; i < sizeGraph; ++i) {
		if (colors[i] == 0) {
			if (DFS(output, colors, associatedMatrix, sizeGraph, i) == 1) {
				free(colors);
				return 1;
			}
		}
	}
	free(colors);
	return 0;
}

