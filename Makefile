all: client server

%: %.c
	gcc -o $@ $<
