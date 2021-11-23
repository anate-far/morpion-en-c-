#ifndef TOOL_H
#define TOOL_H

int GLOBAL_ALLOC_MEMORY;

typedef char* regstr;


int stringToInt(char* str); 

//ok vaut 1 si pas de caractère autre que 0 - 9
//ok vaut 0 sinon
int safeStringToInt(char* str, int* ok);
int get_int (int minv, int maxv);

void intSwap(int* m, int* n); 
void charSwap(char* m, char* n);

void toolsMemoryInit(void);
void* toolsMalloc(int alloc);
void toolsFree(void* ptr, int alloc);
void toolsMemoryCheckAtEndOfApp(void);


float puiss_iter(float a, int b);
float puiss_rec(float a, int b);
float puiss_alex(float a, int b);

void int_normalize_and_warn(int *n, int minv,int maxv);
void int_normalize(int *n, int minv,int maxv);

#endif
