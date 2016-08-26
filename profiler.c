/***********************************All the external include files please write here********************************/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/times.h"
#include "sys/vtimes.h"
/**************************************************Includes ends here*************************************************/

/*******************************************All #defines please include here ******************************************/
#define nl() printf("\n");
#define os() printf(" ");
#define sf(n) scanf("%d",&n);
#define pf(n) printf("%d",n);

/*********************************************#defines ends here******************************************************/

/*********************************All global variables and structures should be defined here**************************/
static clock_t lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
typedef struct pState{
	// This structure stores the process present state from the /proc/PI/stat file 
	int pid;char comm[30];char state;int ppid;int pgrp;int session;int tty_nr;int tpgid;unsigned int flags;unsigned long minflt;unsigned long cminflt;unsigned long majflt;unsigned long cmajflt;unsigned long utime;unsigned long stime;long cutime;long cstime;
}pState;
	


/*********************************global variables ans structures defination ends here********************************/


/**********************************All the code should reside in this block*******************************************/

/*This function is to parse the memory usage*/

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

/*This function is to get the total virtual Memory used by the process*/
int getVirtualMemoryUsed(){ //Note: this value is in KB Please convert it into Bytes for better accuracy!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}


/*This function is to get the physical memory currently used by the process*/
int getPhysicalMemoryUsed(){ //Note: this value is in KB Please convert it into Bytes for better accuracy
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

/*This function returns the total amount of memory used by the program at a given time (heap+stack);*/
int getMemoryUsed(){//Note: this value is in KB Please convert it into Bytes for better accuracy
 FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

	    while (fgets(line, 128, file) != NULL){
			if (strncmp(line, "VmData:", 6) == 0){
			    result = parseLine(line);
			    break;
			}
	    }
	while (fgets(line, 128, file) != NULL){
		if (strncmp(line, "VmStk:", 6) == 0){
		result+=parseLine(line);
		break;
		}
	}
    fclose(file);
    return result;




}


/*we will calculate the cpu usage between two points or in a given block in units of ticks by calling this function twice at those points and
calculating the difference*/
/*The data we will be using from the /proc/PID/stat file are the stime and utime . stime is the time in which the process was in kernel mode and utime is the time in which the process was in user mode*/
unsigned long getCpuProcessTime(){
	FILE* file = fopen("/proc/self/stat", "r");
	char line[228];
 	fgets(line, 228, file);
	pState ps;
	sscanf(line,"%d,%s,%c,%d,%d,%d,%d,%d,%u,%lu,%lu,%lu,%lu,%lu,%lu,%ld,%ld",&ps.pid,ps.comm,&ps.state,&ps.ppid,&ps.pgrp,
&ps.session,&ps.tty_nr,&ps.tpgid,&ps.flags,&ps.minflt,&ps.cminflt,
&ps.majflt,&ps.cmajflt,&ps.utime,&ps.stime,&ps.cutime,&ps.cstime);
return (ps.utime+ps.stime);
}


/***********************************************Code Block over************************************************/

