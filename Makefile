clean:
	rm -f hello_world.o parsing.o

hello_world.o:
	cc -std=c99 -Wall hello_world.c -o hello_world.o

parsing.o:
	cc -std=c99 -Wall mpc.c parsing.c -ledit -lm -o parsing.o

debug: parsing.o
	lldb --arch arm64 parsing.o
