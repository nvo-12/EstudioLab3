#ifndef TDA_LISTA_H
#define TDA_LISTA_H

#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura Nodo
struct nodo {
    int info;
    struct nodo *sig;
};
typedef struct nodo Nodo;

// Definición de la estructura Lista
struct lista {  
    Nodo *head;
    int n;  // Número de nodos de la lista
};
typedef struct lista Lista;

// Funciones de la lista
Lista *crearListaVacia() {
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    lista->head = NULL;
    lista->n = 0;
    return lista;
}

int esListaVacia(Lista *lista) {
    if (lista->head == NULL) return 1;
    return 0;
}

void recorrerLista(Lista *lista) {
    if (!esListaVacia(lista)) {
        Nodo *auxiliar = lista->head;
        while (auxiliar != NULL) {
            printf("%d ", auxiliar->info);
            auxiliar = auxiliar->sig;
        }
        printf("\n");
    } else {
        printf("La lista está vacía\n");
    }
}

void insertarInicio(Lista *lista, int dato) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->info = dato;
    nuevo->sig = lista->head;
    lista->head = nuevo;
    lista->n = lista->n + 1;
}

void insertarFin(Lista *lista, int dato) {
    Nodo *nuevo;
    Nodo *aux;

    nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->info = dato;
    nuevo->sig = NULL;

    if (lista->head == NULL) {
        lista->head = nuevo;
        lista->n = lista->n + 1;
        return;
    }

    aux = lista->head;
    while (aux->sig != NULL) aux = aux->sig;

    aux->sig = nuevo;
    lista->n = lista->n + 1;
}

void eliminarInicio(Lista *lista) {
    Nodo *auxiliar;
    if (!esListaVacia(lista)) {
        auxiliar = lista->head;
        lista->head = lista->head->sig;
        free(auxiliar);
        lista->n = lista->n - 1;
    }
}

void liberarLista(Lista *lista) {
    while (!esListaVacia(lista)) {
        eliminarInicio(lista);
    }
}

#endif  // TDA_LISTA_H