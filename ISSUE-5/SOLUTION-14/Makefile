.PHONY: clean
CC=$(CROSS_COMPILE)gcc
LDFLAGS=-lm
CFLAGS=-O2 $(LDFLAGS)

approximate-pi: approximate-pi.c ss.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm approximate-pi
