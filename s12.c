#include <stdlib.h>
#include <stdio.h>

/* Agregue el/los TDA que va a utilizar en esta actividad */
#include "S11_TDAGrafoMA_C3_CARRILLO_VICENTE.h"
#include "TDAColaC3.h"
#include "TDAlista.h"
#include "TDAPila.h"

/* Funciones requeridas */
int GradodeVertice(TDAgrafoC3* grafo, int ver) {
    int cont = 0, i = 0;
    if (ver < 0 || ver >= grafo->n) {
        printf("Error: vértice fuera de rango.\n");
        return -1;
    }

    while (i < grafo->n) {
        if (grafo->MAdy[ver][i] != 0) {
            cont++;
        }
        i++;
    }
    return cont;
}

int GradoPromedio(TDAgrafoC3* grafo) {
    int i = 0, suma = 0;
    while (i < grafo->n) {
        suma += GradodeVertice(grafo, i);
        i++;
    }
    return suma / grafo->n;
}

int* bfs(TDAgrafoC3* grafo, int ver) {
    ColaC3* cola = crearColaC3();
    int* resultado = (int*)malloc((grafo->n + 1) * sizeof(int));
    int* visitado = (int*)malloc(grafo->n * sizeof(int));
    
    for (int i = 0; i < grafo->n; i++) {
        visitado[i] = 0;
    }

    encolarC3(cola, ver);
    visitado[ver] = 1;
    int idx = 0;

    while (!esColaVacia(cola)) {
        int actual = desencolarC3(cola);
        resultado[idx++] = actual;

        for (int v = 0; v < grafo->n; v++) {
            if (grafo->MAdy[actual][v] == 1 && visitado[v] == 0) {
                encolarC3(cola, v);
                visitado[v] = 1;
            }
        }
    }
    resultado[idx] = -1;

    return resultado;
}

int esConexo(TDAgrafoC3* grafo) {
    int* visitado = (int*)malloc(grafo->n * sizeof(int));

    for (int i = 0; i < grafo->n; i++) {
        visitado[i] = 0;
    }
    ColaC3* cola = crearColaC3();
    encolarC3(cola, 0);
    visitado[0] = 1;

    while (!esColaVacia(cola)) {
        int actual = desencolarC3(cola);

        for (int v = 0; v < grafo->n; v++) {
            if (grafo->MAdy[actual][v] == 1 && visitado[v] == 0) {
                encolarC3(cola, v);
                visitado[v] = 1;
            }
        }
    }

    for (int i = 0; i < grafo->n; i++) {
        if (visitado[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int distancia(TDAgrafoC3* grafo, int i, int j) {
    if (i == j) {
        return 0;
    }

    ColaC3* cola = crearColaC3();
    int* nivel = (int*)malloc(grafo->n * sizeof(int));
    int* visitados = (int*)malloc(grafo->n * sizeof(int));

    for (int k = 0; k < grafo->n; k++) {
        visitados[k] = 0;
        nivel[k] = -1;
    }

    encolarC3(cola, i);
    visitados[i] = 1;
    nivel[i] = 0;

    while (!esColaVacia(cola)) {
        int actual = desencolarC3(cola);

        for (int v = 0; v < grafo->n; v++) {
            if (grafo->MAdy[actual][v] == 1 && visitados[v] == 0) {
                encolarC3(cola, v);
                visitados[v] = 1;
                nivel[v] = nivel[actual] + 1;

                if (v == j) {
                    return nivel[v];
                }
            }
        }
    }
    return -1;
}


int* dfs(TDAgrafoC3 *grafo, int node) {
    int n = grafo->n;
    int *visited = (int *)calloc(n, sizeof(int));  // Vector de nodos visitados
    int *result = (int *)malloc(n * sizeof(int));  // Resultado del recorrido
    int index = 0;

    Stack *stack = createStack(n);
    push(stack, node);

    while (!isEmpty(stack)) {
        int current = pop(stack);

        if (!visited[current]) {
            visited[current] = 1;
            result[index++] = current;

            // Apilar nodos adyacentes no visitados
            for (int i = 0; i < n; i++) {
                if (grafo->MAdy[current][i] == 1 && !visited[i]) {
                    push(stack, i);
                }
            }
        }
    }

    free(stack->data);
    free(stack);
    free(visited);

    return result; // Devuelve el resultado del recorrido
}

/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "TDAgrafo.h"

// Función de Dijkstra
int* dijkstra(TDAgrafoC3* grafo, int start) {
    int n = grafo->n;
    int* dist = (int*)malloc(n * sizeof(int));  // Distancias mínimas desde el nodo inicial
    bool* visited = (bool*)malloc(n * sizeof(bool)); // Nodos visitados
    int INF = INT_MAX;

    // Inicialización
    for (int i = 0; i < n; i++) {
        dist[i] = INF;       // Inicialmente, todas las distancias son "infinito"
        visited[i] = false;  // Ningún nodo está visitado al principio
    }
    dist[start] = 0; // La distancia del nodo inicial a sí mismo es 0

    // Algoritmo principal
    for (int i = 0; i < n - 1; i++) {
        // Encontrar el nodo no visitado con la distancia mínima
        int minDist = INF, u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // No hay más nodos alcanzables
        visited[u] = true;  // Marcar el nodo como visitado

        // Actualizar las distancias de los nodos adyacentes a `u`
        for (int v = 0; v < n; v++) {
            if (grafo->MAdy[u][v] != 0 && !visited[v] && dist[u] != INF) {
                int newDist = dist[u] + grafo->MAdy[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                }
            }
        }
    }

    free(visited);
    return dist; // Devolver el arreglo de distancias mínimas
}*/

/*int* dfs(TDAgrafoC3 *grafo, int start) {
    int n = grafo->n;
    int *visited = (int *)calloc(n, sizeof(int));  // Vector para rastrear nodos visitados
    int *result = (int *)malloc(n * sizeof(int));  // Resultado del recorrido
    int index = 0;

    Stack *stack = createStack(n); // Pila para simular la recursión
    push(stack, start);

    while (!isEmpty(stack)) {
        int current = pop(stack);

        // Si el nodo aún no ha sido visitado
        if (!visited[current]) {
            visited[current] = 1;
            result[index++] = current;

            // Apilar los nodos adyacentes no visitados
            for (int i = 0; i < n; i++) {
                if (grafo->MAdy[current][i] == 1 && !visited[i]) {
                    push(stack, i);
                }
            }
        }
    }

    free(stack->data);
    free(stack);
    free(visited);

    return result; // Devuelve el orden de los nodos visitados
}*/

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <nombre del archivo>\n", argv[0]);
        return 1;
    }

    FILE* archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s.\n", argv[1]);
        return 1;
    }

    int cantVer, cantAris;
    fscanf(archivo, "%d %d", &cantVer, &cantAris);
    
    TDAgrafoC3 *grafo = crearGrafoVacioC3(cantVer);

    int a, b, i;
    for (i = 0; i < cantAris; i++) {
        fscanf(archivo, "%d %d", &a, &b);
        agregar_aristaNDC3(grafo, a, b);
    }

    fclose(archivo);

    /* DECLARACIÓN DE VARIABLES */
    printf("\n");

    /* PROBLEMA 1.a - Grado del vértice */
    printf("Resultados del problema 1:\n");
    int verprueba = 0;  // Puedes cambiar este valor para probar otros vértices
    int grado = GradodeVertice(grafo, verprueba);
    if (grado != -1) {
        printf("Grado del vértice %d: %d\n", verprueba, grado);
    } else {
        printf("El vértice %d no existe en el grafo.\n", verprueba);
    }

    printf("\n");

    /* PROBLEMA 1.b - Grado promedio */
    printf("Resultados del problema 2:\n");
    int promedio = GradoPromedio(grafo);
    printf("%d", promedio);

    printf("\n");

    /* PROBLEMA 2.a - Comprobación de conectividad */
    printf("Resultados del problema 3:\n");
    printf("El grafo es conexo? %d\n", esConexo(grafo));

    printf("\n");

    /* PROBLEMA 2.b - Recorrido BFS */
    printf("Resultados del problema 4:\n");
    int* resultadoBFS = bfs(grafo, 0);  // Nodo inicial 0
    printf("Recorrido BFS: ");
    for (int i = 0; resultadoBFS[i] != -1; i++) {
        printf("%d ", resultadoBFS[i]);
    }
    printf("\n");
    printf("\n");

    /* PROBLEMA 3 - Distancia entre nodos */
    printf("Resultados del problema 5:\n");
    int nodoInicio = 0, nodoDestino = 1;
    int resultado = distancia(grafo, nodoInicio, nodoDestino);

    if (resultado != -1) {
        printf("La distancia entre %d y %d es: %d\n", nodoInicio, nodoDestino, resultado);
    } else {
        printf("No se puede llegar del nodo %d al nodo %d.\n", nodoInicio, nodoDestino);
    }

    printf("\n");

    return 0;
}