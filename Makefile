clean: hello_world
	rm hello_world

hello_world:
	cc -std=c99 -Wall hello_world.c -o hello_world