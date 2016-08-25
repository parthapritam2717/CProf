/***********************************All the external include files please write here********************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include "prime.h"
#include "profiler.h"

/**************************************************Includes ends here*************************************************/

/*******************************************All #defines please include here ******************************************/
#define nl() printf("\n");
#define os() printf(" ");
#define sf(n) scanf("%d",&n);
#define pf(n) printf("%d",n);

/*********************************************#defines ends here******************************************************/

/******************************All the global variables and structs should be declared here***************************/






/***************************************Global variables declaration ends here***************************************/

int main(){
	int n;
	do{
		sf(n);
		if(n==0)break;
		int *array=(int *)malloc(sizeof(int)*n);
		int i;
		for(i=0;i<n;++i){
			sf(array[i]);
		}
		
		// now the processing 
		int count=(count_prime(array,n));
		// dummpy check of the memory used 
		int vmem=(getVirtualMemoryUsed());
		vmem*=1024;
		printf("The virtual memory usage in Bytes is=");pf(vmem);nl();
		vmem=getPhysicalMemoryUsed();vmem*=1024;printf("The physical memory used in Bytes is=");pf(vmem);nl();
		printf("num of primes=");
		pf(count);
		nl();
		free(array);
	}while(n!=0);
	// will also send some packets but later
	
	return 0;
}
