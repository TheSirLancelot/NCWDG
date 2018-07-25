all: bj

bj: BJ.o libBJLib.a
	gcc -lm -o BJ BJ.o -L. -lBJLib

BJ.o: BJ.c
	gcc -O -c BJ.c

BJLib.o: BJLib.c BJLib.h
	gcc -O -c BJLib.c

libBJLib.a: BJLib.o
	ar rcs libBJLib.a BJLib.o

.PHONY: clean

clean:
	rm -rf BJ *.o *.a *.gch
