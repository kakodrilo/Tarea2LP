#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* --- include de los headers utilizados --- */

#include "genetico.h"
#include "fun.h"

/*------------------------------------------*/


//Esta variable se utiliza en la función generarSolucion para asegurar que los valores
// entregados por la función rand() vayan variando.
int flag=0;


/* --- Definicion de tipo Lista a utilizar ---*/

/* ----- Nodos ----- */
typedef struct tNodo{
	void * dato;
	char tipo; // "i" = entero [0-9]; "c" = caracter [A-F]; "b"= bit [0|1]
	struct tNodo* next;
}tNodo;

/* ----- Lista ----- */
typedef struct Lista{
	tNodo* cabeza;
	tNodo* cola;
	tNodo* actual;
	int largo;
}List;

/*----------------------------------------------------------------*/

 /* --- Definicion de funciones ---*/


/*****
*
void * generarSolucion
******
*
Crea una lista enlazada de largo n compuesta por
elementos al azar, y devuelve el puntero correspondiente
******
*
Input:
*
int largo: cantidad de elementos que tendrá la lista a crear.
*
.......
******
*
Returns:
*
void*, puntero a la lista creada.
*****/

void* generarSolucion(int largo){
	if(flag==0){
		srand(time(NULL));	//Aquí se asegura que los valores entregados por la función
							//rand() vayan variando.
		flag=1;				//Esto indica que debe ejecutarse una sola vez dentro de la ejecucion.
	}

	List * pl;

	pl = (List *)malloc(sizeof(List));
	if (pl == NULL) {
		printf("Error al iniciar lista\n");
		exit(1);
	}

	pl->cabeza = pl->cola = pl-> actual = NULL;
	pl->largo = 0;

	for (int i = 0; i < largo; i++) {
		int e;

		tNodo *temp = (tNodo*)malloc(sizeof(tNodo));

		temp->dato = malloc(sizeof(int));
		e=rand()%3;
		if (e==0) {
			*((int *)(temp->dato)) = rand()%10;
			temp->tipo = 'i';
		}
		else if (e==1) {
			*((int *)(temp->dato)) = 65+(rand()%(71-65));
			temp->tipo = 'c';
		}
		else{
			*((int*)(temp->dato)) = rand()%2;
			temp->tipo = 'b';
		}

		temp->next= NULL;
		if (pl->largo!=0) {
			pl->cola->next = temp;
			pl->cola = temp;
		}
		else{
			pl->cola = pl->cabeza = temp;
		}
		pl->largo++;
	}
	return (void*)pl;
}


/*****
*
void borrar
******
*
Libera el espacio de memoria asignado a una lista, vale decir, borra la lista.
******
*
Input:
*
void * Lista: puntero a la lista que se borrará.
*
.......
******
*
Returns:
*
void, no tiene retorno.
*****/

void borrar(void* Lista){
	List *lista = Lista;
	for (int i = 0; i < lista->largo; i++) {
		lista->actual=lista->cabeza->next;
		free((void *)lista->cabeza->dato);
		free((void *)lista->cabeza);
		lista->cabeza=lista->actual;
	}
	free((void*)Lista);
}


/*****
*
void imprimirSolucion
******
*
Muestra por consola los elementos de la lista en el formato (dato,tipo).
******
*
Input:
*
void * Lista: puntero a la lista que contine los elementos a imprimir.
*
.......
******
*
Returns:
*
void, no tiene retorno.
*****/

void imprimirSolucion(void * Lista){
	List *lista = Lista;
	for (lista->actual = lista->cabeza; lista->actual!=NULL; lista->actual = lista->actual->next) {
		if (lista->actual->tipo=='i') {
			printf("(%d,%c)\n",*((int*)(lista->actual->dato)),lista->actual->tipo);
		}
		else if (lista->actual->tipo=='c') {
			printf("(%c,%c)\n",*((char*)(lista->actual->dato)),lista->actual->tipo);
		}
		else {
			printf("(%d,%c)\n",*((int*)(lista->actual->dato)),lista->actual->tipo);
		}

	}
}


/*****
*
void * copiar
******
*
Crea una copia de la lista ingresada y retorna el puntero correspondiente.
******
*
Input:
*
void * Lista: puntero a la lista que se desea copiar.
*
.......
******
*
Returns:
*
void *, puntero que apunta a la nueva lista.
*****/

void* copiar(void* Lista){
	List * lista2;
	List * lista = Lista;

	lista2 = (List *)malloc(sizeof(List));
	lista2->cabeza = lista2->cola = lista2->actual = NULL;
	lista2->largo = 0;

	lista->actual = lista->cabeza;
	for (int i = 0; i < lista->largo; i++) {

		tNodo *copia = (tNodo*)malloc(sizeof(tNodo));
		copia->dato = malloc(sizeof(int));
		*((int*)(copia->dato))=*((int*)(lista->actual->dato));
		copia->tipo=lista->actual->tipo;
		copia->next= NULL;
		if (lista2->largo!=0) {
			lista2->cola->next = copia;
			lista2->cola = copia;
		}
		else{
			lista2->cola = lista2->cabeza = copia;
		}
		lista->actual = lista->actual->next;
		lista2->largo++;

	}
	return (void *)lista2;

}


/*****
*
void  cruceMedio
******
*
Intercambia la seccion de los primeros n/2 elementos de la Lista 1 por los de la lista 2.
En caso de ser de largo impar, n/2 se debe truncar. Ambas listas serán del mismo largo.
******
*
Input:
*
void * Lista1: puntero a una de las listas que se le aplicará el cruce.
void * Lista2: puntero a una de las listas que se le aplicará el cruce.
*
.......
******
*
Returns:
*
void, no tiene retorno.
*****/

void cruceMedio(void* Lista1,void* Lista2) {
	List* lista1 = Lista1, *lista2 = Lista2;
	tNodo *aux = lista1->cabeza;
	lista1->cabeza = lista2->cabeza;
	lista2->cabeza = aux;
	lista1->actual=lista1->cabeza;
	lista2->actual=lista2->cabeza;
	for (int i = 1; i < (lista1->largo)/2; i++) {
		lista1->actual = lista1->actual->next;
		lista2->actual = lista2->actual->next;
	}
	aux = lista1->actual->next;
	lista1->actual->next = lista2->actual->next;
	lista2->actual->next = aux;
}


/*****
*
void  cruceIntercalado
******
*
Intercambia los elementos que se encuentren en posiciones pares entre las listas.
La primera posicion se considera como par (0).
******
*
Input:
*
void * Lista1: puntero a una de las listas que se le aplicará el cruce.
void * Lista2: puntero a una de las listas que se le aplicará el cruce.
*
.......
******
*
Returns:
*
void, no tiene retorno.
*****/

void  cruceIntercalado(void* Lista1, void* Lista2) {
	List *lista1 = Lista1, *lista2 = Lista2;
	int cont = lista1->largo;
	tNodo *aux;
	aux = lista1->cabeza;
	lista1->cabeza = lista2->cabeza;
	lista2->cabeza = aux;

	lista1->actual = lista1->cabeza;
	lista2->actual = lista2->cabeza;

	if((lista1->largo)%2!=0) cont = cont -1;

	for (int i = 1; i < lista1->largo ; i++) {
		aux = lista1->actual->next;
		lista1->actual->next = lista2->actual->next;
		lista2->actual->next = aux;
		lista1->actual = lista1->actual->next;
		lista2->actual = lista2->actual->next;
	}

}


/*****
*
void  mutacionRand
******
*
Selecciona un elemento aleatoriamente y lo reemplaza por otro valor al azar
(que puede ser del mismo o distinto tipo). Siempre se producirá un cambio.
******
*
Input:
*
void * Lista: puntero a la lista en la que se aplicará la mutacion.

*
.......
******
*
Returns:
*
void, no tiene retorno.
*****/

void mutacionRand(void * Lista){
	List *lista = Lista;
	lista->actual = lista->cabeza;

	int pos = rand()%((lista->largo));

	for (int i = 0; i < pos; i++) {
		lista->actual = lista->actual->next;
	}

	int va = *((int*)(lista->actual->dato));
	char ta = lista->actual->tipo;
	int e = rand()%3;

	if (e==0) {
		*((int*)(lista->actual->dato)) = rand()%10;
		lista->actual->tipo = 'i';
	}
	else if (e == 1) {
		*((int*)(lista->actual->dato)) = 65 +(rand()%(71-65));
		lista->actual->tipo = 'c';
	}
	else{
		*((int*)(lista->actual->dato)) = rand()%2;
		lista->actual->tipo = 'b';
	}

	if (*((int*)(lista->actual->dato)) == va && lista->actual->tipo == ta){
		mutacionRand(Lista);
	}
}


/*****
*
void  mutacionTipo
******
*
Selecciona un elemento aleatoriamente y lo reemplaza por otro valor al azar
del mismo tipo. En cualquier caso se cambia el valor del dato.
******
*
Input:
*
void * Lista: puntero a la lista en la que se aplicará la mutacion.

*
.......
******
*
Returns:
*
void, no tiene retorno.
*****/

void mutacionTipo(void * Lista){
	List *lista = Lista;
	lista->actual = lista->cabeza;

	int pos = rand()%((lista->largo));

	for (int i = 0; i < pos; i++) {
		lista->actual = lista->actual->next;
	}

	int va = *((int*)(lista->actual->dato));

	if (lista->actual->tipo=='i') {
		*((int*)(lista->actual->dato)) = rand()%10;
	}
	else if (lista->actual->tipo == 'c') {
		*((int*)(lista->actual->dato)) = 65 +(rand()%(71-65));
	}
	else{
		*((int*)(lista->actual->dato)) = abs(*((int*)(lista->actual->dato))-1);
	}

	if (*((int*)(lista->actual->dato)) == va) {
		mutacionTipo(Lista);
	}
}


/*****
*
int evaluacionLista
******
*
Aplica una funcion de evaluacion sobre cada uno de los nodos, la cual evalua
la calidad de este ultimo. Retorna la suma de todos los puntajes obtenidos.
******
*
Input:
*
int (*fun)(void*): Puntero a la funcion que evalua la calidad del nodo.
void * Lista: puntero a la lista que se desea evaluar.

*
.......
******
*
Returns:
*
int, suma total de la evaluacion de todos los nodos de la lista.
*****/

int evaluacionLista(int (*fun)(void*), void* Lista){
	int suma = 0;
	List* lista = Lista;
	lista->actual = lista->cabeza;

	for (int i = 0; i<lista->largo;i++){
		suma += fun((void*)(lista->actual));
		lista->actual = lista->actual->next;
	}
	return suma;
}


/*****
*
void copiarSinCrear
******
*
Se reemplazan los elemento de cada nodo de la ListaCopia, por los respectivos de la lista Lista.
Esta funcion hace lo mismo que la funcion copia, pero sin asignacion de memoria, por lo que recibe dos punteros,
uno a la lista que se desea copiar, y otro a la lista en la que se reemplazaran los datos.
******
*
Input:
*
void * Lista: puntero a la lista que se desea copiar.
void * ListaCopia : puntaero a la lista en la que se reemplazaran los elementos anteriores de
					cada nodo, por los de la lista Lista.

*
.......
******
*
Returns:
*
void, no tiene retornos.
*****/

void copiarSinCrear(void* Lista,void* ListaCopia){
	List *lista = Lista,*listaCopia = ListaCopia;

	listaCopia->largo = 0;
	listaCopia->actual = listaCopia->cabeza;
	lista->actual = lista->cabeza;

	for (int i = 0; i < lista->largo; i++) {
		*((int*)(listaCopia->actual->dato))=*((int*)(lista->actual->dato));
		listaCopia->actual->tipo=lista->actual->tipo;
		lista->actual = lista->actual->next;
		listaCopia->actual = listaCopia->actual->next;
		listaCopia->largo++;
	}
}


/*****
*
void genetico
******
*
Crea 2 listas del mismo tamaño (listas padre), a las cuale se le aplica el siguiente algoritmo
tantas veces como indica la variable iteraciones:
	- Evaluar la calidad de cada lista padre
	- Aplicar el cruce entre ambas listas padre para obtener dos listas hijas.
	  Se evaluan las cutro listas, si ambas hijas superan a sus respectivos padres,
	  entonces las hijas reemplazan a los padres.
	- Aplicar mutacion sobre las hijas obtenidas del cruce y se evaluan.
	  Si alguna de las hijas supera a respectivo padre, entonces lo reemplaza.
******
*
Input:
*
void (*muta)(void*): puntero a una funcion de mutacion (Rand o Tipo).
void (*cruce)(void*,void*): puntero a una funcion de cruce (Medio o Intercalado).
int n: indica la cantidad de elementos que tendran las listas a crear.
int iteraciones: cantidad de veces que se aplicara el algoritmo.
*
.......
******
*
Returns:
*
void, no tiene retorno.
*****/

void genetico(void (*muta)(void*), void (*cruce)(void*,void*), int n, int iteraciones){
	void* padre1,* padre2, *hijo1, *hijo2;

	padre1 = generarSolucion(n);
	padre2 = generarSolucion(n);
	hijo1 = copiar(padre1);
	hijo2 = copiar(padre2);

	for (int i = 0; i < iteraciones; i++) {
		cruce(hijo1,hijo2);
		if ((evaluacionLista(fun,padre1)<evaluacionLista(fun,hijo1)) && (evaluacionLista(fun,padre2)<evaluacionLista(fun,hijo2))){
			copiarSinCrear(hijo1,padre1);
			copiarSinCrear(hijo2,padre2);
		}

		muta(hijo1);
		muta(hijo2);

		if (evaluacionLista(fun,padre1)<evaluacionLista(fun,hijo1)){
			copiarSinCrear(hijo1,padre1);
		}
		if (evaluacionLista(fun,padre2)<evaluacionLista(fun,hijo2)){
			copiarSinCrear(hijo2,padre2);
		}
	}
	printf("Lista 1: \n");
	imprimirSolucion(padre1);
	printf("Puntaje Lista 1: %d\n\n", evaluacionLista(fun, padre1));
	printf("Lista 2: \n");
	imprimirSolucion(padre2);
	printf("Puntaje Lista 2: %d\n", evaluacionLista(fun, padre2));
	borrar(padre1);
	borrar(padre2);
	borrar(hijo1);
	borrar(hijo2);
}

/*----------------------------------------------------------------------------*/
