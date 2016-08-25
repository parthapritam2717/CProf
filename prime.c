#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<limits.h>
#include<stdbool.h>

bool is_prime(int item){
	double x=sqrt((double)item);
	int i;
	for(i=2;i<(int)x;++i){
		if(item%i==0){
			return 0;
		}
		
	}
	return 1;

}
int count_prime(int *array){
	int i=0,j=0;
	for(i=0;i<sizeof(array)/sizeof(array[0]);++i){
		if(is_prime(array[i])){
			j++;
		}
	}
	return j;
}
