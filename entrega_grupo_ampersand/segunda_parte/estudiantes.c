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
