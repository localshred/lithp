clean:
	rm -f hello_world

hello_world:
	cc -std=c99 -Wall hello_world.c -o hello_world

debug: hello_world
	lldb --arch arm64 hello_world