clean:
	rm -f hello_world.o prompt.o

hello_world.o:
	cc -std=c99 -Wall hello_world.c -o hello_world.o

