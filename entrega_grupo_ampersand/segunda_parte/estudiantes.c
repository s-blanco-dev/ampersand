#include "estudiantes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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


