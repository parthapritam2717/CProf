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
typedef struct pState{
	// This structure stores the process present state from the /proc/PI/stat file 
	int pid;char comm[30];char state;int ppid;int pgrp;int session;int tty_nr;
	int tpgid;unsigned int flags;unsigned long minflt;unsigned long cminflt;unsigned long majflt;
	unsigned long cmajflt;unsigned long utime;unsigned long stime;long cutime;long cstime;
}pState;
struct pstat {
    long unsigned int utime_ticks;
    long int cutime_ticks;
    long unsigned int stime_ticks;
    long int cstime_ticks;
    long unsigned int vsize; // virtual memory size in bytes
    long unsigned int rss; //Resident  Set  Size in bytes

    long unsigned int cpu_total_time;
};




/*********************************global variables ans structures defination ends here********************************/


/**********************************All the code should reside in this block*******************************************/

/*This function is to parse*/
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
		if(file==NULL){
		printf("Error /proc/self/status File cannot be read !!\n");
		exit(-1);
		
	}
	    int result = -1;
	    char line[1000];

	    while (fgets(line, 1000, file) != NULL){
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
	if(file==NULL){
			printf("Error /proc/self/status File cannot be read !!\n");
			exit(-1);
		
		}
    int result = -1;
    char line[1000];

    while (fgets(line, 1000, file) != NULL){
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
	if(file==NULL){
		printf("Error /proc/self/status File cannot be read !!\n");
		exit(-1);
		
	}
    	int result = -1;
    	char line[1000];

	    while (fgets(line, 1000, file) != NULL){
			if (strncmp(line, "VmData:", 6) == 0){
			    result = parseLine(line);
			    break;
			}
	    }
	while (fgets(line, 1000, file) != NULL){
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
unsigned long int getCpuProcessTime(){
	FILE* file = fopen("/proc/self/stat", "r");	
	if(file!=NULL){
		char line[5000];
	 	fgets(line, 5000, file);
		pState ps;
		sscanf(line,"%d,%s,%c,%d,%d,%d,%d,%d,%u,%lu,%lu,%lu,%lu,%lu,%lu,%ld,%ld",&ps.pid,ps.comm,
		&ps.state,&ps.ppid,&ps.pgrp,&ps.session,&ps.tty_nr,&ps.tpgid,&ps.flags,&ps.minflt,&ps.cminflt,
		&ps.majflt,&ps.cmajflt,&ps.utime,&ps.stime,&ps.cutime,&ps.cstime);
		//printf("Processtime=%lu\n\n",(ps.utime+ps.stime));
		fclose(file);
		return (ps.utime+ps.stime);
	}
		else{
			
			printf("Error /proc/self/stat File cannot be read !!\n");
			exit(-1);
			
		
			
	}
	return 0;
}

/*This function gives the total cpu time for all the process*/
unsigned long long int getCpuTime(){
	FILE* file = fopen("/proc/stat", "r");
	if(file==NULL){
		printf("Error /proc/stat File cannot be read !!\n");
		exit(-1);
		
	}
	char line[5000];
 	fgets(line, 5000, file);	
	unsigned long long user,nice,system,idle,iowait,irq,softirq,steal,guest,guest_nice;	
	sscanf(line,"%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu",&user,&nice,&system,&idle,&iowait,&irq,&softirq,&steal,&guest,&guest_nice);
	/*printf("%llu\n",user);
	printf("%llu\n",nice);
	printf("%llu\n",system);
	printf("%llu\n",idle);
	printf("%llu\n",iowait);
	printf("%llu\n",irq);	
	printf("%llu\n",softirq);
	printf("%llu\n",steal);
	printf("%llu\n",guest);
	printf("%llu\n\n",guest_nice);*/
	fclose(file);
	return (user + nice + system + idle+iowait+irq+softirq+steal+guest+guest_nice);
}

/*This function will calculate the number of cores in the system which will be used for calculating the cpu percantage usage by the process*/
void countCores(int *core){
	FILE *file = fopen("/proc/cpuinfo", "r");
	*core = 0;
	char line[1000];
	while(fgets(line, 1000, file) != NULL){
		if (strncmp(line, "processor", 9) == 0) (*core)++;
	}
	fclose(file);
}


/*This function returns the percentage of cpu time our process used*/
long double getCpuPercent(unsigned long *process,unsigned long long *cpu,int cores){
	return ((long double)((long double)(*process)*100))/((long double)(*cpu)*cores);
}

/*
 * read /proc data into the passed struct pstat
 * returns 0 on success, -1 on error
*/
int get_usage(const pid_t pid, struct pstat* result) {
    //convert  pid to string
    char pid_s[20];
    snprintf(pid_s, sizeof(pid_s), "%d", pid);
    char stat_filepath[30] = "/proc/"; strncat(stat_filepath, pid_s,
            sizeof(stat_filepath) - strlen(stat_filepath) -1);
    strncat(stat_filepath, "/stat", sizeof(stat_filepath) -
            strlen(stat_filepath) -1);

    FILE *fpstat = fopen(stat_filepath, "r");
    if (fpstat == NULL) {
        perror("FOPEN ERROR ");
        return -1;
    }

    FILE *fstat = fopen("/proc/stat", "r");
    if (fstat == NULL) {
        perror("FOPEN ERROR ");
        fclose(fstat);
        return -1;
    }

    //read values from /proc/pid/stat
    bzero(result, sizeof(struct pstat));
    long int rss;
    if (fscanf(fpstat, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu"
                "%lu %ld %ld %*d %*d %*d %*d %*u %lu %ld",
                &result->utime_ticks, &result->stime_ticks,
                &result->cutime_ticks, &result->cstime_ticks, &result->vsize,
                &rss) == EOF) {
        fclose(fpstat);
        return -1;
    }
    fclose(fpstat);
    result->rss = rss * getpagesize();

    //read+calc cpu total time from /proc/stat
    long unsigned int cpu_time[10];
    bzero(cpu_time, sizeof(cpu_time));
    if (fscanf(fstat, "%*s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
                &cpu_time[0], &cpu_time[1], &cpu_time[2], &cpu_time[3],
                &cpu_time[4], &cpu_time[5], &cpu_time[6], &cpu_time[7],
                &cpu_time[8], &cpu_time[9]) == EOF) {
        fclose(fstat);
        return -1;
    }

    fclose(fstat);
	int i;
    for(i=0; i < 10;i++)
        result->cpu_total_time += cpu_time[i];

    return 0;
}

/*
* calculates the elapsed CPU usage between 2 measuring points. in percent
*/
void calc_cpu_usage_pct(const struct pstat* cur_usage,
                        const struct pstat* last_usage,
                        double* ucpu_usage, double* scpu_usage)
{
    const long unsigned int total_time_diff = cur_usage->cpu_total_time -
                                              last_usage->cpu_total_time;

    *ucpu_usage = 100 * (((cur_usage->utime_ticks + cur_usage->cutime_ticks)
                    - (last_usage->utime_ticks + last_usage->cutime_ticks))
                    / (double) total_time_diff);

    *scpu_usage = 100 * ((((cur_usage->stime_ticks + cur_usage->cstime_ticks)
                    - (last_usage->stime_ticks + last_usage->cstime_ticks))) /
                    (double) total_time_diff);
}

/*
* calculates the elapsed CPU usage between 2 measuring points in ticks
*/
void calc_cpu_usage(const struct pstat* cur_usage,
                    const struct pstat* last_usage,
                    long unsigned int* ucpu_usage,
                    long unsigned int* scpu_usage)
{

    *ucpu_usage = (cur_usage->utime_ticks + cur_usage->cutime_ticks) -
                  (last_usage->utime_ticks + last_usage->cutime_ticks);

    *scpu_usage = (cur_usage->stime_ticks + cur_usage->cstime_ticks) -
                  (last_usage->stime_ticks + last_usage->cstime_ticks);
}









/***********************************************Code Block over************************************************/

