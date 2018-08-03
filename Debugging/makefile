all: linkedList

linkedList: listMain.o libmyList.a
	gcc -lm -g -o linkedList listMain.o -L. -lmyList

listMain.o: listMain.c
	gcc -O -g -c listMain.c

myList.o: myList.c myList.h
	gcc -O -g -c myList.c

libmyList.a: myList.o
	ar rcs libmyList.a myList.o

.PHONY: clean

clean:
	rm -rf linkedList *.o *.a *.gch
