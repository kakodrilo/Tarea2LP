
ejecucion: genetico
	valgrind ./genetico

genetico: genetico.o fun.o main.o
	gcc fun.o genetico.o main.o -o genetico

fun.o: fun.c fun.h
	gcc -c fun.c -Wall

genetico.o: genetico.c genetico.h
	gcc -c genetico.c -Wall

main.o: main.c
	gcc -c main.c -Wall

clear:
	rm genetico \
	fun.o genetico.o main.o
