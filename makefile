main_runner: main.c headings.h
	gcc main.c -o main_runner

control_runner: control.c headings.h
	gcc control.c -o control_runner

run_main:main_runner
	./main_runner

run_control:control_runner
	./control_runner

clean:
	rm *.o; rm *.*.gch; rm a.out; rm *.*#; rm -rf *.dSYM; rm *~
