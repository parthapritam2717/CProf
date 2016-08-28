#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


int getMemoryUsed();// heap+stack done
int getVirtualMemoryUsed();//done
unsigned long getCpuProcessTime();//done
unsigned long long int getCpuTime();//done
int getPhysicalMemoryUsed();//done
void countCores(int *core);//done
long double getCpuPercent(unsigned long *,unsigned long long *,int );//done we will not use this to get cpu Percent as it gives wrong value sometimes


