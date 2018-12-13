all: main.o control.o headings.h
	gcc main.o control.o

main.o: main.c headings.h
	gcc -c -g main.c

control.o: control.c headings.h
	gcc -c -g control.c

run:
	./a.out

clean:
	rm *.o; rm *.*.gch; rm a.out; rm *.*#; rm -rf *.dSYM; rm *~
