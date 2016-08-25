obj= prime.o code.o profiler.o
code:$(obj)
	cc -o code $(obj) -lm
code.o:code.c prime.h profiler.h

profiler.o:profiler.c

prime.o:prime.c
	cc -c prime.c -lm

.PHONY:clean
clean:
	rm -fr *.o *.*~
	
