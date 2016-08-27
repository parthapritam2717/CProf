obj= code.o profiler.o
code:$(obj)
	cc -o code -g $(obj) -lm
code.o:code.c profiler.h

profiler.o:profiler.c

.PHONY:clean
clean:
	rm -fr *.o *.*~
	
