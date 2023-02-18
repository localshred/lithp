clean:
	rm -f main

main:
	cc -std=c99 -Wall hello_world.c -o main

debug: main
	lldb --arch arm64 main