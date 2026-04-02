#include <stdint.h>
#include <stdbool.h>

/* DECLARACION DE TIPOS */
/* -------------------- */

typedef struct estudiante_s {
  char nombre[64];
  char apellido[64];
  uint32_t ci;
  uint8_t grado;
  float promedio;
} estudiante_t;

typedef struct node_s {
  estudiante_t* estudiante;
  struct node_s* next;
} node_t;


/* DECLARACION DE TIPOS */
/* -------------------- */

node_t* initialize_list();
bool insert_student(node_t* head, estudiante_t* student);
bool remove_student(node_t* head, uint32_t ci);
void print_list(node_t* head);
