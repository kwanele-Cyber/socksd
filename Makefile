flags=-O2 -Wall -std=c2x
ldflags=

.PHONY: all clean

all: clean socksd

socksd: socksd.o
	cc $(flags) $^ -o $@ $(ldflags)

socksd.o: socksd.c socksd.h
	cc $(flags) -c $<

clean:
	rm -f *.o socksd
