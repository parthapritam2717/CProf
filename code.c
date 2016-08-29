/***********************************All the external include files please write here********************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include "prime.h"
#include "profiler.h"
#include "sys/times.h"
#include "sys/vtimes.h"
#include <unistd.h>
#include <sys/types.h>
/**************************************************Includes ends here*************************************************/

/*******************************************All #defines please include here ******************************************/
#define nl() printf("\n");
#define os() printf(" ");
#define sf(n) scanf("%d",&n);
#define pf(n) printf("%d",n);

/*********************************************#defines ends here******************************************************/

/******************************All the global variables and structs should be declared here***************************/
unsigned long  userTime,systemTime;/* These variables are used to store the start user and kernel cpu time and calculate the cpu time we have spent on this block*/
double cpuUser,cpuSystem;// This will save the cpu usage percentage in the block
static int cores;//This variable will contain the number of cores the given system has which will be used while calculating the Cpu percentage usage
static struct pstat blockStart,blockEnd;// will store the process status at the beginiing of the block and at end of block
int errorStatus;// This variable will receive the error status while getting status for process


/***************************************Global variables declaration ends here***************************************/
bool is_prime(int item){	
	double y=(double)item;
	double x=sqrt(y);
	int i;
	int end=(int)x;
	if(item==1){
		return 0;
	}
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
	int c=0;
	int t;
	sf(t);		
	while(t>0){			
		sf(n);	
		int errorStatus=get_usage(getpid(),&blockStart);
		int i;
		int array[n];
		for(i=0;i<n;++i){
			sf(array[i]);
		}					
		int count=(count_prime(array,n));
		errorStatus=get_usage(getpid(),&blockEnd);
		calc_cpu_usage(&blockEnd,&blockStart,&userTime,&systemTime);
		printf("cpu usage=%lu\n",(userTime+systemTime));		
		printf("memory used=%d",getMemoryUsed());
		nl();		
		printf("%d num of primes=",c);
		pf(count);

		c++;				
		nl();
		nl();
		--t;
	}
	// will also send some packets but later
	
	
	return 0;
}
