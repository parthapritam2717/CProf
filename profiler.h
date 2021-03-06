#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


/*structure to save the state of the process from /proc will be used for cpu percentage calculation*/
struct pstat {
    long unsigned int utime_ticks;
    long int cutime_ticks;
    long unsigned int stime_ticks;
    long int cstime_ticks;
    long unsigned int vsize; // virtual memory size in bytes
    long unsigned int rss; //Resident  Set  Size in bytes

    long unsigned int cpu_total_time;
};



int getMemoryUsed();// heap+stack done
int getVirtualMemoryUsed();//done
unsigned long getCpuProcessTime();//done
unsigned long long int getCpuTime();//done
int getPhysicalMemoryUsed();//done
void countCores(int *core);//done
long double getCpuPercent(unsigned long *,unsigned long long *,int );//done we will not use this to get cpu Percent as it gives wrong value sometimes

/*These methods give the correct output for cpu usage*/
void calc_cpu_usage_pct(const struct pstat* cur_usage,
                        const struct pstat* prev_usage,
                        double* ucpu_usage, double* scpu_usage);

void calc_cpu_usage(const struct pstat* cur_usage,
                    const struct pstat* prev_usage,
                    long unsigned int* ucpu_usage,
                    long unsigned int* scpu_usage);
int get_usage(const pid_t pid, struct pstat* result);



