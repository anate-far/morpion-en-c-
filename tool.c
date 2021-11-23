#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "tool.h"



int stringToInt(char* str)
{
	int ok = 0;
	int result = 0;
	
	result = safeStringToInt(str, &ok); 
	
	if(ok == 0)
		printf("ERROR <stringToInt> : la chaine n'est pas numérique\n");

	return result; 

}


int safeStringToInt(char* str, int* ok)
{
	int result = 0;
	int i = 0; 
	
	if(str[0] == '-')
	{
		return -safeStringToInt(str + 1, ok);
	}
	
	*ok = 1; 

	if(str[0] == '\0')
	{
		*ok = 0;
		return 0; 
	}
	while(str[i] != '\0')
	{	
		if((str[i] < '0') || (str[i] > '9') )
		{		
			*ok = 0;
		}


		result *= 10; 
		result += (str[i] - 48); 
	       	i++;	
	}

	return result; 
}

int get_int (int minv, int maxv)
{
	int n;
	
	scanf("%d", &n);
	while ((n < minv) || (n > maxv))
	{
		printf("min = %d; max = %d. Recommencez : ", minv, maxv);
		scanf("%d", &n);
	}	

	return n; 	
}	


void intSwap(int* m, int *n)
{
	int tpm = *m;
	*m = *n;
	*n = tpm; 
}

void charSwap(char* m, char *n)
{
	char tpm = *m;
	*m = *n;
	*n = tpm;
}



void toolsMemoryInit(void)
{
	GLOBAL_ALLOC_MEMORY = 0;
}

void* toolsMalloc(int alloc)
{
	void* ptr = malloc(alloc);
	GLOBAL_ALLOC_MEMORY += alloc;
	return ptr; 
}

void toolsFree(void* ptr, int alloc)
{
	free(ptr);
	GLOBAL_ALLOC_MEMORY -= alloc;
}

void toolsMemoryCheckAtEndOfApp(void)
{
	if(GLOBAL_ALLOC_MEMORY != 0)
		printf("Ce programe a une ou des fuite de memoire\n%d d'octets non liberer\n", GLOBAL_ALLOC_MEMORY);
}	



float puiss_iter(float a, int b)
{
	float r = 1.f;
	int i;

	if(b < 0)
		return 1 / puiss_iter(a, -b);
	
	for(i = 1; i <= b ; i++)
		r *=a;

	return r; 	
}

float puiss_rec(float a, int b)
{
	if(b < 0)
		return 1 / puiss_rec(a, -b);

	else if(b == 0)
		return 1.0;
	else
	return a * puiss_rec(a, b-1);
}

float puiss_alex(float a, int b)
{
	if(b < 0)
		return 1 /puiss_alex(a, -b);
	else if(b == 0)
		return 1.0;	
	else if(b % 2 == 0)
		return puiss_alex(a*a, b / 2 );
	else
		return a * puiss_alex(a*a, (b-1)/2);
}

void int_normalize_and_warn(int *n, int minv,int maxv)
{
	if(*n < minv)
	{
		fprintf(stderr,"ERROR <int_normalize_and_warn> : La valeur %d  est trop petite\n", *n);
		*n = minv;
	}
	else if(*n > maxv)
	{
		fprintf(stderr,"ERROR <int_normalize_and_warn> : La valeur %d est trop grande\n", *n);
		*n = maxv;
	}

}

void int_normalize(int *n, int minv,int maxv)
{
	if(*n < minv)
		*n = minv;
	else if(*n > maxv)
		*n = maxv;

}


