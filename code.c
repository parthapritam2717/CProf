/***********************************All the external include files please write here********************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include "prime.h"
#include "profiler.h"
#include "sys/times.h"
#include "sys/vtimes.h"

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
long double cpuPercentage,temp;// This will save the cpu usage percentage in the block
static int cores;//This variable will contain the number of cores the given system has which will be used while calculating the Cpu percentage usage
static clock_t lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;






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

/*To get the cpu usage*/
void init(){
    FILE* file;
    struct tms timeSample;
    char line[128];
    lastCPU = times(&timeSample);
    lastSysCPU = timeSample.tms_stime;
    lastUserCPU = timeSample.tms_utime;

    file = fopen("/proc/cpuinfo", "r");
    numProcessors = 0;
    while(fgets(line, 128, file) != NULL){
        if (strncmp(line, "processor", 9) == 0) numProcessors++;
    }
    fclose(file);
}

double getCurrentValue(){
    struct tms timeSample;
    clock_t now;
    double percent;
    now = times(&timeSample);
    if (now <= lastCPU || timeSample.tms_stime < lastSysCPU ||
        timeSample.tms_utime < lastUserCPU){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        percent = (timeSample.tms_stime - lastSysCPU) +
            (timeSample.tms_utime - lastUserCPU);
        percent /= (now - lastCPU);
        percent /= numProcessors;
        percent *= 100;
    }
    lastCPU = now;
    lastSysCPU = timeSample.tms_stime;
    lastUserCPU = timeSample.tms_utime;

    return percent;
}

int main(){
	init();	
	countCores(&cores);
	//temp=getCurrentValue();
	int n;	
	// First we should count the number of cores present in the system which will be used later 
	printf("The Number of cores is%d\n",cores);
	int c=0;
	int t;
	sf(t);
	while(t>0){
		sf(n);	
		int i;
		int array[n];
		for(i=0;i<n;++i){
			sf(array[i]);
		}
		int count=(count_prime(array,n));
		//cpuPercentage=getCurrentValue();
		printf("Cpu percentage=%Lf",getCurrentValue());		
		nl();	
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
