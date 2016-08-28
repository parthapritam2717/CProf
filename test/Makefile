obj= getCpuUsage.o profiler.o
getCpuUsage:$(obj)
	gcc -o getCpuUsage -g $(obj) -lm

getCpuUsage.o:getCpuUsage.c profiler.h
	gcc -g -c getCpuUsage.c
	
profiler.o:profiler.c
	gcc -g -c profiler.c

.PHONY:clean
clean:
	rm -fr *.o *.*~
	
