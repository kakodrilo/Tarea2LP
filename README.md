# Tarea2LP
Tarea 2 Lenguajes de Programación 2018-2
>Integrantes:
>  - Joaquín Castillo Tapia	Rol:201773520-1	
>  - María Paz Morales Llopis	Rol:201773505-8 
>
>Paralelo: 200

### Para correr el codigo es necesario:
#### Archivos:

* genetico.h : Header con la declaración de las principales funciones de genetico.c
* genetico.c : Código con la definición de las funciones declaradas en genetico.h
* fun.h : Header con la declaración de la función de evaluación. Esta función debe llamarse obligatoriamente fun. 
* fun.c : Código con la definición de la funcion de evaluación, este debe comenzar con:
  ```C
  #include "fun.h"
  typedef struct tNodo{
  void * dato;
  char tipo;
  }tNodo;
  ``` 
   
* main.c : Código en donde se define la función main en la cual se utilizarán las funciones de los archivos genetico.h y fun.h. El archivo debe comenzar con:
  ```C
  #include "fun.h"
  #include "genetico.h"
  ``` 
	  

 * makefile : Archivo que contiene las reglas de compilación.
 
>   Todos los archivos deben estar en la misma ubicación.
>
>   Los archivos deben sí o sí tener ese nombre.
>
>   La carpeta entregada contiene archivos fun.h, fun.c y main.c de ejemplos.

#### Compilación:
* Compilador gcc
* valgrind
* Para compilar y ejecutar, escribir el siguiente comando en al terminal (dentro de la ubicación de los archivos):
   
   ```
   $ make
   ```
		
>	En los comandos de compilación está incluido -Wall
>
>	La ejecución se hace con valgrind
>
>	Este comando crea 4 archivos nuevos: fun.o, genetico.o, main.o. Y el ejecutable genetico.

* Para borrar los archivos creados y reiniciar la compilación, ejcutar en la teminal:
   
   ```
   $ make clear
   ```
			
### Supuestos:
- El primer nodo de la lista está en la posición 0 (considerado como par).
- Los elementos de la lista se imprimen hacia abajo.
- Si luego de realizar cualquiera de las funciones mutación, la lista queda igual, entonces se realiza la mutación nuevamente.
- Las listas entregadas como parámetros en las funciones de cruce siempre tienen el mismo largo.
