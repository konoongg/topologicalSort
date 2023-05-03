typedef struct TOutput TOutput;
struct TOutput {
	long long Value;
	struct TOutput* Next;
};

int TopSort(char* associatedMatrix, int sizeGraph, TOutput** output);
int DFS(TOutput** output, char* colors, char* associatedMatrix, int sizeGraph, int index);
TOutput* AddValue(TOutput* output, int value);
void FreeOutput(TOutput* output);
