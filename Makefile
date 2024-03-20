# An epic makefile -> https://stackoverflow.com/a/48945536

DEPS     = -ledit -lm lval.c mpc.c
CC_FLAGS = -std=c99 -Wall -Werror

clean:
	rm -f hello_world parsing

hello_world:
	cc -std=c99 -Wall -Werror $@.c -o $@

parsing:
	cc $(CC_FLAGS) $(DEPS) $@.c -o $@

debug: parsing
	lldb --arch arm64 parsing

repl: clean parsing
	./parsing
