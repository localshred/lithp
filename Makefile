clean:
	rm -f hello_world parsing

hello_world:
	cc -std=c99 -Wall -Werror $@.c -o $@

parsing:
	cc -std=c99 -Wall -Werror mpc.c $@.c -ledit -lm -o $@

debug: parsing
	lldb --arch arm64 parsing
