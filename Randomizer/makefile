all: Randomizer

Randomizer: rando.o librandoFunc.a
	gcc -lm -g -o Randomizer rando.o -L. -lrandoFunc

rando.o: rando.c
	gcc -O -g -c rando.c

randoFunc.o: randoFunc.c rando.h
	gcc -O -g -c randoFunc.c

librandoFunc.a: randoFunc.o
	ar rcs librandoFunc.a randoFunc.o

.PHONY: clean

clean:
	rm -rf Randomizer *.o *.a *.gch results.txt
