/***********************************All the external include files please write here********************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include "prime.h"

/**************************************************Includes ends here*************************************************/

/*******************************************All #defines please include here ******************************************/
#define nl() printf("\n");
#define os() printf(" ");
#define sf(n) scanf("%d",&n);
#define pf(n) printf("%d",n);

/*********************************************#defines ends here******************************************************/

int main(){
	do{
		int n;
		sf(n);
		int *array=(int *)malloc(sizeof(int)*n);
		int i;
		for(i=0;i<n;++i){
			sf(array[i]);
		}
		// now the processing 
		pf(count_prime(array));
		nl();
	}while(n!=0);
	// will also send some packets but later
	
	return 0;
}
