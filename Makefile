all: client server

%: %.c
	cc -o $@ $<
