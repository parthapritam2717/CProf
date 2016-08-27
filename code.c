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
unsigned long  timeStart;/* These variables are used to store the start user and kernel cpu time and calculate the cpu time we have spent on this block*/
unsigned long long cpuTimeStart;/*These variables are used to get the total cpu time betwwen the desired blocks and we will then calculate the percentage usage of the cpu during that block*/
long double cpuPercentage;// This will save the cpu usage percentage in the block
int cores;//This variable will contain the number of cores the given system has which will be used while calculating the Cpu percentage usage






/***************************************Global variables declaration ends here***************************************/
bool is_prime(int item){	
	double y=(double)item;
	double x=sqrt(y);
	int i;
	int end=(int)x;
	for(i=2;i<(int)x;++i){
		if(item%i==0){
			return 0;
		}
		
	}
	return 1;

}
int count_prime(int *array,int s){
	int i=0,j=0;	
	for(i=0;i<s;++i){
		if(array[i]>=1 && is_prime(array[i])){
			j++;
		}
	}
	return j;
}

int main(){
	int n;
	countCores(&cores);// First we should count the number of cores present in the system which will be used later 
	printf("The Number of cores is%d\n",cores);
	int c=0;
	int t;
	sf(t);
	while(t>0){
		sf(n);	
		int i;
		int *array=(int *)malloc(sizeof(int)*n);
		for(i=0;i<n;++i){
			sf(array[i]);
		}
		int count=(count_prime(array,n));
		timeStart=getCpuProcessTime();
		cpuTimeStart=getCpuTime();
		cpuPercentage=getCpuPercent(&timeStart,&cpuTimeStart,cores);
		printf("%Lf",cpuPercentage);		
		nl();	
		//
		printf("memory used=%d",getMemoryUsed());
		nl();		
		printf("%d num of primes=",c);
		pf(count);
		c++;
		nl();		
		free(array);		
		nl();
		--t;
	}

	// will also send some packets but later
	
	return 0;
}
