#include "fun.h"
#include <stdio.h>

typedef struct tNodo{
	void * dato;
	char tipo; // "i" = entero [0-9]; "c" = caracter [A-F]; "b"= bit [0|1]
}tNodo;

// Esta es una funcion de evaluacion de ejemplo. El nombre de la funcion debe ser fun. 
int fun(void* Nodo){
	return *((int*)(((tNodo*)(Nodo))->dato));
}
