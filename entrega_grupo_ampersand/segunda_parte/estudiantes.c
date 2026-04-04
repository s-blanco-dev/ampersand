#include "estudiantes.h"
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


void print_student(estudiante_t* student){
  if (student == NULL) {
    return;
  }

  printf("%s, %s\nCI: %d\nGrado: %d\nPromedio: %f\n", student->apellido, student->nombre, student->ci, student->grado, student->promedio);
}

/*
 * @brief Inicializa una lista enlazada con un nodo choclo
 *
 * El nodo choclo (término acuñado por el equipo de desarrollo) es un nodo que sólo 
 * sirve para marcar el inicio de una lista (no tiene datos y apunta a NULL)
 *
 * @return node_t*  El puntero al nodo inicial de la lista 
 * */
node_t* initialize_list() {
  node_t* choclo = malloc(sizeof(node_t));
  // Mi alma aguarda al Señor, más que el centinela la aurora
  
  if (choclo == NULL) {
    return NULL;
  }

  choclo->estudiante = NULL;
  choclo->next = NULL;
  return choclo;
}

bool insert_student(node_t* head, estudiante_t* student){
  node_t* temp = head;
  node_t* newNode = malloc(sizeof(node_t));
  newNode->estudiante = student;
  newNode->next = NULL;

  if (newNode == NULL) {
    return false;
  }

  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = newNode;
  return true;
}

bool remove_student(node_t *head, uint32_t ci){
  node_t* temp = head;

  while (temp->next != NULL) {
    if (temp->next->estudiante->ci == ci) {
      node_t *target = temp->next;
      temp->next = target->next;
      free(target->estudiante); // borro todo
      free(target);      
      return true;
    }
    temp = temp->next;
  }

  return false;
}

void print_list(node_t *head){
  if (head == NULL) {
    return;
  }

  node_t* temp = head->next;
  int i = 0;
  while (temp != NULL) {
    printf("%d | CI: %d -> ", i, temp->estudiante->ci);
    i++;
    temp = temp->next;
  }
  printf("NULL \n");
}

/*
 * @brief Permite buscar estudiante por ci o nombre y apellido
 *
 * Itera sobre la lista hasta encontrar una coincidencia. Si el tipo de búsqueda es por ci (tipo == true), 
 * retorono cuando esta coincide. Si es por nombre y apellido (tipo == false), entonces retorno 
 * si hay coincidencia de ambos miembros.
 *
 * @param head  Puntero al primer elemento de la lista
 * @param tipo  Define el tipo de búsqueda (true si es por ci, false si es por nombre y apellido)
 * @param ci    CI del estudiante (se usa cuando tipo == true)
 * @param nombre    String con nombre del estudiante (se usa cuando tipo == false)
 * @param apellido    String con apellido del est. (se usa cuando tipo == false)
 * */
estudiante_t* search_student(node_t* head, bool tipo, uint32_t ci, char* nombre, char* apellido){
  node_t* temp = head->next;

  while (temp != NULL) {
    if (tipo == true) {
      // tipo de búsqueda por ci
      if (temp->estudiante->ci == ci) {
        return temp->estudiante;
      }
    } else {
      // tipo de búsqueda por nombre y apellido
      if (strcmp(temp->estudiante->nombre, nombre) == 0 && strcmp(temp->estudiante->apellido, apellido) == 0) {
        return temp->estudiante;
      }
    }
    temp = temp->next;
  }

  return NULL; // el estudiante no existe
}

int compare_by_ci(estudiante_t* a, estudiante_t* b){
  if (a->ci < b->ci) return -1;
  if (a->ci > b->ci) return 1;
  return 0;
}

int compare_by_apellido(estudiante_t* a, estudiante_t* b){
  // Inicialmente comparo por el apellido de los pupilos:
  int compare = strcmp(a->apellido, b->apellido);
  if (compare != 0){
    return compare;
  // Si llegan a tener el mismo apellido, comparamos por sus nombres:
  compare = strcmp(a->nombre, b->nombre);
  if (compare != 0){
    return compare;
  }
  // Si llegaran a apellidarse y llamarse igual, ejemplo: "Santiago Blanco", comparo finalmente por cedula:
  if (a->ci < b->ci) return -1;
  if (a->ci > b->ci) return 1;
  }
}

/**
 * @brief Reorganiza un subárbol para mantener la propiedad de heap (max-heap).
 *
 * Esta función asegura que el nodo en la posición `i` cumpla la propiedad de heap:
 * el valor en `arr[i]` debe ser mayor (según el comparador) que sus hijos.
 * Si no se cumple, intercambia el elemento con el mayor de sus hijos y continúa
 * el proceso recursivamente.
 *
 * Se utiliza como parte del algoritmo Heap Sort para construir y mantener
 * la estructura de heap.
 *
 * @param arr Array de punteros a estudiantes (estudiante_t*).
 * @param n Cantidad de elementos en el heap (tamaño del array).
 * @param i Índice del nodo que se desea "heapificar".
 * @param cmp Puntero a función comparadora que define el criterio de orden.
 *            Debe retornar:
 *              > 0 si el primer elemento es mayor que el segundo,
 *              = 0 si son iguales,
 *              < 0 si el primero es menor.
 *
 * @note Esta implementación construye un max-heap.
 * @note Complejidad temporal: O(log n).
 */
void heapify(estudiante_t** arr, int n, int i, int (*cmp)(estudiante_t*, estudiante_t*)){
  
  // inicializar el mas grande como root
  int largest = i;
  // hijo izquierdo (left child)
  int left = 2 * i + 1;
  // hijo derecho (right child)
  int right = 2 * i + 2;
  
  // "if left child is larger than root: modify this":
  if (left < n && cmp(arr[left], arr[largest]) > 0){
    largest = left;
  }
  if (right < n && cmp(arr[right], arr[largest]) > 0){
    largest = right;
  }
  // si el mas grande no es root:
  if (largest != i){
    estudiante_t* temp = arr[i];
    arr[i] = arr[largest];
    arr[largest] = temp;
    
    // heapify recursivo:
    heapify(arr, n, largest, cmp);
  }
}

/**
 * @brief Ordena un array de estudiantes utilizando el algoritmo Heap Sort.
 *
 * Este algoritmo ordena el array en orden ascendente según el criterio definido
 * por la función comparadora. Primero construye un max-heap a partir del array,
 * y luego extrae iterativamente el elemento máximo (raíz del heap),
 * colocándolo al final del array.
 *
 * El proceso consiste en:
 * 1. Construir un max-heap desde el array original.
 * 2. Intercambiar la raíz (máximo) con el último elemento.
 * 3. Reducir el tamaño del heap y aplicar heapify nuevamente.
 * 4. Repetir hasta ordenar todo el array.
 *
 * @param arr Array de punteros a estudiantes (estudiante_t*).
 * @param n Cantidad de elementos en el array.
 * @param cmp Puntero a función comparadora que define el criterio de orden.
 *            Debe retornar:
 *              > 0 si el primer elemento es mayor que el segundo,
 *              = 0 si son iguales,
 *              < 0 si el primero es menor.
 *
 * @note El orden final es ascendente según el comparador.
 * @note Complejidad temporal:
 *       - Mejor caso: O(n log n)
 *       - Caso promedio: O(n log n)
 *       - Peor caso: O(n log n)
 * @note Complejidad espacial: O(1) adicional (in-place sobre el array).
 */
void heap_sort(estudiante_t** arr, int n, int (*cmp)(estudiante_t*, estudiante_t*)){

  if (arr == NULL || n <= 1){
    return;
  }
  // construccion del heap (heapify desde abajo):
  for (int i = n / 2 - 1; i >= 0; i--){
    heapify(arr, n, i, cmp);
  }
  // uno por uno extraemos los elementos del heap:
  for (int i = n - -1; i > 0; i--){
    // movemos el root actual al final:
    estudiante_t* temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;

    heapify(arr, i, 0, cmp);
  }
}

// Metodo para saber el largo de una lista
int list_lenght(node_t* head){
  int count = 0;
  node_t* temp = head->next;

  while (temp != NULL){
    count++;
    temp = temp->next;
  }
  return count;
}

void sort_list(node_t* head, int (*cmp)(estudiante_t*, estudiante_t*)){

  if (head == NULL || head->next == NULL){
    return;
  }

  int n = list_lenght(head);

  estudiante_t** arr = malloc(n * sizeof(estudiante_t*));
  if (arr == NULL){
    return;
  }
  
  node_t* temp = head->next;
  int pp = 0;

  while (temp != NULL){
    arr[pp] = temp->estudiante;
    pp++;
    temp = temp->next;
  }
  // aplicamos nuestro algoritmo que marcha joya (heapsort > quicksort):
  heap_sort(arr, n, cmp);

  temp = head->next;
  pp = 0;
  while (temp != NULL){
    temp->estudiante = arr[pp];
    pp++;
    temp = temp->next;
    }

  free(arr);
}

void sort_by_ci(node_t* head,){
  sort_list(head, compare_by_ci);
}

void compare_by_apellido(node_t* head){
  sort_list(head, compare_by_apellido);
}
