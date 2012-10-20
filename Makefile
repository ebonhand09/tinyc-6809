# vim noexpandtab
CFLAGS:=-Wall -g

all: tinyc

tinyc: main.o
	$(CC) -o tinyc $^

clean:
	rm -f *~ *.o tinyc

