#include "estudiantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
  printf("=== Iniciando Prueba de Estudiantes ===\n");

  node_t* lista = initialize_list();

  estudiante_t* e1 = malloc(sizeof(estudiante_t));
  e1->ci = 12345678;
  e1->grado = 1;
  e1->promedio = 9.5;
  strcpy(e1->nombre, "Nicolás");
  strcpy(e1->apellido, "Calarco");

  print_student(e1);

  printf("Insertando flaco CI: %d...\n", e1->ci);
  if (insert_student(lista, e1)) {
      printf("Todo joya.\n");
  }

  estudiante_t* e2 = malloc(sizeof(estudiante_t));
  e2->ci = 87654321;
  e2->grado = 2;
  e2->promedio = 7.8;
  strcpy(e2->nombre, "Pedro");
  strcpy(e2->apellido, "Alonso");
    
  printf("Insertando muchacho CI: %d...\n", e2->ci);
  insert_student(lista, e2);

  
  estudiante_t* e3 = malloc(sizeof(estudiante_t));
  e3->ci = 3456789;
  e3->grado = 3;
  e3->promedio = 9.1;
  strcpy(e3->nombre, "Alfredo");
  strcpy(e3->apellido, "Arnaud");

  printf("Insertando pupilo CI: %d...\n", e3->ci);
  insert_student(lista, e3);


  // busco estudiante por ci
  estudiante_t* uuu = search_student(lista, true, 12345678, NULL, NULL);
  print_student(uuu);

  // busco estudiante por nombre y apellido
  estudiante_t* aah = search_student(lista, false, 0, "Pedro", "Alonso");
  print_student(aah);

    printf("\nContenido de la lista:\n");
    print_list(lista);

    // 5. Intentamos borrar
    printf("\nBorrando estudiante 12345678...\n");
    if (remove_student(lista, 12345678)) {
        printf("Estudiante fletado.\n");
    } else {
        printf("No se pudo borrar (Joel Gak me lo impide).\n");
    }

    printf("\nLista final:\n");
    print_list(lista);

  //FALTA LIBERAR MEMORIA
    return 0;
}
