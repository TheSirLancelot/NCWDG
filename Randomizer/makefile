all: Randomizer

Randomizer: rando.o librandoFunc.a
	gcc -lm -o Randomizer rando.o -L. -lrandoFunc

rando.o: rando.c
	gcc -O -c rando.c

randoFunc.o: randoFunc.c rando.h
	gcc -O -c randoFunc.c

librandoFunc.a: randoFunc.o
	ar rcs librandoFunc.a randoFunc.o

.PHONY: clean

clean:
	rm -rf Randomizer *.o *.a *.gch results.txt
