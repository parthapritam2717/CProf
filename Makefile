code:prime.o prime.h code.c
	cc -o code code.c prime.o -lm
prime.o:prime.c
	cc -c prime.c -lm


	
