/***********************************All the external include files please write here********************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>


/**************************************************Includes ends here*************************************************/

/*******************************************All #defines please include here ******************************************/
#define nl() printf("\n");
#define os() printf(" ");
#define sf(n) scanf("%d",&n);
#define pf(n) printf("%d",n);

/*********************************************#defines ends here******************************************************/

/******************************All the global variables and structs should be declared here***************************/






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
		printf("%d num of primes=",c);
		pf(count);
		c++;
		nl();
		--t;
	}

	// will also send some packets but later

	return 0;
}
