#include <stdio.h>
#include <stdlib.h>
#include "TDALista.h"

typedef struct cola {
    int n;       // Número de elementos en la cola
    Lista *cola; // Lista que actúa como base de la cola
} ColaC3;

// Crear una cola vacía
ColaC3 *crearColaC3() {
    ColaC3 *nuevo = (ColaC3 *)malloc(sizeof(ColaC3));
    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria para la cola.\n");
        exit(EXIT_FAILURE);
    }
    nuevo->n = 0;
    nuevo->cola = crearListaVacia();
    if (nuevo->cola == NULL) {
        printf("Error: no se pudo asignar memoria para la lista interna de la cola.\n");
        free(nuevo);
        exit(EXIT_FAILURE);
    }
    return nuevo;
}

// Verificar si la cola está vacía
int esColaVacia(ColaC3 *C) {
    return C->n == 0;
}

// Mostrar los elementos de la cola
void mostrarColaC3(ColaC3 *C) {
    printf("\n\nMostrando ColaC3\n");
    recorrerLista(C->cola);
}

// Encolar un elemento
void encolarC3(ColaC3 *C, int dato) {
    insertarFin(C->cola, dato);
    C->n++;
}

// Desencolar un elemento
int desencolarC3(ColaC3 *C) {
    if (esColaVacia(C)) {
        printf("Error: no se puede desencolar, la cola está vacía.\n");
        return -1; // Retorna un valor especial indicando que la operación falló
    }
    int dato = C->cola->head->info;
    eliminarInicio(C->cola);
    C->n--;
    return dato;
}

// Liberar la memoria de la cola
void liberarColaC3(ColaC3 *C) {
    liberarLista(C->cola); // Libera la lista asociada
    free(C);               // Libera la estructura de la cola
}
