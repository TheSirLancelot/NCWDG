all: section102

section102: myMain.o libmyLibrary.a
	gcc -lm -o section102 myMain.o -L. -lmyLibrary

myMain.o: myMain.c
	gcc -O -c myMain.c

myLibrary.o: myLibrary.c myLibrary.h
	gcc -O -c myLibrary.c

libmyLibrary.a: myLibrary.o
	ar rcs libmyLibrary.a myLibrary.o

.PHONY: clean

clean:
	rm -f section102 *.o *.a *.gch
